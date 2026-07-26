#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("村庄马厩");
    SetLong("这里是村庄马厩。镇民们来这里把坐骑交给当地的马女英格丽德照料。这里井然有序，虽然有点臭味，但显然英格丽德经营得很专业。");
    SetItems(([
                ({ "building", "schoolhouse", "school", "village school", "village schoolhouse" }) : "一座小巧但维护良好的木制建筑，镇民和他们的孩子来这里获取知识。",
                ({ "building", "buildings" }) : "供人类居住的建筑结构。",
                ]));
    SetProperties(([
                "no attack" : 1,
                ]));
    SetInventory(([
                "/domains/town/npc/ingrid" : 1,
                "/domains/town/npc/horse" : 1,
                ]));
    SetExits(([
                "north" : "/domains/town/room/vill_road4",
                ]));

    SetEnters( ([ 
                ]) );

}
void init(){
    ::init();
}
