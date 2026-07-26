//Lassondra@Nightmare
inherit "/lib/std/room";


void create() {
    ::create();
    SetShort("蜜月套房" );
    SetProperties( ([ "no castle" : 1, "light" : 2 ]) );
    SetLong( "蜜月套房是一间非常豪华的房间。一张铺着翠绿色丝绸"
            "被罩的大床立在房间中央。脚下的地毯是深米色，"
            "几乎与床头柜和梳妆台的木质色调完美搭配。"
            "带有金色把手的大型双开门通往套房内外。" );
    SetItems( ([ "suite" : "这是噩梦旅馆一间非常大且看起来很昂贵的房间。",
                "room" : "这是噩梦旅馆的蜜月套房之一。",
                "carpet" : "地毯非常厚实，呈深米色。",
                "bureau" : "梳妆台被多次打磨过，从它在灯光下闪闪发亮就能看出来。",
                "nightstand" : "床头柜放置在床的两侧。",
                ({ "doors", "door" }) : "大型深色房门是非常深的红木色。",
                ({ "handles", "handle" }) : "双开门上的把手是金色的。"
                ]) );
    SetExits( ([
                "leave" : "/domains/Praxis/hall5",
                "west" : "/domains/Praxis/hall5.c",
                ]) );
}
void init(){
    ::init();
}
