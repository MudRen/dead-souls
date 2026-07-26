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
    SetExits( ([ "north" : "/domains/Praxis/hall3",
                "south" : "/domains/Praxis/hall",
                "east" : "/domains/Praxis/inn103",
                "west" : "/domains/Praxis/inn104"
                ]) );
    //set_pre_exit_functions( ({ "east" , "west" }), ({ "room_103", "room_104" }) );
}

int room_103() {
    if(present("/domains/Praxis/hotel"->query_key_id(103),this_player()))
        return 1;
    write( "你不能进去！");
    return 0;
}

int room_104() {
    if(present("/domains/Praxis/hotel"->query_key_id(104),this_player()))
        return 1;
    write( "你不能进去！");
    return 0;
}

void init(){
    ::init();
}
