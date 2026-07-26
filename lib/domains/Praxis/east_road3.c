#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("no castle", 1);
    SetShort( "东大道北端");
    SetLong(
            "东大道突然到了尽头，你发现自己来到了普拉克西斯森林的脚下。"
            "这些普拉克西斯的外围地区不常有人造访。这里非常安静和孤独，"
            "周围几乎没有人在。前方，在道路尽头，你可以看到一块"
            "钉在树上的小告示牌。一条小步道从道路向东延伸。");
    SetItems(
            (["road" : "穿越普拉克西斯东端的道路。",
             "forest" : "森林黑暗而令人生畏。",
             "intersection" : "其中一角有一家餐厅。",
             "alley" : "明亮而美好。",
             "restaurant" : "最后的龙餐厅。",
             "sign" : "一块小白告示牌，也许你可以读一读。"]) );
    SetSkyDomain("town");
    SetExits( ([
                "south" : "/domains/Praxis/east_road2",
                ]) );
}

int go_north() {
    if(this_player()->query_level() > 5) {
        write("你试图继续向北走，但小径变得太窄，无法容纳你的体型。");
        return 0;
    }
    return 1;
}

void init() {
    ::init();
    add_action("read","read");
}

int read(string str) {
    if(str == "sign") {
        write("告示牌上写着：%^RED%^欢迎所有新成员来到噩梦世界！"
                "北边有一片专门为初到普拉克西斯的新玩家准备的特殊区域。%^RESET%^");
        return 1;
    }
    notify_fail("读什么？\n");
    return 0;
}
