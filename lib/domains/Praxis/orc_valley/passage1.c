inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetShort( "黑暗的通道");
    SetLong(
            "你身处兽人堡垒内部的一条黑暗通道中。");
    SetItems(
            (["passage" :  "你几乎什么都看不见。"]) );
    SetExits( 
            (["east" : "/domains/Praxis/orc_valley/chamber1",
             "west" : "/domains/Praxis/orc_valley/open"]) );
}

void init(){
    ::init();
}
