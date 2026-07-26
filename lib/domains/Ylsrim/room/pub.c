/*    /domains/Ylsrim/room/pub.c
 *    From the Dead Souls Mud Library
 *    An example pub room
 *    Created by Descartes of Borg 960302
 */

#include <lib.h>
#include <message_class.h> // defines MSG_SYSTEM

inherit LIB_ROOM;

// This is a special SetRead() function that allows players to read
// the menu

int readMenu(object who, string str) {
    string* tmp2 = ({});
    string* tmp = ({ sprintf("%:-20s %:-7s", "Drink", "Cost") });
    int langlevel = this_player()->GetLanguageLevel("Edhellen");
    object ob = present_file("/domains/Ylsrim/npc/lars");

    if( !ob ) { // lars is dead!
        this_player()->eventPrint("菜单上沾满了血迹，难以辨认。");
        tmp = ({ translate("Bad wolf.", langlevel) });
    }
    else {
        foreach(string *item in keys(ob->GetMenuItems())) {
            tmp += ({ sprintf("%:-20s %d electrum", capitalize(item[0]),
                        to_int(ob->GetCost(item))) });
        }
        foreach(string element in tmp){
            element = translate(element, langlevel);
            tmp2 += ({ element });
        }
        tmp = tmp2;
    }
    // show the menu a page at a time
    this_player()->eventPage(tmp, MSG_SYSTEM); // MSG_SYSTEM means ignore blocking
    return 1;
}
protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("indoors");
    SetAmbientLight(25);
    SetShort("拉尔斯酒馆");
    SetLong("拉尔斯酒馆是伊尔斯利姆最著名的聚会场所之一。"
            "然而正如你所见，它并不是最舒适的那种。"
            "桌椅散落各处，墙上满是各种语言的涂鸦。"
            "饮品菜单大概是墙上唯一可读的东西。"
            "如果你懂精灵语的话。");
    SetLanguage("Edhellen");
    SetInventory(([
                "/domains/Ylsrim/npc/lars" : 1,
                ]));
    SetListen("喧闹的派对声让你很难听到其他声音。");
    SetSmell("这个地方闻起来像是被麦酒浸泡过。");
    AddItem(({ "tables", "stools" }), "随着白天的推移和顾客们的社交，"
            "桌椅开始四处移动。当然，没有什么比一场好斗更能移动它们了。");
    AddItem(({ "menu", "drinks", "menu of drinks" }), "菜单是用精灵语写的。你能读懂吗？", ({ "drink" }));
    AddItem(({ "writing", "walls" }), "各种语言的涂鸦，用各种笔迹和手迹覆盖了大部分墙壁。");
    SetExits(([ "east" : "/domains/Ylsrim/room/"+ "s_bazaar" ]));
    // Bring in the Bar Keep
    // make the writing and the menu readable
    SetRead("writing", (: readMenu :));
    SetRead("menu", (: readMenu :));
}
void init(){
    ::init();
}
