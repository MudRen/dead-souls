/*    /domains/Ylsrim/room/fighter.c
 *    from the Dead Souls Object Library
 *    created by Descartes of Borg 960512
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetNoClean(1);
    SetTown("Ylsrim");
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("战士大厅内部");
    SetLong("战士们聚集在这里饮酒、吹嘘和训练。他们还会在这里为彼此留下有用的武器和物品，"
            "因为他们知道这里是世界重置时物品不会丢失的庇护所。");
    SetExits( ([
                "south" : "/domains/Ylsrim/room/"+ "fighter_hall",
                ]) );
    SetInventory( ([
                "/domains/Ylsrim/obj/cask" : ({ 900, 1 }),
                "/domains/Ylsrim/npc/segata" : ({ 300, 1 }),
                ]) );
    SetDoor( "south", "/domains/Ylsrim/etc/fighter_door.c");
    SetNoClean(1);
    SetPersistent(1);
    RestoreObject();
}

void init(){
    ::init();
}
