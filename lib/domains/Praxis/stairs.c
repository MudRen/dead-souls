#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetProperty("no castle", 1);
    SetShort( "修道院楼梯间");
    SetLong(
            "一段螺旋楼梯向上通往修道院阁楼，向下通往地窖。"
            "祈祷区在西边。");
    SetExits(
            (["west" : "/domains/Praxis/monastery",
             "up" : "/domains/Praxis/monk_join",
             "down" : "/domains/Praxis/immortal_hall"]) );
    SetItems(
            (["stairs" : "它们在这座古老的修道院里螺旋上升和下降。"]) );
    SetProperty("no castle", 1);
}
void init(){
    ::init();
}

