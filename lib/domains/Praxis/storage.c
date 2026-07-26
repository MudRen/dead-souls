inherit "/lib/std/room";

void create() {
    int i;
    ::create();
    SetShort( "冒险者杂货储藏室");
    SetLong( "霍勒斯在这里存放武器等物品。");
    SetExits( 
            (["south" : "/domains/Praxis/supply"]) );
    new("/domains/Praxis/obj/misc/vial")->move(this_object());
    //for( i=0 ; i<5 ; i++ )
    //new("/realms/nialson/newspaper/paper")->move(this_object());
}
void init(){
    ::init();
}
