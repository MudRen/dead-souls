/*    /domains/Ylsrim/room/adv_hall.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    object ob;

    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("冒险者大厅");
    SetLong("一块公告板立在这间圆形房间的中央，来自各地的冒险者们聚集在此互相交流。"
            "卡利德路在南边。楼梯通向上面的高塔。");
    SetItems( ([ "stairs" : "楼梯盘旋而上，通往俯瞰卡利德路的高塔。",
                "tower" : "楼梯消失在黑暗中，你无法看清太多。" ]));
    SetExits( ([
                "up" : "/domains/Ylsrim/room/"+ "tower",
                "south" : "/domains/Ylsrim/room/"+ "kaliid4" ]) );
    ob = new("/domains/Ylsrim/etc/adv_board");
    ob->set_max_posts(30);
    ob->eventMove(this_object());
}
void init(){
    ::init();
}
