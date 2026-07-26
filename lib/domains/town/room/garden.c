#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("庄园花园");
    SetLong("这里曾经是一座美丽而简朴的花园的遗迹。如今杂草丛生，显然觅食的动物早已吃光了曾经生长在这里的娇嫩花卉和蔬菜。园丁的小屋在北边。");
    SetItems(([
                ({ "flowers", "vegetables", "flowers and vegetables" }) : "如果它们曾经存在过，那现在肯定已经不在了。",
                ({ "shack", "wooden shack" }) : "北边有一座破旧的木屋。",
                "garden" : "一片杂草和泥土的混乱景象。",
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
