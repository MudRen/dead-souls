inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "笛卡尔之墓");
    SetLong(
            "这是古老墓地的寒冷而寂静的东北角。"
            "当你看着这座坟墓上安装的雕像的扭曲形态时，你感到脊背发凉。"
            "坟墓上堆着小堆的螺母和螺栓。你注意到雕像上有一块牌匾。");
    SetItems(
            (["cemetery" : "寂静的坟墓在你周围延伸。你感觉有人在注视着你。",
             "grave" : "坟墓覆盖着小金属螺母、螺栓和其他金属祭品。",
             "nuts" : "坟墓覆盖着成堆的小金属片。",
             "bolts" : "坟墓覆盖着小金属片，包括螺母和螺栓。",
             "statue" : "雕像是一个大立方体，由许多金属碎片粘合而成。",
             "writing" : "博格长眠于此，单元#82664302-tr，"
             "停止运作时无人哀悼，无人注意。",
             "plaque" : "牌匾是银色金属的。你也许能读上面的刻字。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["northwest" : "/domains/Praxis/cemetery/grave_yard8",
             "southwest" : "/domains/Praxis/cemetery/grave_yard2",
             "southeast" : "/domains/Praxis/cemetery/grave_yard5"]) );
}

void reset() {
    ::reset();
    if (!present("ghost"))
        new("/domains/Praxis/cemetery/mon/ghost6")->move(this_object());
}

void init() {
    ::init();
    add_action("read","read");
}

int read(string str) {
    if (str == "plaque") {
        write (::GetLong("writing"));
        return 1;
    }
    notify_fail("读什么？\n");
    return 0;
}
