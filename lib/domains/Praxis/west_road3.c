#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("enter", "enter");
}

void create() {
    ::create();
    SetProperty("light", 2);
    SetShort( "西大道北端");
    SetLong(
            "西大道突然到了尽头，被北边的森林吞没。一棵巨大的"
            "古柳树为这一整段道路提供了遮蔽。在它巨大的根部，"
            "你可以看到一个通向地底深处的洞。博克拉路在南边很远的地方。");
    SetItems(
            (["tree" : "它一定比普拉克西斯本身还要古老。",
             "hole" : "你也许能进入树洞。",
             "road" : "道路的这一端被那棵神秘巨树的阴影笼罩。",
             "foo" : "你太傻了。",
             "bar" : "连这个也要检查，是吧？"]) );
    SetSkyDomain("town");
    SetExits( 
            (["south" : "/domains/Praxis/west_road2"]) );
}

int enter(string str) {
    if(!str) {
        notify_fail("进入什么？\n");
        return 0;
    }
    if(str != "hole" && str != "tree") {
        notify_fail("你在这里不能那样做。\n");
        return 0;
    }
    this_player()->eventMoveLiving("/domains/Praxis/mage_join", "into the tree");
    return 1;
}
