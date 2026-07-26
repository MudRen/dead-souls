/*    /domains/Ylsrim/room/bank_room.c
 *    From the Dead Souls Mud Library
 *    An example of a room with an item that allows jumping and climbing
 *    Created by Descartes of Borg 961010
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("伊尔斯利姆银行屋顶");
    SetDayLong("站在伊尔斯利姆银行滚烫的土坯屋顶上，你几乎可以看到整个沙漠小镇的全貌。"
            "银行南侧的墙壁足够粗糙，可以攀爬下去到卡利德路。"
            "建筑其他几面的墙壁实在太光滑了，无法攀爬下去。你也许还可以跳到路上去。");
    SetNightLong("从银行屋顶这个制高点望去，伊尔斯利姆的灯光看起来很美。");
    AddItem("adobe", "墙壁和屋顶都是用这种材料建造的。");
    // this is the wall that can be climbed down
    AddItem(new("/domains/Ylsrim/etc/roof_wall"));
    // this is the road that people can jump into
    AddItem(new("/domains/Ylsrim/etc/road"));
    // this is the roof people can jump from
    AddItem(new("/domains/Ylsrim/etc/roof"));
}
void init(){
    ::init();
}
