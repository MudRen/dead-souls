/*    /domains/Praxis/npc/otik.c
 *    from Dead Souls
 *    created by Descartes of Borg 950603
 */

#include <lib.h>
#include <vendor_types.h>

inherit LIB_VENDOR;

protected void create() {
    ::create();
    SetKeyName("yulia");
    SetId( ({ "vendor","secretary","assistant","manager" }) );
    SetAdjectives( ({ "executive","medical","guild" }) );
    SetShort("尤莉亚，诊所助理");
    SetLevel(12);
    SetLong("尤莉亚是典型的办公室助理：她有点傲慢、爱管闲事、态度粗鲁；但她看起来是一个足够称职的秘书。她是你购买治疗单的人。阅读墙上的列表了解可用的治疗单。");
    SetGender("female");
    SetMorality(40);
    SetRace("human");
    AddCurrency("dollars", random(100));
    SetProperty("no bump", 1);
    SetLocalCurrency("dollars");
    SetStorageRoom("/domains/campus/room/healer2");
    SetMaxItems(10000);
    SetVendorType(VT_HERB);
    SetSkill("bargaining", 1);

}
