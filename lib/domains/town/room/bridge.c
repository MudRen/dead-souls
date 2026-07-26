#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("拱桥");
    SetNightLong("这是一座古老的拱桥，由灯柱照亮。它已经历了更好的时光，但看起来仍然相当稳固。桥上潦草地写着一些奇特的文字。东边是一座城镇，西边是黑暗。有一条未照亮的小路通向桥下。");
    SetDayLong("这是一座古老的拱桥。它已经历了更好的时光，但看起来仍然相当稳固。桥上潦草地写着一些奇特的文字。桥下是一条河流。东边是一座城镇，西边是一片阴暗的森林。有一条小路通向桥下。");
    SetItems( ([
                ({"cracks","surface","bridge"}) : "桥面上有几道裂缝，但看起来年代久远且并不严重……主要是这座建筑经受风雨侵蚀的痕迹。",
                ({"span","river","stream","bank"}) : "下方是一条水流湍急的小河。你也许可以沿着桥爬下去到达下面的河岸。",
                "town" : "东边有一座小镇。",
                ({"writing","scrawl","grafitti","grafitto"}):
                "这里写着涂鸦，笔迹古怪而犹豫，似乎不习惯书写。",
                ({"path","forest","dark forest"}) : "桥的西边有一条通往黑暗森林的小路。"
                ]) );
    SetSkyDomain("town");
    SetExits( ([
                "east" : "/domains/town/room/road2",
                "west" : "/domains/town/room/forest_path1",
                "down" : "/domains/town/room/riverbank",
                ]) );
    SetRead(({"writing","scrawl","grafitti","grafitto"}),"HVMANES EVNT DOMVS");
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
