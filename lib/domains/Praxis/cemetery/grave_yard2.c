#include <lib.h>
inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "墓地入口");
    SetLong(
            "你进入了一座古老、声名狼藉的墓地。有几座新坟，"
            "但大多数都非常古老且无人打理。你看到坟墓上有一块"
            "破裂的大理石墓碑。");
    SetItems(
            (["depths" : "你向下望进梅丽莎的坟墓，看到一团旋转的白色薄雾。",
             "haze" : "薄雾像活物一样移动，有时呈现出女性的形态。",
             "haziness" : "朦胧的雾气不断旋转，覆盖着坟墓。",
             "depression" : "凹陷是由于坟墓上的土壤下沉造成的。有薄雾覆盖着。",
             "headstone" : "一块古老的墓碑，也许是第一块。除了梅丽莎·普拉克西斯的名字外，其他文字已经无法辨认。",
             "graves" : "这里的大多数坟墓都杂草丛生且无人打理。你站在一座非常破旧、塌陷的坟墓旁边。",
             "cemetery" : "普拉克西斯的居民安葬在那里。看起来阴森恐怖。",
             "grave" : "你低头看着梅丽莎的坟墓。你在坟墓因岁月而塌陷的深处看到了一种奇怪的朦胧感。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["west" : "/domains/Praxis/cemetery/grave_yard",
             "northeast" : "/domains/Praxis/cemetery/grave_yard6",
             "east" : "/domains/Praxis/cemetery/grave_yard5",
             "southeast" : "/domains/Praxis/cemetery/grave_yard4",
             "south" : "/domains/Praxis/cemetery/grave_yard3",
             "down" : "/domains/Praxis/cemetery/grave_yard7",
             "north"	 : "/domains/Praxis/cemetery/grave_yard8"]) );
}
void init(){
    ::init();
} 
