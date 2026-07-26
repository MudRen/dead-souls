#include <lib.h>

inherit LIB_ROOM;

int PreExit(mixed args...){
    object *livings;
    string duderace = this_player()->GetRace();
    if(sizeof(users()) > 210) return 1;
    livings = get_livings(this_object());
    foreach(object living in livings){
        if(base_name(living) == "/domains/default/vehicle/strider" &&
                previous_object(2) != living ){
            write("行者挡住了你的路。");
            return 0;
        }
    }
    return 1;
}

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("测试实验室走廊东端");
    SetLong("这是测试实验室的主走廊。东边是骑战斗竞技场。走廊从这里向西延伸。");
    SetExits( ([
                "west" : "/domains/default/room/wiz_corr_east2",
                ]) );
    AddExit("east", "/domains/default/virtual/arena/5005,4999", (: PreExit :));
    SetInventory(([
                "/domains/default/vehicle/strider" : 1,
                ]));

    SetProperty("no attack", 1);

}
int CanReceive(object ob) {
    return room::CanReceive();
}

void init(){
    ::init();
}
