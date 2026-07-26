/*    /domains/Ylsrim/room/tower.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960512 
 */ 

#include <lib.h> 
#include <jump.h> 

inherit LIB_ROOM; 
inherit LIB_JUMP; 

int ReadSign() {
    this_player()->more("/domains/town/txt/ylsrim_sign.txt");
    return 1;
}

void create() { 
    room::create();
    SetClimate("indoors");
    SetTown("Ylsrim");
    SetAmbientLight(28);
    SetShort("伊尔斯利姆高塔");
    SetLong("高塔俯瞰着卡利德路。路的南边是永远繁忙的伊尔斯利姆集市。"
            "螺旋楼梯向下通往冒险者大厅的中心。"
            "\n%^RED%^这里有一块告示牌，你可以阅读。%^RESET%^");
    SetItems( ([ ({ "road", "kaliid road" }) :
                "你也许可以从这里跳到路上去。",
                "bazaar" : "看起来很热闹。",
                "sign":"一块告示牌。要阅读它，请输入 'read sign'。",
                "tower" : "你所在的高塔。",
                ({ "stairs", "staircase" }) : "楼梯向下通往大厅的中心。" ]) );
    SetExits( ([ "down" : "/domains/Ylsrim/room/"+ "adv_hall" ]) );
    SetInventory(([
                "/domains/Ylsrim/obj/stargate" : 1,
                ]));
    SetRead("sign", (: ReadSign :) );
    SetCoordinates("1000,1001,1");
} 
void init(){
    ::init();
}
