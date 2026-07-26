#include <lib.h>
inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "暗影之墓");
    SetLong(
            "你在墓地最南端的区域。你听不到友好的声音，只有不祥的寂静。"
            "这里有一座孤坟，坟头有一块小墓碑。");
    SetItems(
            (["headstone" : "墓碑是深钴蓝色的，上面有文字。",
             "cemetery" : "寂静的坟墓在你周围延伸。你感觉有人在注视着你。",
             "grave" : "坟墓覆盖着柔软的青草，已经在这里很长时间了。",
             "writing" : "暗影长眠于此。他被一群愤怒的年轻不朽者绞死了，因为他们嫌他在城堡里太吹毛求疵。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["north" : "/domains/Praxis/cemetery/grave_yard2",
             "northeast" : "/domains/Praxis/cemetery/grave_yard4"]) );
}

void reset() {
    ::reset();
    if (!present("ghost"))
        new("/domains/Praxis/cemetery/mon/ghost3")->move(this_object());
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
