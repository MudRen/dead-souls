//  /domains/Praxis/obj/misc/stone_pile.c
//  A stone pile/stones for stoning criminals.
//  For use with the Nightmare Mortal Law system
//  Created by Manny@Nightmare  940901

#include <lib.h>

inherit LIB_ITEM;

object target;
void set_target(object who);

void create() {
    ::create();
    SetKeyName("pile");
    SetId( ({ "stones", "pile of stones", "pile" }) );
    SetShort("一堆石头");
    SetLong("一堆漂亮的圆石头，非常适合扔向亡命之徒和罪犯。");
    SetPreventGet("你一次只能拿一块石头。");
}

void init() {
    ::init();
    add_action("get_stone", "get");
}

int get_stone(string str) {
    object stone;

    if(!str || str != "stone") return 0;
    message("say", "你从石头堆里捡起一块石头。你感到一股强烈的欲望"
            "想要试着把它<throw>向"
            +target->query_cap_name()+"...", this_player());
    message("say", this_player()->query_cap_name()+"从石头堆里捡起了一块石头。", environment(this_player()), this_player());
    stone = new("/"+__DIR__+"stone");
    stone->set_target(target);
    stone->move(this_player());
    return 1;
}

void set_target(object who) { target = who; }


