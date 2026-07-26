#include <lib.h>

inherit LIB_NPC;

void create() {
    ::create();
    SetKeyName("mora");
    SetId( ({ "mora", "medium", "fortune teller", "teller" }) );
    SetShort( "莫拉，命运占卜师");
    SetLong(
            "她在精神层面上超越了这个现实世界。"
            "作为最高级别的灵媒，她为前来寻求指引的人占卜命运。"
            "为自己\"horoscope\"需要60金币。"
            "为他人占卜需要100金币。"
           );
    SetRace( "gnome");
    SetGender("female");
    SetRace("human");
    SetHealthPoints(950);
    SetLanguage( "nibelungen",100  );
    SetMaxHealthPoints(950);
    SetMagicPoints(900);
    SetMaxMagicPoints(900);
    SetLevel(17);
    SetStat("wisdom", 40);
    SetSkill("magic attack", 100);
    SetAction(12,
            ({
             "来吧！让我告诉你你的星座运势！",
             "只需60金币就能知道你的星座运势。",
             "我能与平行现实沟通。",
             "我能告诉你敌人的星座运势。",
             "我的精神状态总是很好。"
             })
            );
    SetMorality(-5);
    AddCurrency("gold", random(60));
}

void init() {
    ::init();
    add_action("horoscope", "horoscope");
}

int horoscope(string str) {
    object ob;
    string msg;
    int mag, phy, cost;

    if(!str || str == "me" || str == "myself") ob = this_player();
    else ob = find_player(lower_case(str));
    if(!ob) {
        notify_fail("我找不到"+capitalize(str)+"。\n");
        return 0;
    }
    if(ob == this_player()) cost = 60;
    else cost = 110;
    if(this_player()->query_money("gold") < cost) {
        notify_fail("你没有足够的金币。\n");
        return 0;
    }
    mag = ob->query_spiritual();
    phy = ob->query_physical();
    this_player()->AddCurrency("gold", -cost);
    write("你支付了"+cost+"金币让莫拉为你做今日的占卜。");
    say(this_player()->query_cap_name()+"向莫拉支付了星座运势占卜费用。", this_player());
    switch(mag) {
        case -5:
            if(ob == this_player()) msg = "灵性现实与你的灵魂断开了连接。";
            else msg = "灵性现实与"+ob->query_possessive()+"的灵魂断开了连接。";
            break;
        case -4:
            if(ob == this_player()) msg = "你感觉与灵性现实脱节了。";
            else msg = capitalize(str)+"感觉与灵性现实脱节了。";
            break;
        case -3:
            if(ob == this_player()) msg = "你的灵魂今天特别虚弱。";
            else msg = capitalize(str)+"的灵魂今天特别虚弱。";
            break;
        case -2:
            if(ob == this_player()) msg = "你今天最好不要依赖灵性方面的事情。";
            else msg = capitalize(str)+"今天最好不要依赖灵性方面的事情。";
            break;
        case -1:
            if(ob == this_player()) msg = "你需要集中注意力才能在灵性方面表现出色。";
            else msg = capitalize(str)+"需要集中注意力才能在灵性方面表现出色。";
            break;
        case 0:
            if(ob == this_player()) msg = "今天对你来说是灵性层面上普通的一天。";
            else msg = "今天对"+capitalize(str)+"来说是灵性层面上普通的一天。";
            break;
        case 1:
            if(ob == this_player()) msg = "你只需稍作努力就能在灵性方面表现出色。";
            else msg = capitalize(str)+"只需稍作努力就能在灵性方面表现出色。";
            break;
        case 2:
            if(ob == this_player()) msg = "你今天在魔法方面会做得很好。";
            else msg = capitalize(str)+"今天在魔法方面会做得很好。";
            break;
        case 3:
            if(ob == this_player()) msg = "你的灵性光环今天闪耀得非常强烈。";
            else msg = capitalize(str)+"的灵性光环今天闪耀得非常强烈。";
            break;
        case 4:
            if(ob == this_player()) msg = "你今天有着异常灿烂的灵性光环。";
            else msg = capitalize(str)+"今天有着异常灿烂的灵性光环。";
            break;
        case 5:
            if(ob == this_player()) msg = "今天没有人能阻挡你的魔法。";
            else msg = "今天没有人能阻挡"+ob->query_possessive()+"的魔法。";
            break;
    }
    write(""+msg);
    switch(phy) {
        case -5:
            if(ob == this_player()) msg = "你今天真的应该躺在床上。";
            else msg = capitalize(str)+"今天真的应该躺在床上。";
            break;
        case -4:
            if(ob == this_player()) msg = "你今天感觉相当虚弱。";
            else msg = capitalize(str)+"今天感觉相当虚弱。";
            break;
        case -3:
            if(ob == this_player()) msg = "今天对你的身体来说不是最好的日子。";
            else msg = "今天对"+capitalize(str)+"的身体来说不是最好的日子。";
            break;
        case -2:
            if(ob == this_player()) msg = "你的身体今天会不太舒服。";
            else msg = capitalize(str)+"的身体今天会不太舒服。";
            break;
        case -1:
            if(ob == this_player()) msg = "你的身体今天有点不舒服。";
            else msg = capitalize(str)+"的身体今天有点不舒服。";
            break;
        case 0:
            if(ob == this_player()) msg = "你今天会过得不错。";
            else msg = capitalize(str)+"今天会过得不错。";
            break;
        case 1:
            if(ob == this_player()) msg = "你今天会做得很好。";
            else msg = capitalize(str)+"今天会做得很好。";
            break;
        case 2:
            if(ob == this_player()) msg = "你的体力有些高。";
            else msg = capitalize(str)+"的体力有些高。";
            break;
        case 3:
            if(ob == this_player()) msg = "今天对你来说是身体非常强健的一天。";
            else msg = "今天对"+capitalize(str)+"来说是身体非常强健的一天。";
            break;
        case 4:
            if(ob == this_player()) msg = "你处于极佳的身体状态！";
            else msg = capitalize(str)+"处于极佳的身体状态！";
            break;
        case 5:
            if(ob == this_player()) msg = "在身体方面，你处于罕见的最佳状态。";
            else msg = "在身体方面，"+capitalize(str)+"处于罕见的最佳状态。";
            break;
    }
    write(""+msg);
    return 1;
}
