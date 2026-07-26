/*    /domains/Ylsrim/room/kaliid6.c
 *    From the Dead Souls Mud Library
 *    An example of a room with an object that allows climbing
 *    Created by Descartes of Borg 961010
 */

#include <lib.h>
#include <climb.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("卡利德路银行南侧");
    SetLong("卡利德路向东西方向延伸，横跨伊尔斯利姆，一望无际。"
            "路北侧粗糙的墙壁看起来像是伊尔斯利姆银行特有的土坯墙。"
            "沿着银行墙壁向西，你可以看到卡利德路与另一条路交汇。");
    SetSkyDomain("town");
    AddItem(({ "bank", "bank of ylsrim" }), "伊尔斯利姆的当地银行。它有一面布满孔洞的土坯墙。", ({ "ylsrim" }));
    AddItem("road", "伊尔斯利姆的主要街道。", "kaliid");
    AddItem("holes", "你也许可以利用这些孔洞攀爬墙壁。");
    // here is the thing that can be climbed, have a look at it!
    AddItem(new("/domains/Ylsrim/etc/wall"));
    SetExits( ([ "east" : "/domains/Ylsrim/room/"+ "kaliid5",
                "west" : "/domains/Ylsrim/room/"+ "kaliid7" ]));
}
void init(){
    ::init();
}
