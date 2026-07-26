#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetSmell("default", "建筑物散发着腐朽的气味。");
    SetListen("default", "组成地板的木板在你的体重下嘎吱作响。");
    SetShort( "一座破败的建筑");
    SetLong(
            "破损的木板和腐烂的茅草让这个地方非常危险，不宜行走。"
            "患病啮齿动物的吱吱声告诉你这里已不再由人形生物管理，"
            "但各处的零星证据表明最近有人形生物经过。"
            "小巷在北边。");
    SetItems(
            (["board" : "它因暴露在天气中而腐烂。",
             "boards" : "你不想依靠它们来支撑。",
             "thatch" : "它曾经构成了建筑物的屋顶，但现在不再了。",
             "roof" : "一片腐烂茅草的拼凑。",
             "evidence" : "留下的灰尘尚未安定。",
             "dust" : "看起来有些地方灰尘还没落定多久。",
             "foo" : "你说的foo是什么意思？"]) );
    SetExits( 
            (["north" : "/domains/Praxis/alley2"]) );
}

void reset() {
    object rat;

    ::reset();
    if(!present("rat")) {
        rat = new("/lib/npc");
        rat->SetKeyName("rat");
        rat->SetId( ({ "rat", "filthy rat", "a filthy rat" }) );
        rat->SetLevel(1);
        rat->SetShort( "一只肮脏的老鼠");
        rat->SetLong("一只令人厌恶的小啮齿动物。");
        rat->SetRace( "rodent");
        rat->SetCurrency("silver", random(10));
        rat->SetHealthPoints(60+random(10));
        rat->SetMorality(-1);
        rat->move(this_object());
    }
    if(!present("torch")) 
        new("/domains/town/obj/torch")->move(this_object());
}
void init(){
    ::init();
}
