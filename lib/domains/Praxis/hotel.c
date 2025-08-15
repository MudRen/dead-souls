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
    SetShort("梦魇旅店");
    SetLong(
            "你发现自己站在最负盛名的梦魇旅店入口处。"
            "地板上铺着豪华的红地毯，墙壁镶着金色的装饰条。"
            "你身后是进入时经过的巨大橡木门，"
            "正前方就是旅店的前台。"
            "输入list查看可用房间，输入<rent 'type'>租用特定类型的房间。"
           );
    SetItems( ([ "entrance" : "旅店的大堂非常宽敞。看起来这是相当昂贵的旅店。",
                "floor" : "地板上覆盖着非常厚的红地毯，边缘有金色流苏。",
                "carpet" : "地毯状况良好，虽然有些地方有些磨损。中间有一个金色的旅店标志。",
                ({ "wall", "walls" }) :
                "墙壁被漆成白色，所有边缘都有金色装饰条。",
                ({ "doors", "door" }) :
                "沉重的橡木门上雕刻着精美的旅店徽章。由于大量抛光，门在光线下闪闪发光。",
                "desk" : "前台也是由橡木制成，位于大堂后面。",
                "hotel" : "你在梦魇旅店里。"
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
            message("my_action", "Check out time!\nThe receptionist "
                    "hurries you out into the lobby.", tmp[j]);
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
