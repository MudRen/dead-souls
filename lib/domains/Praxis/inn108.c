inherit "/lib/std/room";


void create() {
    ::create();
    SetProperties( ([ "light" : 2, "no castle" : 1 ]) );
    SetShort( "一间豪华卧房" );
    SetLong( "你进入了噩梦旅馆的豪华套房之一。一张铺着淡蓝色缎面"
            "被罩的大床立在房间中央。右边有一个木质衣柜，床的两侧"
            "各放置了一个橡木床头柜。一个插满玫瑰的水晶花瓶放在"
            "靠后墙的梳妆台上。要离开房间，请输入 'leave'。");
    SetItems( ([ ({ "rooms", "room" }) :
                "这是噩梦旅馆的豪华套房之一。",
                "bed" : "床非常大，看起来很舒适。",
                "closet" : "木质衣柜在角落里。",
                "vase" : "花瓶里插满了新鲜的玫瑰。",
                "bureau" : "木质梳妆台靠在远处的墙边。",
                "wall" : "墙壁最近被漆成了乳白色。",
                "nightstand" : "床头柜由高品质木材制成。",
                ]) );
    SetExits( ([
                "leave" : "/domains/Praxis/hall3",
                "east" : "/domains/Praxis/hall4.c",
                ]) );
}
void init(){
    ::init();
}
