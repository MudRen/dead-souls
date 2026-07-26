//  /domains/Praxis/obj/misc/hood.c
//  A hood for blinding players
//  For the Nightmare mortal law system
//  Created by Manny@Nightmare 940906

#include <lib.h>

inherit LIB_ITEM;

create() {
    ::create();
    SetKeyName("hood");
    SetId(({"hood", "black hood" }) );
    SetShort("一个黑色头套");
    SetLong("一个用来遮住受害者眼睛的黑色头套");
    SetPreventDrop("头套牢牢地固定在你的脖子上");
}

void init() {
    ::init();
    if(!living(environment(this_object()))) this_object()->remove();
    add_action("cmd_look", "look");
    add_action("cmd_look", "peek");
    add_action("cmd_look", "give");
}

int cmd_look() {
    message("my_action", "太暗了。", this_player());
    return 1;
}

