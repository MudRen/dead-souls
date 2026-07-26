#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("动物园走廊");
    SetLong("这条短走廊通向下方的动物园。这条走廊是专门设计来驱赶NPC的，以防止下面的生物逃跑。主测试实验室走廊在北边。");
    SetExits( ([
                "north" : "/domains/default/room/wiz_corr_east",
                "down" : "/domains/default/room/menagerie.c",
                ]) );

    SetInventory(([
                ]));

}
int CanReceive(object ob) {
    //if(living(ob) && !creatorp(ob) && !present("testchar badge",ob)) {
    //	message("info","Creator staff only, sorry.", ob);
    //	return 0;
    //   }
    if(living(ob) && !interactive(ob)){
        message("info","不允许NPC进入，抱歉。", ob);
        return 0;
    }
    return room::CanReceive(ob);
}

void init(){
    ::init();
}
