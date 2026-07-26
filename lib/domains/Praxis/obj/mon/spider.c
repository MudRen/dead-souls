//  /domains/Praxis/obj/mon/spider.c
//  Semi-Random spiders for the Pit of Spiders
//  Part of the Mortal Law system at Nightmare
//  Created by Manny@Nightmare 940831

#include <lib.h>

inherit LIB_NPC;

create() {
    ::create();
    SetKeyName("spider");
    switch(random(5)) {
        case 0:
            SetId( ({ "spider", "leaper", "black leaper" }) );
            SetShort("黑色跳跃者");
            SetLong("很少有蜘蛛比臭名昭著的黑色跳跃者更大更可怕了。");
            SetLevel(20);
            break;
        case 1:
        case 2:
            SetId( ({ "spider", "timber spider", "giant timber spider" }) );
            SetShort("巨型木材蜘蛛");
            SetLong("一只非常大且丑陋的灰色蜘蛛。看起来相当饥饿。");
            SetLevel(random(3)+12);
            break;
        default:
            SetId( ({ "spider", "cave spider" }) );
            SetShort("普拉克西斯洞穴蜘蛛");
            SetLong("一只中等大小的黑色蜘蛛，尾端有一个新月形的标记。");
            SetLevel(random(3)+8);
            break;
    }
    SetRace("insect");
    SetGender("male");
    SetAggressive(999999);
    SetDie( (:"death_func":) );
}

int death_func() {
    message("say", "%^RED%^"+this_object()->query_name()+"发出一声"
            "响亮的尖叫，然后倒地死亡。", environment(this_object()));
    if(!present("spider", environment(this_object()))) {
        int x;

        message("say", "%^RED%^你注意到更多的蜘蛛"
                "从坑底的裂缝中爬了进来！",
                environment(this_object()));
        for(x=0; x<10; ++x) {
            new("/"+__DIR__+"obj/mon/spider")->move(environment(this_object()));
        }
    }
    return 1;
}
