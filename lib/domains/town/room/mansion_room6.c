#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("仆人宿舍");
    SetLong("你在值班员工的简朴宿舍里。"
            "从缺乏个人物品来看，"
            "仆人似乎轮流值班。");
    SetInventory( ([
                "/domains/town/obj/cot" :1,
                ]) );
    SetExits( ([
                "east" : "/domains/town/room/mansion_uhall3"
                ]) );

    SetDoor("east", "/domains/town/doors/m6.c");

}
void init(){
    ::init();
}
