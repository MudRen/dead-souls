/*    /std/estate.c
 *    from Nightmare IV
 *    a standard estate entrance
 *    created by Descartes of Borg 940702
 */

#include <std.h>

inherit OBJECT;

string __Exit;

void create() {
    ::create();
    SetId( ({ "estate" }) );
    SetPreventGet("你无法拿走一整座房产！");
    SetPreventPut("你怎么能把房产那样做呢？");
    SetPreventDrop("真好奇你是怎么把这个弄到手的。");
    SetNoClean(1);
}

void init() {
    ::init();
    add_action("cmd_enter", "enter");
}

void set_exit(string str) { __Exit = str; }

protected int cmd_enter(string str) {
    if(present(str, environment(this_object())) != this_object()) return 0;
    this_player()->move_player(__Exit, "走进了房产");
    return 1;
}

void SetShort(string str) {
    SetId(GetId() + ({ lower_case(str) }) );
    ::SetShort(str);
}

