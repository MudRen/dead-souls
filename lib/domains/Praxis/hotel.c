/*    /d/standard/hotel.c
 *    from Nightmare IV
 *    a place to stay for rest and other things
 *    created by Descartes of Borg (what a cutie!)
 *    and Lassondra@Nightmare 940424
 */

#include <lib.h>
#include <clock.h>
#include <daemons.h>

inherit LIB_ROOM;

int query_occupied(int chambre);
string query_key_id(int chambre);
object query_room(int chambre);
void check_out();
private void random_key(int chambre);

nosave private mapping __Rooms;
void create() {
    int x;

    room::create();
    SetProperties( ([ "indoors":1, "light":2, "no castle":1]) );
    SetShort("噩梦旅馆");
    SetLong(
            "你发现自己来到了噩梦世界最有声望的旅馆入口。"
            "地板铺着厚厚的红色地毯，墙壁用金色颜料装饰。"
            "你进来时经过的大型橡木门在你身后，正前方是旅馆的前台。"
            "输入 list 查看可用房间，<rent '类型'> 租赁特定类型的房间。"
           );
    SetItems( ([ "entrance" : "旅馆大厅非常宽敞。看起来这是一家相当昂贵的旅馆。",
                "floor" : "地板覆盖着非常厚的红色地毯，边缘有金色流苏。",
                "carpet" : "地毯状况良好，虽然有些地方有点磨损。"
                "地毯中央有一个金色的旅馆标志。",
                ({ "wall", "walls" }) :
                "墙壁被漆成白色，所有边缘都有金色装饰。",
                ({ "doors", "door" }) :
                "沉重的橡木门上精美地雕刻着旅馆徽章。"
                "经过大量抛光后，门在光线中闪闪发亮。",
                "desk" : "前台也是橡木制的，位于大厅后方。",
                "hotel" : "你在噩梦旅馆里。"
                ])
            );
    SetExits( ([
                "north" : "/domains/Praxis/hall",
                "west" : "/domains/Praxis/n_centre1.c",
                ]) );
    //    if(!event_pending(this_object())) {
    //        if((x=hour(time())) > 9) x= (9+(20-x))*HOUR;
    //        else x = HOUR*(9-x);
    //        event("check_out", x, 0, 1);
    //    }
    //    SetNoClean(1);
    //    __Rooms = allocate_mapping(10);
    //    this_object()->check_out();
}
void reset() {
    int x;

    room::reset();
    if(present("receptionist")) return;
    new("/domains/Praxis/obj/mon/receptionist")->move(this_object());
}
void set_occupied(int x) { __Rooms[x]["occupied"] = 1; }
int query_occupied(int chambre) {
    return __Rooms[chambre]["occupied"];
}
string query_key_id(int chambre) {
    return __Rooms[chambre]["key id"];
}

object query_room(int x) {
    return load_object(sprintf("/domains/Praxis/inn%d", x));
}
void check_out() {
    object *tmp;
    int i, j;

    if(previous_object() != this_object() &&
            base_name(previous_object()) != EVENTS_D) return;
    for(i=1; i<11; i++) {
        __Rooms[100+i] = ([ "occupied":0, "key id": random_key(100+i) ]);
        j = sizeof(tmp = livings() & all_inventory(query_room(100+i)));
        while(j--) {
            message("my_action", "退房时间到了！\n接待员催促你到大厅。", tmp[j]);
            tmp[j]->eventMoveLiving("/domains/Praxis/hotel", "out");
        }
    }
}
string random_key(int chambre) {
    return sprintf("praxishotel%d%d", chambre, random(100));
}
void init(){
    ::init();
}
