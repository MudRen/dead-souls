inherit "/lib/std/room";

void init() {
    ::init();
    add_action( "leave", "leave" );
    add_action( "bounce", "bounce" );
}

void create() {
    ::create();
    SetProperties( ([ "light" : 2, "no castle" : 1 ]) );
    SetShort( "一间卧房" );
    SetLong( "你进入了噩梦旅馆豪华卧房中的一间。房间整洁有序。"
            "一张大床位于房间中央，两侧各有一个床头柜。"
            "一盏水晶灯放在右边的床头柜上。地毯是柔和的沙色，"
            "家具是深橡木色。要离开房间，请输入 'leave'。" );
    SetItems( ([
                ({ "room", "chambers", "chamber" }) :
                "这是一间非常舒适的房间。",
                "inn" : "噩梦旅馆被誉为这片土地上最好的旅馆。",
                "bed" : "床非常大且舒适。看起来在上面蹦跳会很有趣。",
                ({ "night stand", "night stands" }) :
                "床头柜是非常坚固的橡木家具。",
                "lamp" : "灯是一盏精致水晶制成的古董灯。",
                "carpet" : "地毯是非常柔和的米色。", ]) );
    SetExits( ([
                "west" : "/domains/Praxis/hall2.c",
                ]) );

}

int bounce(string str) {
    if(!str || str!="bed" ) {
        notify_fail( "在什么上面蹦？\n");
        return 0;
    }

    write( "你在床上开心地蹦上蹦下。");
    return 1;
}
int leave(string str) {
    write( "你打开旅馆房间的门，走进了走廊。" );
    this_player()->eventMoveLiving( "/domains/Praxis/hall2.c");
    return 1;
}
