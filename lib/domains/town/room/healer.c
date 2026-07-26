#include <lib.h>
inherit LIB_SHOP;
inherit LIB_AMBIANCE;

int ReadList(){
    write("AVAILABLE PROCEDURES:\n"
            "\thealing, cost 200:\t\tfacilitate rapid recovery from wounds\n"
            "\tregeneration, cost 1200:\tgrow back severed limbs\n"
            "\texcision, cost 700:\t\tremove bullets\n"
            "\tpoison antidote, cost 200:\tmitigate the effects of poisoning\n"
            "\tclaritin, cost 10:\t\talleviate cold symptoms\n"
            "\n"
            "Example: If you are badly hurt and need healing:\n\n"
            "\"buy healing slip from james\"\n"
            "\n"
            "If you've been poisoned: \n\n"
            "\"buy antidote from james\"\n"
            "\n"
            "Once you have your slip, go west to see the doctor and "
            "give the slip to him.\n"

         );
    return 1;
}
protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("治疗师公会");
    SetLong("你在治疗师公会里。人们遇到医疗问题时会来这里，付出一定费用就能得到帮助。医生的工作区似乎在西边。萨奎沃路在东边。\n%^GREEN%^这里有一份你可以阅读的清单。%^RESET%^");
    SetItems( ([
                ({"list","list on the wall"}) : "一份可用治疗项目的清单",
                "wall" : "支撑天花板的平坦垂直结构。",
                ({"work area","doctor's work area"}) : "在西边。",
                ({"road","tavern road"}) : "道路在外面，东边。"
                ]) );
    SetRead( ({"list","list on wall"}) , (: ReadList :) );
    SetInventory(([
                "/domains/town/obj/bbucket" :1,
                "/domains/town/npc/james" : ({60, 1})
                ]) );
    SetExits( ([
                "east" : "/domains/town/room/road",
                "out" : "/domains/town/room/road",
                "west" : "/domains/town/room/chamber",
                ]) );
    SetProperty("no attack", 1);

}
void init(){
    ::init();
}
