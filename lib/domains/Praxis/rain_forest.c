inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "雨林深处");
    SetLong("你在热带雨林深处。东边有一间小屋。");
    SetItems(
            ([ "forest" : "一片远离文明的潮湿丛林。"]) );
    SetSkyDomain("town");
    SetExits( ([
                "southwest" : "/domains/Praxis/jungle",
                "east" : "/domains/Praxis/rogue_join.c",
                ]) );
}
void init(){
    ::init();
}
