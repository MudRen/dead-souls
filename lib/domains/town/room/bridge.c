#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("驼背桥");
    SetNightLong("这是一座古老的驼背桥，由路灯照亮。它曾经辉煌过，但仍然相当稳固。桥上有一些奇怪的文字。东边是小镇，西边是黑暗。有一条没有照明的路径通向桥下。");
    SetDayLong("这是一座古老的驼背桥。它曾经辉煌过，但仍然相当稳固。桥上有一些奇怪的文字。桥横跨下方的小河。东边是小镇，西边是黑暗的森林。有一条小路通向桥下。");
    SetItems( ([
                ({"cracks","surface","bridge"}) : "桥面上有一些裂缝，但它们看起来陈旧且微小...主要是这座结构经受住自然元素考验多长时间的标志。",
                ({"span","river","stream","bank"}) : "下方是一条小河，水流湍急有力。你可能可以爬下桥到达下方的河岸。"
                "town" : "东边有一个小镇。"
                ({"writing","scrawl","grafitti","grafitto"}):
                "这里写着涂鸦，字迹奇怪且不确定，好像不习惯写字的努力。"
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
