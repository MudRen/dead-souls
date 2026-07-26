//  /domains/Praxis/pit.c
//  A torture chamber, for use with the Nightmare Mortal law system.
//  Created by Manny@Nightmare 940830

#include <lib.h>

inherit LIB_ROOM;

create() {
    ::create();
    SetProperties( ([ "light": 0, "no teleport" : 1, "no magic" : 1
                ]) );
    SetShort("蜘蛛坑");
    SetLong("你站在地下深处的一个圆形坑中。"
            "环绕你的墙壁完全光滑，没有任何可以攀爬或逃脱的痕迹。");
    SetItems( ([ ({ "walls", "wall" }) : "一面光滑的圆形墙壁，"
                "约50肘尺深，异常光滑。"]) );
}

void reset() {
    int x;

    ::reset();
    if(!present("spider")) {
        for(x=0; x<15; ++x) {
            new("/domains/Praxis/obj/mon/spider")->move(this_object());
        }
    }
}
void init(){
    ::init();
}
