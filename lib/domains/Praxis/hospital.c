#include <lib.h>
#include <daemons.h>

inherit LIB_ROOM;

#define COST    money/bonus
#define MAX_DONATION 600

mapping blood;

void init() {
    ::init();
    add_action("new_body", "renew");
    add_action("clean_poison", "clean");
    add_action("regenerate", "regenerate");
    add_action("read", "read");
    add_action("donate", "donate");
    add_action("transfuse", "transfuse");
}

void create() {
    ::create();
    SetProperties( (["light" :2 , "indoors" :1 , "castle" : 1 ]) );
    SetShort( "普拉克西斯医院");
    SetLong(
            "你正身处普拉克西斯医院。它基本上就是一个大房间，"
            "几排简陋的床铺整齐排列。医院看起来不太干净，"
            "在接受服务之前你可能要三思。远处的墙上张贴着"
            "所有可提供服务的清单。通往主路的出口在东边。");
    SetItems(
            (["list" : "你可以输入 <read list> 查看所有服务项目。",
             "hospital" : "这里的牧师擅长再生失去的肢体。",
             "clerics" : "他们正在为伤员治疗伤口。",
             "cleric" : "他正在为一位病人治疗伤口。"]));
    SetExits( 
            (["east" : "/domains/Praxis/n_centre2"]) );
    blood = ([ "who": ([]), "hp":200, "mp":200 ]);
    SetProperty("no teleport", 1);
}

int new_body(string str) {
    object *inv;
    int i;

    if( this_player()->query_level() != 1) {
        notify_fail("牧师只为新手提供这项服务。\n");
        return 0;
    }
    inv = all_inventory(this_player());
    for(i=0; i<sizeof(inv); i++) {
        inv[i]->unequip();
    }
    write("一位牧师走到你面前，低声念了一段祈祷词。");
    write("你又恢复了出生时的所有肢体！");
    say("一位牧师为新手"+this_player()->query_cap_name()+"低声祈祷。", this_player());
    this_player()->new_body();
    return 1;
}

int read(string str) {
    if(!str) {
        notify_fail("读什么？\n");
        return 0;
    }
    if(str != "list") {
        notify_fail("这里没有那个可以阅读。\n");
        return 0;
    }
    message("info", "欢迎来到普拉克西斯牧师医院！",this_player());
    message("Ninfo",
            "牧师提供以下服务：\n"
            "------------------------------------------------------------------\n"
            "<renew 身体>: 这是牧师为冒险中失去肢体的新手冒险者\n"
            "	提供的慈善服务。所有肢体都会被替换。\n"
            "<regenerate [肢体]>: 这项服务面向失去肢体的有经验冒险者。\n"
            "	肢体将被替换并恢复如新。\n"
            "	再生费用表：\n"
            "            次要肢体（非牧师）从 "+currency_value(320, "gold")+" 金币起\n"
            "            主要肢体（非牧师）最高 "+currency_value(800, "gold")+" 金币\n"
            "            牧师 "+currency_value(240, "gold")+" 至 "+currency_value(600, "gold")+" 金币\n"
            "<clean 毒素>: 帮助清除体内的部分毒素。\n"
            "\t费用： "+currency_value(50, "gold")+" 金币\n"
            "<donate # (hp 或 mp) 血液>: 捐献你的一些血液以换取金币。\n"
            "<transfuse # (hp 或 mp)>: 为你的身体注入一些血液以恢复生命值或魔法值\n"
            "\t费用：数量乘以 "+currency_value(3, "gold")+" 金币。\n"
            "当前库存： "+blood["hp"]+" 生命值血液和 "+blood["mp"]+" 魔法值血液可供使用。\n"
            "------------------------------------------------------------------\n"
            "携带断肢可享受半价再生优惠！\n"
            "您的捐款只用于公益事业。\n", this_player());
    return 1;
}

int clean_poison(string str) {
    object tp;

    if(!str) return 0;
    if(str != "poison") return 0;
    tp = this_player();
    if(tp->query_poisoning()<1) {
        notify_fail("牧师轻声对你说：但你并没有中毒啊！\n");
        return 0;
    }
    if(tp->query_money("gold") < currency_value(50, "gold")) {
        notify_fail("你没有足够的金币支付费用。\n");
        return 0;
    }
    tp->AddCurrency("gold", -currency_value(50, "gold"));
    tp->add_poisoning(-10);
    write("牧师对你施放了一个治疗术。");
    say("牧师对"+tp->query_cap_name()+"施放了一个治疗术。", tp);
    return 1;
}

