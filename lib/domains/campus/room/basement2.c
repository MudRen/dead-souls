#include <lib.h>
inherit LIB_ROOM;

int push_it(string str){
    if(str=="wall" || str=="west wall"){
        write("西墙打开了，你掉了进去！\n");
        say(this_player()->GetName()+"突然掉了下去消失了！\n");
        this_player()->eventMoveLiving("/domains/campus/room/tunnel", "west through a secret exit", this_player()->GetName()+" tumbles in.");
        return 1;
    }
}

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(5);
    SetShort("地下室");
    SetLong("你在LPC大学行政楼的地下室里。这里非常黑暗，相当潮湿。荧光灯似乎已经完全损坏。地下室东侧似乎光线稍好一些。西墙看起来有很多污渍……比这里的其他地方更脏。");
    SetItems(([
                "basement" : "这是一个黑暗、令人毛骨悚然的地下室。",
                "building" : "你在LPC大学行政楼的地下室里。",
                ({"wall","west wall"}) : "墙上似乎有很多模糊的手印。",
                ({"dark","darkness"})  : "到处都是黑暗。",
                ({"light","lighting","fluorescent lighting"}) : "这里的照明已经完全损坏。",
                ({"prints","print","handprint","handprints"}) : "模糊的手印，好像有人曾靠在墙上。",
                "air" : "空气沉重，让人难以呼吸。很难想象谁会喜欢待在这里。"]));
    SetExits( ([
                "east" : "/domains/campus/room/basement.c",
                ]) );
    SetRead( ([
                ({"wall","west wall"}) : "The cake is a lie.",
                ]), "malkierien" ); 
    SetProperty("no attack", 1);
}

void init(){
    ::init();
    add_action("push_it","push");
    add_action("push_it","search");
    add_action("push_it","touch");
    add_action("push_it","open");
}
