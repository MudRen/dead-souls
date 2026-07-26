/*    /domains/Ylsrim/room/kaliid7.c
 *    From the Dead Souls Mud Library
 *    An example simple room with an item in it
 *    Created by Descartes of Borg 970101
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("伊尔斯利姆西边边缘");
    SetLong("卡利德路在这里到达西端，伊尔斯利姆消失在沙漠中。"
            "在东边不远处，你可以看到当地银行的所在。");
    SetSkyDomain("town");
    AddItem(({ "bank", "bank of ylsrim" }), "伊尔斯利姆的当地银行。它有一面土坯墙。", ({ "ylsrim" }));
    AddItem("desert", "一片巨大的沙漠环绕着伊尔斯利姆，使它看起来如此脆弱。");
    AddItem("road", "伊尔斯利姆的主要街道。", "kaliid");
    SetInventory(([ "/domains/Ylsrim/weapon/stick" : 1 ]));
    SetExits( ([ "east" : "/domains/Ylsrim/room/"+ "kaliid6",
                "west" : "/domains/Ylsrim/room/"+ "sand_room" ]));
}
void init(){
    ::init();
}
