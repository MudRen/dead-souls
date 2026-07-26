inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 1);
    SetShort( "影狼之墓");
    SetLong(
            "你在普拉克西斯墓地的北端。古老、被遗弃已久的坟墓"
            "在你周围散布。一种诡异的寂静笼罩着这片区域，"
            "仿佛在等待什么可怕的事情。你在这里看到一座坟墓，"
            "有一块古色古香的墓碑。");
    SetItems(
            (["cemetery" : "寂静的坟墓在你周围延伸。你感觉有人在注视着你。",
             "grave" : "坟墓很古老，被草覆盖。",
             "writing" : "刻字写着：神秘的影狼长眠于此。"
             "当他被发现与说NI的骑士混在一起时，被泥潭玩家们果断处决了。",
             "headstone" : "墓碑是灰色大理石的。你也许能读上面的文字。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["southeast" : "/domains/Praxis/cemetery/grave_yard6",
             "south" : "/domains/Praxis/cemetery/grave_yard2"]) );
}
void reset() {
    ::reset();
    if (!present("ghost"))
        new("/domains/Praxis/cemetery/mon/ghost8")->move(this_object());
}

void init() {
    ::init();
    add_action("read","read");
}

int read(string str) {
    if(str == "writing" || str == "headstone") {
        write (::GetLong("writing"));
        return 1;
    }
    notify_fail("读什么？\n");
    return 0;
}
