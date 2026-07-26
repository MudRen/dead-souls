#include <lib.h>
#include <position.h>

inherit LIB_BARKEEP;

mixed NoKill(object attacker);

protected void create() {
    barkeep::create();
    SetKeyName("lars");
    SetId( ({ "lars", "owner", "barkeep", "bartender", "keeper" }) );
    SetShort("酒馆老板拉尔斯");
    SetLevel(1);
    SetLong("拉尔斯是当地酒馆的老板，这是镇中心一家古老而著名的"+
            "饮酒场所。他是一个低调的家伙，相当快活。");
    SetMenuItems(([
                ({ "espresso", "imported espresso" }) : "/domains/town/meals/espresso",
                ({ "sandwich", "ham sandwich" }) : "/domains/town/meals/ham_sand",
                ({ "spring water", "water" }) : "/domains/town/meals/water",
                ({ "first class ale", "ale" }) : "/domains/town/meals/ale",
                ({ "regular coffee", "coffee" }) : "/domains/town/meals/coffee",
                ({ "firebreather" }) : "/domains/town/meals/fire",
                ({ "special of the house", "special" }) : "/domains/town/meals/special",
                ]));
    SetGender("male");
    SetMorality(40);
    SetRace("human");
    AddCurrency("electrum", random(200));
    SetSkill("bargaining", 1);
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
    SetAttackable( (: NoKill :) );
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}
void init(){
    ::init();
}

mixed NoKill(object attacker){
    if(attacker->GetTown() == "Town"){
        return "拉尔斯就像你最喜欢的叔叔。你发现自己无法攻击他。";
    }
    else {
        tell_object(attacker,"拉尔斯轻松地挡开了你的攻击，把你踢出了门外。");
        say("拉尔斯轻松地挡开了"+attacker->GetName()+"的攻击，"+
                "把"+objective(attacker)+"踢出了门外。");
        tell_room("/domains/town/room/road",attacker->GetName()+"从酒馆里飞了出来，"+
                "一屁股摔在了路上。");
        attacker->eventMove("/domains/town/room/road");
        attacker->eventDescribeEnvironment();
        attacker->SetPosition(POSITION_SITTING);
        return "";
    }
}
