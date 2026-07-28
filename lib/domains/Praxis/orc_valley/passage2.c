inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indooors", 1);
    SetShort( "黑暗的通道");
    SetLong(
            "你身处兽人堡垒内部的一条黑暗通道中。");
    SetItems(
            (["passage" : "你几乎什么都看不见。"]) );
    SetExits( 
            (["west" : "/domains/Praxis/orc_valley/chamber2",
             "east" : "/domains/Praxis/orc_valley/open"]) );
}
void init(){
    ::init();
}
