#include <lib.h>
inherit LIB_ROOM;

int found;
string SearchFun(){
    string result;
    if(found == 0){
        object ob = new("/domains/town/obj/safe_key");
        result="你搜索房间并找到了一把复杂的钥匙！";
        tell_room(this_object(),this_player()->GetName()+ 
                " 搜索房间并找到了什么东西 ",
                ({ this_player() }) );
        if(ob->eventMove(this_player()))
            ob->eventMove(this_object());
        found = 1;
        return result;
    }
    return "你没发现什么特别的东西。";
}
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆西客房");
你在公馆的楼上西客房里。房间布置豪华，家具精美。看起来这里很久没有人打扫了。
    SetExits( ([
                "east" : "/domains/town/room/mansion_uhall1"
                ]) );
    SetItems( ([ 
                ({"here","area","place","room"}) : "公馆里的客房。",
                "dust" : "这里有些灰尘，比这种好地方应有的要多一点。"
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
