inherit "/lib/std/room";

void create() {
    ::create();
    SetShort( "隐藏处");
    SetLong( "东西藏在这里。");
    SetProperty("storage room", 1);
}
void init(){
    ::init();
}
