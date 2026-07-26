#include <lib.h>
#include <armor_types.h>
inherit "/lib/std/armor";

void create() {
    ::create();
    SetKeyName("helm");
    SetId( ({ "helm", "helmet", "knight's helm" }) );
    SetShort( "骑士头盔");
    SetLong( "正义骑士的头盔。");
    SetMass(375);    SetValue( 95);

    SetArmorType(A_HELMET);
    SetRestrictLimbs( ({ "head" }) );
    SetAC(3);
    SetWear( (: this_object(), "extra_worn" :) );
}

int extra_worn() {
    if(this_player()->query_alignment() < 200) {
        write("这个头盔因厌恶而灼烧。");
        say(this_player()->query_cap_name()+"试图戴上骑士头盔时被灼烧了。");
        return 0;
    }
    write("你感到善良的力量流过你的全身。");
    say(this_player()->query_cap_name() + "因骑士头盔的善良力量而闪耀。");
    return 1;
}
