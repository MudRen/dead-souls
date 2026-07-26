//	/d/standard/bank.c
//	from the Nightmare mudlib
//	banking room
//	created by Descartes of Borg 28 february 1993

#include <lib.h>
#include <daemons.h>
//#include <money.h>
//#include <bank.h>

#define BANK_ID "praxis"

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("Bugga", "Bugga");
    add_action("read", "read");
}

void create() {
    ::create();
    SetProperty("magic hold", 10);
    SetProperty("no castle", 1);
    SetProperty("light", 2);
    SetProperty("night light", 2);
    SetShort( "普拉克西斯银行");
    SetLong(
            "欢迎来到普拉克西斯银行！\n"
            "普拉克西斯银行是一座可爱的建筑。红色地毯覆盖着磨损的地板，"
            "北边有一个抛光的木质柜台。银行后面有一个金库，"
            "存放着全镇的存款。出纳员旁边的牌子详细说明了所有命令。"
            "银行的出口在南边。");
    SetItems(
            (["bank" : "你在它巨大的大厅里。你面前有一个柜台，身后是出口。",
             "citizens" : "他们漫无目的地闲逛。",
             "account" : "你是个疯子。",
             "sign" : "阅读它会给你一份命令列表。",
             "teller" : "出纳员不耐烦地看着你。",
             "counter" : "一个出纳员在后面等你做些什么。",
             "exit" : "通往小巷。",
             "vault" : (: this_object(), "look_at_vault" :) ]) );
    SetExits( 
            (["south":"/domains/Praxis/alley1"]) );
}

void reset() {
    object mon, weapon, key;

    ::reset();
    if(!present("guard")) {
        mon = new(LIB_NPC);
        mon->SetKeyName("guard");
        mon->SetId( ({ "guard", "bank guard", "big ogre" }) );
        mon->SetRace( "ogre");
        mon->SetGender("male");
        mon->SetShort( "银行守卫");
        mon->SetLong( "一个被雇来守卫新开银行的又大又丑的食人魔。\n");
        mon->SetLevel(14);
        mon->SetRace("human");
        mon->SetHealthPoints(500 + random(100));
        mon->SetClass("fighter");
        mon->SetSpellChance(10);
        mon->SetSpells( ({ "parry", "Bugga" }) );
        mon->SetSkills("defense", 70);
        mon->SetSkills("blade", 90);
        mon->set_emotes(9,
                ({ "守卫说：该死的小偷！",
                 "守卫咕哝着。",
                 "守卫说：你别想从我这里过去！",
                 "守卫说：你让我恶心。"}), 1);
        mon->set_emotes(3,
                ({ "守卫大口吃着老鼠派。",
                 "守卫说：我讨厌盗贼。" }), 0);
        mon->SetWielding_limbs( ({ "right hand", "left hand" }) );
        mon->move(this_object());
        weapon = new(LIB_ITEM);
        weapon->SetKeyName("broadsword");
        weapon->SetId( ({ "broadsword", "sword" }) );
        weapon->SetShort( "阔剑");
        weapon->SetLong( "一把巨大的阔剑。");
        weapon->SetClass(13);
        weapon->SetType("blade");
        weapon->SetMass(700);
        weapon->SetValue(91);
        weapon->move(mon);
        mon->eventForce("wield broadsword in right hand");
        key = new(LIB_ITEM);
        key->SetKeyName("key");
        key->SetId( ({ "bank key", "key", "bronze key" }) );
        key->SetShort( "铜钥匙");
        key->SetLong( "一把不起眼的铜钥匙。");
        key->SetMass(29);
        key->SetValue(35);
        key->move(mon);
    }
    if(query_reset_number() != 1) {
        object tmpob = present("guard");
        if(tmpob){
            tmpob->eventForce("close vault");
            tmpob->eventForce("lock vault with key");
        }
    }
}

int do_drunkard() {
    if(present("guard") && !this_player()->query_invis()) {
        present("guard")->eventForce("kill "+this_player()->query_name());
        this_player()->add_follower(present("guard"));
        write("守卫在你把钥匙插进去之前就阻止了你！");
        say(this_player()->query_cap_name()+"试图闯入金库时被阻止了！");
        return 0;
    }
    if(this_player()->query_intox()) {
        write("你醉醺醺地摸索着银行钥匙。");
        say(this_player()->query_cap_name()+"醉醺醺地摆弄着银行钥匙。");
        return 0;
    }
    return 1;
}

int read(string str) {
    if(str != "sign") return notify_fail("读什么？\n");
    message("info",
            "你可以在普拉克西斯商业银行执行以下操作：\n"
            "<open account>\n为你开设账户。\n\n"
            "<close account>\n关闭你的账户。\n\n"
            "<balance>\n显示你的账户余额信息。\n\n"
            "<deposit [#] [类型]>\n存入指定数量的货币。\n\n"
            "<withdraw [#] [类型]>\n取出指定数量的货币。\n\n"
            "<exchange [#] of [类型1] for [类型2]>\n兑换货币。收取10%的手续费。\n\n",
            this_player()
           );
    return 1;
}

int Bugga(string str) {
    string limb;
    object ob;
    int amount;

    if(this_player()->is_player()) return 0;
    ob = (object)this_player()->query_current_attacker();
    if(!ob) return 1;
    limb = ob->return_limb();
    if(ob->query_class() == "rogue") amount = 24 + random(30);
    else amount = 20 + random(20);
    ob->do_damage(limb, amount);
    tell_object(ob, "守卫用左拳猛击你的"+limb+"！");
    tell_room(this_object(), "守卫用左拳猛击了"+ob->query_cap_name()+"的"+limb+"！", ({ ob }));
    return 1;
}

