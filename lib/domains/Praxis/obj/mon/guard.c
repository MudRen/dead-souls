#include <lib.h>
#include ROOMS_H

inherit LIB_NPC;

private object __Target;

void heart_beat() {
    ::heart_beat();
    if(__Target && environment(__Target) != environment(this_object())) {
        message("say", "%^BOLD%^%^RED%^守卫对你说：%^RESET%^"+
                "你以为你要去哪儿，小子？？", __Target);
        __Target->eventMoveLiving(environment(this_object()));
    }
}

void set_target(object ob) {
    if(!ob) return;
    __Target = ob;
}
