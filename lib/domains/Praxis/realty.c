/*    /domains/Praxis/realty.c
 *    from Nightmare IV
 *    the place to buy stuff
 *    created by Descartes of Borg 940702
 */

#include <lib.h>
#include <objects.h>

#define DEED_COST 250000
#define ORDER_COST 17000

inherit LIB_ROOM;

void create() {
    room::create();
    SetProperties( ([ "light":2, "indoors":1 ]) );
    SetShort("普拉克西斯房地产");
    SetLong(
            "欢迎来到普拉克西斯房地产！\n"
            "人们来这里购买建造庄园的地契，以及用于修改庄园的"
            "工作订单。办公室以各种沉闷的颜色装饰，"
            "办公室尽头的一张桌子是所有业务办理的地方。"
           );
    SetItems( ([ "colours": "主要是暗红色。", "desk": (: "at_desk" :),
                "office":"一个有桌子的小空间。"]) );
    SetExits( ([ "north" : "/"+__DIR__+"unnamed1" ]) );
}

void init() {
    room::init();
    add_action("read_list", "read");
    add_action("cmd_buy", "buy");
}

void reset() {
    object ob, arm;

    room::reset();
    if(present("atmos")) return;
    ob = new(LIB_NPC);
    ob->SetKeyName("atmos");
    ob->SetProperties( (["no paralyze":1, "no steal":1]));
    ob->SetId( ({ "atmos", "atmos the patron of high mortals", "patron",
                "realtor" }) );
    ob->SetShort("阿特摩斯，高级凡人的守护者");
    ob->SetLong("阿特摩斯是个怪人。");
    ob->SetLevel(66);
    ob->SetRace("artrell");
    ob->SetClass("mage");
    ob->AddCurrency("gold", currency_value(100, "gold"));
    ob->SetStat("constitution", 500);
    ob->SetStat("dexterity",500);
    ob->SetStat("strength", 500);
    ob->SetSkill("melee", 390);
    ob->SetSkill("defense", 500);
    ob->SetSkill("stealth", 300);
    ob->SetSkill("magic attack", 500);
    ob->SetHealthPoints(1000000);
    ob->SetMagicPoints(5000000);
    ob->SetSpellChance(20);
    ob->SetSpells( ({ "freeze", "fireball" }) );
    ob->SetMorality(100);
    ob->AddLimb("head","FATAL",800000,0,15);
    ob->AddLimb("torso","FATAL",800000,0,15);
    ob->AddLimb("first arm","",600000,0,15);
    ob->AddLimb("second arm","",600000,0,15);
    ob->AddLimb("third arm","",600000,0,15);
    ob->AddLimb("fourth arm","",600000,0,15);
    ob->AddLimb("first hand","",400000,0,15);
    ob->AddLimb("second hand",400000,0,15);
    ob->AddLimb("third hand","",400000,0,15);
    ob->AddLimb("fourth hand","",400000,0,15);
    ob->AddLimb("left leg","",600000,0,15);
    ob->AddLimb("right leg","",600000,0,15);
    ob->AddLimb("left foot","",400000,0,15);
    ob->AddLimb("right foot","",400000,0,15);
    ob->move(this_object());
    arm = new(LIB_ARMOR);
    arm->SetKeyName("plate of atmos");
    arm->SetId( ({ "plate", "plate of atmos" }) );
    arm->SetAdjectives( ({ "heavy", "the" }) );
    arm->SetShort("阿特摩斯的板甲");
    arm->SetLong("一件精美的仿银板甲，曾属于怪人阿特摩斯。");
    arm->SetAC(10);
    arm->true(1);
    arm->SetValue(1000);
    arm->SetMass(1500);
    arm->SetType("armour");
    arm->SetRestrictLimbs( ({ "torso", "first arm", "second arm", "third arm",
                "fourth arm" }) );
    arm->set_illuminate(20);
    arm->move(ob);
    ob->eventForce("wear plate");
}

protected int cmd_buy(string str) {
    object ob;

    if(!present("atmos", this_object()))
        return notify_fail("阿特摩斯不在！\n");
    if(str == "deed") {
        if(this_player()->query_money("gold") <
                currency_value(DEED_COST, "gold")) {
            message("my_action", "你没有足够的金币。",this_player());
            return 1;
        }
        message("my_action", "你购买了一份地契。", this_player());
        message("other_action", this_player()->query_cap_name()+
                "购买了一份地契。", this_object(), ({ this_player() }));
        this_player()->AddCurrency("gold", -currency_value(DEED_COST, "gold"));
        ob = new(OB_DEED);
        if(ob->move(this_player())) {
            message("my_action", "你掉了你的地契。", this_player());
            message("other_action", this_player()->query_cap_name()+
                    "掉了"+possessive(this_player())+"的地契。", this_object(),
                    ({ this_player() }));
            ob->move(this_object());
        }
        return 1;
    }
    else if(str == "order" || str == "work order" ) {
        if(this_player()->query_money("gold") <
                currency_value(ORDER_COST, "gold")) {
            ob->eventForce("speak 你的金币太少了！");
            return 1;
        }
        message("my_action", "你购买了一份工作订单。", this_player());
        message("other_action", this_player()->query_cap_name()+
                "购买了一份工作订单。", this_object(), ({ this_player() }));
        this_player()->AddCurrency("gold", -currency_value(ORDER_COST, "gold"));
        ob = new(OB_ORDER);
        if(ob->move(this_player())) {
            message("my_action", "你掉了工作订单！", this_player());
            message("other_action", this_player()->query_cap_name()+
                    "掉了"+possessive(this_player())+"的工作订单。",
                    this_object(), ({ this_player() }));
            ob->move(this_object());
        }
        return 1;
    }
    else return 0;
}

string at_desk(string str) {
    string tmp;

    tmp = "桌子上张贴着一份房地产选项清单。";
    if(present("atmos")) tmp += "阿特摩斯坐在后面等候。";
    else tmp += "似乎没有人在。";
    return tmp;
}
protected int read_list(string str) {
    string tmp;

    if(str != "list") return 0;
    tmp = "欢迎来到普拉克西斯房地产！\n"
        "你可以购买以下任何物品：\n"
        "    deed- 创建庄园的地契："+
        currency_value(DEED_COST, "gold")+" 金币。\n"
        "    order- 添加房间的工作订单："+
        currency_value(ORDER_COST, "gold")+" 金币。\n";
    message("info", tmp, this_player());
    return 1;
}
