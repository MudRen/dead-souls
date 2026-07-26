#include <lib.h>
inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "弗拉梅之墓");
    SetLong(
            "你进入了一个为保险代理人、银行家和玩泥巴的女性预留的区域。"
            "这是一个悲伤而阴暗的地方，很少有哀悼者造访，因为通常没有哀悼者。"
            "这里有一座坟墓吸引了你的目光。它覆盖着断铅笔和揉皱的纸张，"
            "上面写着一些不起作用的代码片段。某个可怜的生物遭遇了不幸的结局。"
            "你看到一个小木牌，因为没人想到要立一块墓碑。");
    SetItems(
            (["cemetery" : "寂静的坟墓在你周围延伸。你感觉有人在注视着你。",
             "grave" : "坟墓覆盖着一个程序员的垃圾和纪念品。",
             "pencils" : "铅笔都是短短的、咬过的、断掉的。没有一支还能写字。",
             "writing" : "弗拉梅长眠于此。这位可爱的年轻姑娘"
             "因为在错误的时间和错误的神灵面前使用幽默而不幸去世。"
             "让这成为年轻不朽者的教训。",
             "paper" : "无数小纸片和纸团散落在各处。",
             "code" : "那些代码片段从来没有起作用过，而且对正常人类来说是无法理解的。",
             "marker" : "牌匾是白色大理石的。你也许能读上面的文字。"])  );
    SetExits( 
            (["northeast" : "/domains/Praxis/cemetery/grave_yard5",
             "northwest" : "/domains/Praxis/cemetery/grave_yard2",
             "southwest" : "/domains/Praxis/cemetery/grave_yard3"]) );
}

void reset() {
    ::reset();
    if (!present("ghost"))
        new("/domains/Praxis/cemetery/mon/ghost4")->move(this_object());
}

void init() {
    ::init();
    add_action("read","read");
}

int read(string str) {
    if (str == "writing")  {
        write (::GetLong("writing"));
        return 1;
    }
    notify_fail("读什么？\n");
    return 0;
}

