#include <lib.h>
inherit LIB_ITEM;

create() {
    ::create();
    SetId(({"sword","dull sword","a dull sword"}));
    SetKeyName("sword");
    SetShort("一把钝剑");
    SetLong( "这把剑经历过更好的日子。它似乎在下水道里放了一段时间，"
            "结果生锈得几乎没用了。");
    SetMass(500);   SetValue( 50);

    SetClass(7);
    SetWeaponType("blade");
    SetWield("当你挥舞这把剑时，一层恶心的黏液覆盖了你的手。");
}
