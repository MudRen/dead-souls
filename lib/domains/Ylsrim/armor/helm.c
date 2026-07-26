/*    /domains/Ylsrim/armor/helm.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ARMOR;

varargs int WearHelm(object who, mixed where);

protected void create() {
    armor::create();
    SetKeyName("desert helm");
    SetId( ({ "helm", "desert helm" }) );
    SetAdjectives( ({ "sandy", "brown" }) );
    SetShort("一顶布满灰尘的头盔");
    SetLong("这顶头盔是沙漠头盔，授予沙漠中受尊敬的骑士。"
            "它由魔力沙凝聚而成，保护正义之士的头部。");
    SetDamagePoints(3000);
    SetVendorType(VT_ARMOR);
    SetMass(200);
    SetValue(300);
    SetArmorType(A_HELMET);
    SetWear( (: WearHelm :) );
    SetProtection(BLUNT, 40);
    SetProtection(BLADE, 3);
    SetProtection(KNIFE, 10);
    SetProtection(HEAT, 30);
}

varargs int WearHelm(object who, mixed where) {
    object env = environment(who);
    if( who->GetMorality() < 300 ) {
        who->eventPrint("头盔灼烧着你的头！");
        who->eventReceiveDamage(0, HEAT, random(10) + 10, 0, "head");
        return 0;
    }
    who->eventPrint("你戴上了沙漠头盔。");
    if(env) tell_room(env, who->GetName()+" wears the desert helm.", ({who}));
    return 1;
}
