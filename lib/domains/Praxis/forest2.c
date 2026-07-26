#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("no castle", 1);
    SetShort("北方森林中的一条小径");
    SetLong(
            "这条小径带你越来越深入北方森林的深处。森林变得更加茂密，"
            "树木表明这里是森林中较古老的区域。树叶如此茂密，"
            "几乎没有光线能穿透。向北继续深入森林，向南带你回到"
            "主村庄。东边你可以看到另一条小路延伸出去。");
    SetItems(
            (["footpath" : "穿过巨大北方森林的小径。",
             "forest" : "北方森林。人迹罕至。",
             ({ "trees", "tree" }) : "树木巨大而令人生畏。",
             "foliage" : "树叶是深绿色的。"
             ]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "south" : "/domains/Praxis/forest1",
                "north" : "/domains/Praxis/forest3",
                ]) );
}
void init(){
    ::init();
}
