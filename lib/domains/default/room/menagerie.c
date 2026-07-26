#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("动物园");
    SetLong("这是一个神奇的区域，包含了创造者们可以用于他们区域的各种种族的示例。通常这些生物不会像这样挤在一起，但强大的魔法将它们束缚在这里，以便MUD工作人员可以分析和测试它们。南边、东边和西边还有更多生物。");
    SetExits( ([ 
                "south" : "/domains/default/room/menagerie_south",
                "east" : "/domains/default/room/menagerie_e",
                "west" : "/domains/default/room/menagerie_w",
                "up" : "/domains/default/room/wiz_corr_south",
                ]) );
    SetInventory(([
                "/domains/default/npc/horse" : 1,
                "/domains/default/npc/bird" : 1,
                "/domains/default/npc/elephant" : 1,
                "/domains/default/npc/bat" : 1,
                "/domains/default/npc/newt" : 1,
                "/domains/default/npc/lynx" : 1,
                "/domains/default/npc/deer" : 1,
                "/domains/default/npc/spider" : 1,
                "/domains/default/npc/bear" : 1,
                "/domains/default/npc/dryad" : 1,
                "/domains/default/npc/rat" : 1,
                "/domains/default/npc/zookeeper" : 1,
                "/domains/default/npc/cow" : 1,
                "/domains/default/npc/centaur" : 1,
                "/domains/default/npc/gnome" : 1,
                "/domains/default/npc/moth" : 1,
                "/domains/default/npc/gecko" : 1,
                ]));

}
void init(){
    ::init();
}
