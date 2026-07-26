#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "金融区外");
    SetLong(
            "向东通往普拉克西斯郊外的乡村地带，这条无名土路"
            "几乎无人行走。普拉克西斯的商业区在西边。");
    SetItems(
            (["road" : "向东的路暂时被封锁了。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "west" : "/domains/Praxis/s_centre3",
                ]) );
}
void init(){
    ::init();
}
