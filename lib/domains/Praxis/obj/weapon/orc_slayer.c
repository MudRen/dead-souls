#include <lib.h>
inherit LIB_ITEM;

create() {
    ::create();
    SetId(({"sword", "the_one_orc_slayer","orcslayer","fine sword"}));
    SetKeyName("orcslayer");
    SetShort("一把精良的剑");
    SetLong("这是一把制作精良的剑，上面有一个垂死兽人的图案。\n上面有文字。\n");
    SetMass(611);   SetValue( 200);

    SetClass(7);
    SetWeaponType("blade");
    SetWield("当你挥舞这把剑时，你感到对兽人的强烈仇恨。\n");
    SetRead( "Orcslayer\n");

    true();
}

int eventStrike(object ob) {
    int x, y;

    if(ob->query_race() != "orc") return 0;
    y = random(10);
    x = this_player()->query_alignment();
    if(x> 0) x = (x/100);
    else x = 0;
    y += x;
    write("兽人杀手吸取了更多兽人的鲜血！\n");
    say(this_player()->query_cap_name()+"的兽人杀手吸取了更多兽人的鲜血！\n", this_player());
    return y;
}
