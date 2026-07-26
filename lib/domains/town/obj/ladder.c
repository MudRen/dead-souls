#include <lib.h>
#include <climb.h> // defines CLIMB_DOWN

//inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_ITEM;
inherit LIB_CLIMB; // This makes it climbable

int LadderClimb(){
    if(base_name(environment()) == "/domains/town/room/mansion_ext"){
        write("你爬上梯子，通过二楼的窗户进入了大宅。");
        eventClimb(this_player(),CLIMB_UP,"/domains/town/room/mansion_uhall1");
        return 1;
    }
    if(base_name(environment()) == "/domains/amigara/room/passage1"){
        write("你爬上梯子到达了洞穴的更高层。");
        eventClimb(this_player(),CLIMB_UP,"/domains/amigara/room/cave");
        return 1;
    }
    write("这把梯子在这里似乎无法使用。");
    return 0;
}

protected void create() {
    ::create();
    SetKeyName("ladder");
    SetId("ladder");
    SetAdjectives(({"short","wood","wooden"}));
    SetShort("一个梯子");
    SetLong("这是一把标准的木梯，适合攀爬。");
    SetClimb( (: LadderClimb :) , CLIMB_UP);
    SetCanClimbCarried(0);
    SetMass(100);
    SetBaseCost("silver", 10);
}

void init(){
    ::init();
}
