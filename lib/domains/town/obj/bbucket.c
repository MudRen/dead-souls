#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bin");
    SetId(({"bin","can","dustbin","trash","rubbish"}));
    SetAdjectives(({"metal","small","blue","recycling","trash","garbage","dust"}));
    SetShort("一个回收箱");
    SetLong("这是一个蓝色垃圾桶，标有回收标志。你可以把不需要的东西扔进去。");
    SetMass(274);
    SetBaseCost("silver",50);
    SetMaxCarry(999999);
}

int tidy_up(){
    object *inv;
    inv = all_inventory(this_object());
    foreach(object thing in inv){
        if(thing) thing->eventMove(load_object("/domains/town/room/furnace"));
    }
    return 1;
}

int eventReceiveObject(object ob){
    write("你把东西放进了回收箱。\n");
    call_out((: tidy_up :),1);
    return 1;
}
mixed CanGet(object ob) { return "这个桶纹丝不动。";}

void init(){
}