int regenerate(string limb) {
    int money, bonus;
    mapping limb_info;
    object tp;
    string *there, *missing;

    tp = this_player();
    if(present(limb, this_player())) bonus = 2;
    else bonus = 1;
    there = tp->query_limbs();
    missing = this_player()->query_severed_limbs() +
        RACES_D->query_limbs(this_player()->query_race());
    /*
       checking with the race_d is allowing compatibility with old
       versions of the mudlib
     */
    if(!missing) {
        notify_fail("你并没有缺少任何肢体！\n");
        return 0;
    }
    if(member_array(limb, missing) == -1) {
        notify_fail("你并没有缺少那个肢体！\n");
        return 0;
    }
    if(member_array(limb, there) != -1) {
        notify_fail("你已经恢复了那个肢体！\n");
        return 0;
    }
    limb_info= RACES_D->query_limb_info(limb,tp->query_race());
    if(!limb_info) {
        notify_fail("那个肢体无法被替换！\n");
        return 0;
    }
    if(limb_info["attach"] != "0") {
        if(member_array(limb_info["attach"], there) == -1) {
            notify_fail("你需要一个"+limb_info["attach"]+"才能做到！\n");
            return 0;
        }
    }
    if(strsrch(limb, "hand") != -1 || strsrch(limb, "foot") != -1 || 
            strsrch(limb, "hoof") != -1) {
        money = (this_player()->query_class() == "cleric" ? 
                currency_value(240, "gold") : currency_value(320, "gold"));
    }
    else money = (this_player()->query_class() == "cleric" ? 
            currency_value(600, "gold") : currency_value(800, "gold"));
    if(tp->query_money("gold") < COST) {
        notify_fail("牧师告诉你：你没有足够的金币。\n");
        return 0;
    }
    tp->AddLimb(limb, limb_info["ref"], tp->query_max_hp()/limb_info["max"], 0, 0);
    if(member_array(limb, RACES_D->query_wielding_limbs(tp->query_race())) != -1) 
        tp->add_wielding_limb(limb);
    this_player()->AddCurrency("gold", -COST);
    say(sprintf("%s向牧师们寻求帮助，治疗缺失的%s。", this_player()->query_cap_name(), limb));
    write("牧师们恢复了你的"+limb+"！");
    return 1;
}

int donate(string str) {
    string what;
    int amount, tmp;

    if(!str) {
        notify_fail("捐献什么？\n");
        return 0;
    }
    if(sscanf(str, "%d %s of blood", amount, what) !=2) {
        notify_fail("正确语法：<donate [#] [hp | mp] of blood>\n");
        return 0;
    }
    if(what != "mp" && what != "hp") {
        notify_fail("捐献什么？\n");
        return 0;
    }
    if(blood[this_player()->query_name()]+amount > MAX_DONATION) {
        write("你需要等一段时间才能再捐献那么多血液。");
        return 1;
    }
    tmp = call_other(this_player(), "query_"+what);
    if(tmp < amount + 5) {
        notify_fail("你必须至少比计划捐献的多出5点！\n");
        return 0;
    }
    call_other(this_player(), "add_"+what, -amount);
    this_player()->AddCurrency("gold", currency_value(amount/5, "gold"));
    blood[what] += amount;
    blood["who"][this_player()->query_name()] += amount;
    write("You donate some blood for "+(currency_value(amount/5, "gold"))+" gold coins.");
    say(this_player()->query_cap_name()+" donates some blood for some gold.", this_player());
    call_out("reduce_donation", 900, ({ this_player(), amount }));
    return 1;
}

int transfuse(string str) {
    string what;
    int amount;

    if(!str) {
        notify_fail("Transfuse what?\n");
        return 0;
    }
    if(sscanf(str, "%d %s", amount, what) != 2) {
        notify_fail("Correct syntax: <transfuse [#] [mp | hp]>\n");
        return 0;
    }
    if(what != "hp" && what != "mp") {
        notify_fail("You cannot do that!\n");
        return 0;
    }
    if(amount < 1) {
        notify_fail("Are you crazy?!?\n");
        return 0;
    }
    if(blood[what] < amount) {
        notify_fail("We do not have that much blood in right now.\n");
        return 0;
    }
    if(this_player()->query_money("gold") < currency_value(amount*3, "gold")) {
        notify_fail("You do not have enough gold for the tithe.\n");
        return 0;
    }
    this_player()->AddCurrency("gold", -currency_value(amount*3, "gold"));
    call_other(this_player(), "add_"+what, amount);
    write("You receive a blood transfusion");
    say(this_player()->query_cap_name()+" receives a blood transfusion.", this_player());
    return 1;
}

void reduce_donation(mixed *tmp) {
    blood["who"][tmp[0]] -= tmp[1];
    if(blood["who"][tmp[0]] < 1) map_delete(blood, tmp[0]);
}




