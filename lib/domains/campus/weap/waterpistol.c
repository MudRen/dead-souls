/*    /domains/Examples/weapon/sword.c
 *    from the Dead Souls LPC Library
 *    a simple sword example, nothing fancy
 *    created by Descartes of Borg 950402
 */

#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_PISTOL;


protected void create() {
    ::create();
    SetKeyName("water pistol");
    SetId(({"pistol","gun"}));
    SetAdjectives(({"water","toy","plastic","squirt"}));
    SetShort("小塑料水枪");
    SetLong("一把小型红色透明塑料水枪，形状像射线枪。");
    SetMass(10);
    SetDollarCost(5);
    SetVendorType(VT_WEAPON);
    SetClass(10);
    SetDamageType(BLUNT);
    SetFirearmType("auto");
    SetWeaponType("blunt");
}

varargs mixed eventShoot(object shooter, mixed target, string direction){
    string name,patsy;
    object killer, env;

    if(!target || direction){
        write("你不能那样做。");
        return 1;
    }

    killer = this_player();
    name = killer->GetName();
    env = environment(killer);
    patsy = target->GetName();

    tell_room(env,name+"用"+possessive(killer)+
            "水枪把"+patsy+"淋了个透！",{killer,target} );
    tell_object(killer,"你用水枪把"+patsy+"淋了个透！哈哈哈，"+
            nominative(target)+"看起来像个傻瓜！");
    tell_object(target,name+"用"+possessive(killer)+
            "水枪把你淋了个透！哈哈哈！你看起来像个湿漉漉的大傻瓜！");
    return 1;
}

void init(){
    ::init();
}
