#include <lib.h>
inherit LIB_SHOP;
inherit LIB_AMBIANCE;

int ReadList(){
    write("可用治疗项目：\n"
            "\t治疗，费用200：\t\t促进伤口快速恢复\n"
            "\t再生，费用1200：\t\t重新长出断肢\n"
            "\t手术，费用700：\t\t取出子弹\n"
            "\t解毒剂，费用200：\t\t减轻中毒效果\n"
            "\t抗过敏药，费用10：\t\t缓解感冒症状\n"
            "\n"
            "示例：如果你受了重伤需要治疗：\n\n"
            "\"buy healing slip from james\"\n"
            "\n"
            "如果你中毒了：\n\n"
            "\"buy antidote from james\"\n"
            "\n"
            "拿到单子后，往西走找医生，把单子给他。\n"

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
