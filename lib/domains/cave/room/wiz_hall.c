#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

protected void create() {
    object ob;
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("创造者大厅");
    SetLong("一个通用的巫师大厅。");
    SetProperty("no attack", 1);
    SetProperty("nopeer",1);
}

int CanReceive(object ob) {
    if(playerp(ob) && !creatorp(ob) && !present("testchar badge",ob)) {
        message("info","Creator staff only, sorry.", ob);
        return 0;
    }
    return ::CanReceive(ob);
}

void init(){
    ::init();
}
