/*    /domains/Ylsrim/room/weaponry.c
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
    SetAmbientLight(28);
    SetShort("伊尔斯利姆武器店");
    SetLong((: CheckOpen :));
    SetItems( ([ ({ "case", "cases" }) : (: CheckItem :),
                "bazaar" : "来自各地的人们四处游荡，寻找便宜货。" ]) );
    SetObviousExits("east");
    SetExits( ([ "east" : "/domains/Ylsrim/room/"+ "bazaar" ]) );
    SetInventory( ([ "/domains/Ylsrim"+ "/npc/shiela" : 1 ]) );
}

string CheckOpen(string str) {
    object ob;

    ob = present("vendor");
    if( query_night() ) {
        if( ob ) ob->eventDestruct();
        return ("武器店的展柜已经空了，因为武器店已经打烊了。"
                "集市在东边。");
    }
    if( !ob )
        return ("新鲜的鲜血溅满了曾经陈列着武器的破碎展柜。"
                "武器已经不见了，店主显然被谋杀了。"
                "你只能摇摇头，从东边离开。");
    return ("密封的展柜里陈列着武器，展示了当地店主的商品。"
            "她从前来出售战利品或购买装备继续冒险的冒险者手中"
            "买卖各种武器。出口在东边。");
}

string CheckItem(object ob) {
    if( query_night() ) return "展柜是空的。";
    else if ( present("vendor") ) return "展柜里摆满了武器。";
    else return "展柜已经破碎，沾满了鲜血。";
}

void init(){
    ::init();
}
