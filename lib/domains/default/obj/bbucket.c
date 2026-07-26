#include <lib.h>
#include ROOMS_H

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bin");
    SetId(({"bin","can","dustbin","trash","rubbish"}));
    SetAdjectives(({"metal","small","blue","recycling","trash","garbage","dust"}));
    SetShort("一个回收 bin");
    SetLong("这是一个蓝色垃圾桶， marked with the letters \"/dev/null\"。");
    SetMass(200);
    SetBaseCost("silver",50);
    SetMaxCarry(999999);
}

int tidy_up(){
    object *inv;
    inv = all_inventory(this_object());
    foreach(object thing in inv){
        if(thing) thing->eventMove(ROOM_FURNACE);
    }
    return 1;
}

int eventReceiveObject(object ob){
    write("你将物品放入回收 bin。\n");
    call_out((: tidy_up :),1);
    return 1;
}
mixed CanGet(object ob) { return "这个桶纹丝不动。";}

void init(){
    ::init();
}
