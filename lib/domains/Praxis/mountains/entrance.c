#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetProperty("no castle", 1);
    SetListen("default", "各种声音从四面八方嘲弄着你。");
    SetSmell("default", "霉味从山的深处升起。");
    SetShort( "达洛克山脉下的隧道入口");
    SetLong(
            "你在达洛克山脉下哥布林的昏暗隧道里。唯一的光源是通往外面的开口。"
            "随着隧道向山的更深处下降，变得更加黑暗。"
            "东墙前面长出了一丛浓密的灌木，使得一个小洞穴很难被看到。"
            "东北方向你可以看到一条岩石小路。");
    SetItems(
            (["tunnel" : "非常昏暗。",
             "light" : "光线不多。",
             "opening" : "通往外面的世界。",
             "mountain" : "你感到邪恶贯穿其中。"]) );
    SetExits( ([ 
                "out" : "/domains/Praxis/pass2",
                ]) );
    AddExit("down", "/domains/Praxis/mountains/tunnel1", (: "go_down" :));
}

int go_down() {
    if(this_player()->query_level() > 10) {
        message("my_action", "一股魔力阻止你进入山的更深处。", this_player());
        return 0;
    }
    return 1;
}
