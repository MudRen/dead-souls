#include <lib.h>
inherit LIB_SHOP;
inherit LIB_AMBIANCE;

int ReadList(){
    write("可用治疗项目：\n"
            "\t治疗术，费用200：\t\t加速伤口快速恢复\n"
            "\t再生术，费用1200：\t\t重新长出断肢\n"
            "\t切除术，费用700：\t\t移除子弹等异物\n"
            "\t解毒剂，费用200：\t\t缓解中毒效果\n"
            "\t感冒药，费用10：\t\t缓解感冒症状\n"
            "\n"
            "示例：如果你严重受伤需要治疗：\n\n"
            "\"buy healing slip from james\"\n"
            "\n"
            "如果你中毒了： \n\n"
            "\"buy antidote from james\"\n"
            "\n"
            "拿到你的单据后，向西去见医生，"
            "把单据交给他。\n"

         );
    return 1;
}
protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("医疗师公会");
    SetLong("你在医疗师公会里。当人们有医疗问题时就会来到这里，"
            "只要付费，就能得到帮助。"
            "看起来医生的工作区域就在西边。"
            "萨奎弗路在东边。"
            "\n%^GREEN%^这里有一个你可以阅读的列表。%^RESET%^");
    SetItems( ([
                ({"list","list on the wall"}) : "一个列出可用治疗项目的列表",
                "wall" : "一个平整的垂直结构，支撑着天花板。",
                ({"work area","doctor's work area"}) : "医生的工作区域在西边。",
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
