#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("no castle", 1);
    SetShort( "北方森林深处");
    SetLong(
            "小径突然急转向西北，继续深入北方森林。"
            "小径正被大量灌木丛覆盖。在角落里，你发现了一个"
            "通往地底深处的神秘黑暗洞穴。一条小路向西北延伸，"
            "向南则回到森林外面。");
    SetItems(
            ([
             ({"path", "footpath"}) : "穿过北方森林的小径。",
             "forest" : "北方森林是一个非常黑暗和邪恶的地方。",
             "undergrowth" : "灌木丛正在慢慢吞噬小径。",
             "cavern" : "它神秘的入口召唤你进入。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "south" : "/domains/Praxis/forest2",
                "down" : "/domains/Praxis/kataan_join",
                ]) );
}

void init(){
    ::init();
}
