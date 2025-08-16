#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("医疗师公会储藏室");
    SetLong("这个空房间是公会存放杂物的地方。");
    SetInventory(([
                "/domains/town/meals/claritin" : 20,
                "/domains/town/obj/slip_heal" : 100,
                "/domains/town/obj/slip_regenerate" : 10,
                "/domains/town/obj/slip_excise" : 10,
                "/domains/town/meals/potion_antidote" : 20,
                ]));
    SetExits( ([ 
                ]) );

}
int CanReceive(object sneak) {
    object *living_stack = get_livings(sneak);
    if(!living_stack || !arrayp(living_stack)) living_stack = ({ sneak });
    foreach(object ob in living_stack){
        if(living(ob) && !creatorp(ob) &&
                !member_group(ob,"TEST")) {
            message("info","储藏室仅限公会官员进入。", ob);
            return 0;
        }
    }
    return 1;
}

void init(){
    ::init();
}
