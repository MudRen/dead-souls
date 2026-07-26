/*    /domains/Ylsrim/etc/cold.c
 *    From the Dead Souls Mud Library
 *    An example of how to build a germ
 *    created by Descartes of Borg 961216
 */

#include <lib.h>
#include <damage_types.h>

inherit LIB_GERM;

protected void create() {
    germ::create();
    SetId("cold");
    SetType("cold");
    SetCommunicable(40);
    SetCure(20);
    SetLifeSpan(60);
}

int eventSuffer(object who) {
    if( !random(100) ) {
        Destruct();
        return 1;
    }
    switch(random(3)) {
        case 0:
            send_messages("cough", "$agent_name$agent_verb痛苦地咳嗽。",
                    who, 0, environment(who));
            break;

        case 1:
            send_messages("", "$agent_possessive_noun红鼻子流满了$agent_possessive脸。", who, 0, environment(who));
            break;

        case 2:
            send_messages("look", "$agent_name$agent_verb看起来很痛苦。",
                    who, 0, environment(who));
            break;
    }
    who->eventReceiveDamage(0, COLD, random(3) + 1, 1);
    return 1;
}

