#include <lib.h>
inherit LIB_ROOM;

int found;
string SearchFun(){
    string result;
    if(found == 0){
        object ob = new("/domains/town/obj/safe_key");
        result="你搜索房间，找到了一把复杂的钥匙！";
        tell_room(this_object(),this_player()->GetName()+
                "搜索了房间，似乎找到了什么东西。",
                ({ this_player() }) );
        if(ob->eventMove(this_player()))
            ob->eventMove(this_object());
        found = 1;
        return result;
    }
    return "你什么也没找到。";
}
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园西客房");
    SetLong("你在庄园楼上的西客房里。房间装饰和家具都很豪华。看起来已经很久没有人打扫这里了。");
    SetExits( ([
                "east" : "/domains/town/room/mansion_uhall1"
                ]) );
    SetItems( ([
                ({"here","area","place","room"}) : "庄园里的一间客房。",
                "dust" : "这里有一些灰尘，在这样好的地方，灰尘比预期的要多一些。",
                ]) );
    SetInventory(([
                "/domains/town/obj/gbed" : 1,
                ]) );
    SetSearch( ([ "default"  : (: SearchFun :)  ]) );
    found = 0;

    SetDoor("east", "/domains/town/doors/m2.c");

}
void init(){
    ::init();
    AddSearch( ({"here","area","place","room"})  , (: SearchFun :)  );
}
