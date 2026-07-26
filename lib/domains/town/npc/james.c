#include <lib.h>
#include <vendor_types.h>

inherit LIB_VENDOR;

protected void create() {
    ::create();
    SetKeyName("james");
    SetId( ({ "vendor","secretary","assistant","manager" }) );
    SetAdjectives( ({ "executive","medical","guild" }) );
    SetShort("公会秘书兼经理詹姆斯");
    SetLevel(12);
    SetLong("詹姆斯是典型的学徒治疗师：他有点"+
            "傲慢、官僚、生硬；但他看起来"+
            "是一个能干的秘书和公会官员。"+
            "他是你购买治疗代币的人。"+
            "请看墙上的列表了解可用的代币。");
    SetGender("male");
    SetMorality(40);
    SetRace("human");
    AddCurrency("silver", random(100));
    SetSkill("bargaining", 1);
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
    SetStorageRoom("/domains/town/room/healer2");
    SetMaxItems(10000);
    SetVendorType(VT_HERB);
    SetSkill("bargaining", 1);
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}

void init(){
    ::init();
}
