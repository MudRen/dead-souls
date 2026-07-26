#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("建造者休息室");
    SetLong("这是一个舒适的休息室，建造者们可以在这里聚集讨论他们的工作，并在留言板上互相留言。冒险者公会在北边。");
    SetProperty("no attack", 1);
    SetProperty("nopeer",1);
    ob = new("/lib/bboard");
    ob->SetKeyName("chalkboard");
    ob->SetId( ({ "board", "chalkboard", "dusty board", "dusty chalkboard" }) );
    ob->set_board_id("builder_board");
    ob->set_max_posts(30);
    ob->SetShort("一个布满灰尘的黑板");
    ob->eventMove(this_object());
    SetItems( ([
                ({"sign"}) : "一个你可以阅读的指示牌。",
                ]) );
    SetExits( ([ 
                "north" : "/domains/town/room/adv_guild",
                ]) );
    SetInventory(([
                "/domains/default/obj/couch" : 1,
                ]));
}

int CanReceive(object sneak) {
    object *living_stack = get_livings(sneak);
    if(!living_stack || !arrayp(living_stack)) living_stack = ({ sneak });
    foreach(object ob in living_stack){
        if(playerp(ob) && !builderp(ob) && !present("testchar badge",ob) &&
                !member_group(ob,"TEST")) {
            message("info","仅限工作人员使用，抱歉。", ob);
            return 0;
        }
    }
    return 1;
}

void init(){
    ::init();
}
