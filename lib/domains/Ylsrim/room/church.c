/*    /domains/Ylsrim/room/church
 *    From the Dead Souls Mud Library
 *    An example of a religious class hall
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>

inherit LIB_ROOM;

int CheckPriest(string dir) {
    object ob;

    if( this_player()->ClassMember("cleric") || creatorp(this_player()) ) {
        return 1;
    }
    if( ob = present("cleric", this_object()) ) {
        ob->eventForce("speak 我不能让你进入这些神圣的房间。");
        return 0;
    }
    else {
        return 1;
    }
}

protected void create() {
    room::create();
    SetNoClean(1);
    SetTown("Ylsrim");
    SetClimate("indoors");
    SetAmbientLight(27);
    SetShort("伊尔斯利姆教堂");
    SetLong("昏暗的蜡烛发出足够的光芒，照亮了这座简朴的达林教教堂。"
            "达林教徒来这里祈祷，其他人则来皈依达林教。");
    AddItem("candle", "蜡烛看起来发出的光并不多，但教堂非常明亮。", ({ "dim" }));
    AddItem(new("/domains/Ylsrim/etc/church_button"));
    SetExits(([ 
                "south" : "/domains/Ylsrim/room/"+ "kaliid3"]));
    SetDoor("south", "/domains/Ylsrim/etc/church_door");
    SetInventory(([ "/domains/Ylsrim/npc/priest" : 1 ]));
}
void init(){
    ::init();
}
