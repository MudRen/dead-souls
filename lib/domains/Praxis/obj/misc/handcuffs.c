//  /domains/Praxis/obj/misc/handcuffs.c
//  From the Nightmare IV mudlib
//  Autoloading handcuffs for use with the mortal law system.
//  Created by Manny@Nightmare 940821

#include <lib.h>
#include <dirs.h>
#define ALLOWED_COMMANDS ({ "look", "say", "tell", "shout", "smile",\
        "frown", "grin", "shiver", "giggle", "laugh", "cry", "whimper",\
        "inventory", "pray", "dest", "call", "eval" })

inherit LIB_ITEM;

create() {
    ::create();
    SetId( ({ "handcuffs", "cuffs" }) );
    SetKeyName("handcuffs");
    SetShort("绳索手铐");
    SetLong("用来约束不法角色的粗绳。");
    SetMass(0);
    SetValue(0);
    SetPreventDrop("你无法放下那个，你的手被绑住了。");
}

void init() {
    ::init();
    add_action("all_cmds", "");
    if(!living(environment(this_object()))) this_object()->eventDestruct();
    command("save");
}

mixed *query_auto_load() {
    return (DIR_STANDARD_DOMAIN+"/obj/misc/handcuffs.c", ({ }) );
}

int all_cmds(string str) {

    if(member_array(query_verb(), ALLOWED_COMMANDS) == -1) {
        message("say", "%^RED%^你戴着手铐无法那样做。",
                this_player());
        return 1;
    }
    if(this_player()->query_ghost()) call_out("destroy_me", 0);
    return 0;
}

void destroy_me() {
    eventDestruct();
}
