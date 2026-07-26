#include <lib.h>
inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "福洛克之墓");
    SetLong(
            "你在一座古老、黑暗的墓地里。诡异的寂静让你神经紧张。"
            "你脚边是一座新挖的坟墓，挖得很匆忙。几朵凋谢的花"
            "无声而悲伤地见证了过去的感情。一块小大理石牌匾"
            "放在一边，还没有安装在坟墓头部。");
    SetItems(
            (["cemetery" : "寂静的坟墓在你周围延伸。你感觉有人在注视着你。",
             "grave" : "坟墓是新的，堆着新土。",
             "blossoms" : "花已经枯萎褪色了。看起来很悲伤。",
             "writing" : "可怜的老福洛克长眠于此。他的遗言是："
             "救命啊！！我正在接收线路噪音..fjjjdk..%$fffs..*嘎嘎*.."
             "0w0w0w0w0w!!",
             "plaque" : "牌匾是灰色大理石的。你也许能读上面的文字。"]) );
    SetExits( 
            (["northwest" : "/domains/Praxis/cemetery/grave_yard6",
             "west" : "/domains/Praxis/cemetery/grave_yard2",
             "southwest" : "/domains/Praxis/cemetery/grave_yard4"]) );
}
void reset() {
    ::reset();
    if (!present("ghost"))
        new("/domains/Praxis/cemetery/mon/ghost5")->move(this_object());
}

void init() {
    ::init();
    add_action("read","read");
}

int read(string str) {
    if(str == "writing" || str == "plaque") {
        write (::GetLong("writing"));
        return 1;
    }
    notify_fail("读什么？\n");
    return 0;
}

