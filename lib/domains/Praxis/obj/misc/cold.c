#include <lib.h>

inherit LIB_GERM;

int coughs;

void create() {
    germ::create();
    coughs = 80;
    SetKeyName("cold");
    SetId( ({ "cold" }) );
    SetShort("感冒");
    SetLong("一种病毒感染，基本上无害，但通常会在大多数生物的一生中困扰它们。");
    SetCommunicable(10);
    SetCure(1);
    SetLifeSpan(300);
    SetType("viral");
}

void suffer(object ob) {
    coughs--;
    if(coughs%2) return;
    ob->add_hp(-(ob->query_hp()/10));
    message("my_action", "你剧烈地咳嗽！", ob);
    message("other_action", ob->query_cap_name()+"剧烈地咳嗽！",
            environment(ob), ob);
    if(!coughs) this_object()->remove();
}
