/*    /domains/Ylsrim/room/armory.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951023
 */

#include <lib.h>
#include <dirs.h>

inherit LIB_ROOM;

string CheckOpen(string str);
string CheckItem(string str);

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("indoors");
    SetAmbientLight(27);
    SetShort("伊尔斯利姆防具店");
    SetLong((: CheckOpen :));
    SetItems( ([ ({ "case", "cases" }) : (: CheckItem :),
                "bazaar" : "来自各地的人们四处游荡，寻找便宜货。" ]) );
    SetObviousExits("west");
    SetExits( ([ "west" : "/domains/Ylsrim/room/"+ "bazaar" ]) );
    SetInventory( ([ "/domains/Ylsrim"+ "/npc/max" : 1 ]) );
}

string CheckOpen(string str) {
    object ob;

    ob = present("vendor");
    if( query_night() ) {
        if( ob ) ob->eventDestruct();
        return ("防具店的展柜已经空了，因为防具店已经打烊了。"
                "集市在西边。");
    }
    if( !ob )
        return ("新鲜的鲜血溅满了曾经陈列着防具的破碎展柜。"
                "防具已经不见了，店主显然被谋杀了。"
                "你只能摇摇头，从西边离开。");
    return ("密封的展柜里陈列着防具，展示了当地店主马克斯的商品。"
            "他从前来出售战利品或购买装备继续冒险的冒险者手中"
            "买卖各种防具。出口在西边。");
}

string CheckItem(string str) {
    if( query_night() ) return "展柜是空的。";
    else if ( present("vendor") ) return "展柜里摆满了防具。";
    else return "展柜已经破碎，沾满了鲜血。";
}

void init(){
    ::init();
}
