#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("公馆花园");
    SetLong("这里曾经是美丽而简单的花园，现在只剩下残骸。现在杂草丛生，很明显，觅食的动物很久以前就吃掉了曾经在这里生长的娇嫩花朵和蔬菜。园丁的小屋在北边。");
    SetItems(([
                ({ "flowers", "vegetables", "flowers and vegetables" }) : "如果它们曾经在这里，现在肯定已经不在了。",
                ({ "shack", "wooden shack" }) : "北边有一个破旧的木制小屋。",
                "garden" : "杂草和泥土的混乱。",
                ]));
    SetSkyDomain("town");
    SetExits( ([
                "east" : "/domains/town/room/mansion_ext",
                "north" : "/domains/town/room/shack"
                ]));
    SetEnters( ([
                "shack" : "/domains/town/room/shack",
                ]) );
}
void init(){
    ::init();
}
