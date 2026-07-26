inherit "/lib/std/room";

void create() {
    ::create();
    SetShort( "冒险者杂货储藏室");
    SetLong( "霍勒斯在这里存放武器等物品。\n");
    SetExits( (["south" : "/domains/Praxis/supply"]) );
}
void init(){
    ::init();
}
