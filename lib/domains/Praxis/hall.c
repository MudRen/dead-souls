inherit "/lib/std/room";

void create() {
    ::create();
    SetProperties( ([ "light" : 1, "no castle" : 1 ]) );
    SetShort( "噩梦旅馆" );
    SetLong( "走廊非常安静，你几乎听不到脚踩在厚实地毯上的声音。"
            "每间房间的左右两侧都有镶着金边的大型木门。"
            "每隔约5英尺悬挂着一盏小灯笼，发出柔和的光芒，照亮道路。" );
    SetItems( ([ "hallway" : "走廊非常安静。",
                "carpet" : "深酒红色。",
                ({ "lanterns", "lanter" }) :
                "灯笼是带玻璃面板的金色灯笼。",
                "doors" : "门是大型橡木屏障。",
                ]) );
    SetExits( ([ "north" : "/domains/Praxis/hall2",
                "south" : "/domains/Praxis/hotel",
                "east" : "/domains/Praxis/inn101",
                "west" : "/domains/Praxis/inn102",
                ]) );
    //set_pre_exit_functions( ({ "east", "west" }), ({ "room_101", "room_102" }) ); 
}

int room_101() {
    if(present("/domains/Praxis/hotel"->query_key_id(101),this_player()))
        return 1;
    write( "你不能进去！");
    return 0;
}

int room_102() {
    if(present("/domains/Praxis/hotel"->query_key_id(102),this_player()))
        return 1;
    write( "你不能进去！");
    return 0;
}

void init(){
    ::init();
}
