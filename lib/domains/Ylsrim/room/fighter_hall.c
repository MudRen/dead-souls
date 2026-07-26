/*    /domains/Ylsrim/room/fighter_hall
 *    from the Dead Souls Object Library
 *    created by Descartes of Borg 960512
 */

#include <lib.h>

inherit LIB_ROOM;

int CheckFighter(string dir);

protected void create() {
    room::create();
    SetNoClean(1);
    SetTown("Ylsrim");
    SetClimate("indoors");
    SetAmbientLight(27);
    SetShort("战士大厅");
    SetLong("战士大厅建于许多世代之前，作为所有经过伊尔斯利姆的战士的聚会场所。"
            "此外，它也是招募新战士加入行列的地方。"
            "一扇华丽的橡木门矗立在北边。");
    SetExits( ([
                //"north" : ({ "/domains/Ylsrim/room/"+ "fighter", (: CheckFighter :) }),
                "north" : "/domains/Ylsrim/room/fighter",
                "south" : "/domains/Ylsrim/room/kaliid5",
                ]) );
    SetInventory(([ "/domains/Ylsrim/npc/roshd" : 1 ]));
    SetItems( ([
                ({ "meeting","room","hall","fighter hall" }) :
                "新冒险者可以在这里成为战士。",
                ]) );
    SetDoor( "north", "/domains/Ylsrim/etc/fighter_door");
    //SetListen("default","Sounds of old veterans recalling battles of "
    //        "the past can be heard being told.");
}

int CheckFighter(string dir) {
    object ob;
    if( this_player()->ClassMember("fighter") ||
            creatorp(this_player()) ) return 1;
    if( ob = present("fighter", this_object()) ) {
        ob->eventForce("speak 我不能让你进入伊尔斯利姆伟大战士的大厅");
        return 0;
    }
    else return 1;
}

void init(){
    ::init();
}
