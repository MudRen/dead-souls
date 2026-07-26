#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("no castle", 1);
    SetShort( "普拉克西斯农田");
    SetLong(
            "你漫步进入的区域是普拉克西斯的农田。"
            "大片玉米田环绕着你，向东向西延伸数英里。"
            "玉米秆长得又高又壮，让人很难看清前方。"
            "在远处，你可以看到一个农舍的斑点。");
    SetItems(
            (["stalks" : "覆盖了大量土地的巨大玉米秆。",
             "stalk" : "一根巨大的玉米秆。",
             "farmhouse" : "农舍在很远的地方，无法到达。",
             "field" : "这个地方一定为整个地区提供食物。",
             "corn" : "一些人喜欢吃的粮食。它是%^YELLOW%^黄色%^RESET%^的。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["north"	: "/domains/Praxis/w_boc_la2"]) );
}

void reset() {
    ::reset();
    SetSearch("field", (: this_object(), "stalk_searching" :));
    SetSearch("stalks", (: this_object(), "stalk_searching" :));
}

void stalk_searching() {
    message("my_action", "在搜遍了所有高大的玉米秆后，"
            "你在其中找到了一把铲子！", this_player());
    message("other_action", this_player()->query_cap_name()+"在玉米秆中找到了一把铲子。", this_object(), ({ this_player() }));
    new("/domains/Praxis/obj/misc/shovel")->move(this_object());
    RemoveSearch("stalks");
    RemoveSearch("field");
}
void init(){
    ::init();
}
