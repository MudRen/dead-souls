#include <lib.h>
#include "../customdefs.h"

inherit LIB_TABLE;


void create() {
    ::create();
    SetKeyName("sample table");
    SetId( ({ "table" ,"sample table"}) );
    SetAdjectives( ({ "simple","sample" }) );
    SetShort("一张简单的桌子");
    SetLong("这是一张简单的示例桌子。它是\"台面\" "+
            "类型容器的示例。");
    SetBaseCost(1200);
    SetMaxCarry(5000);
    SetInventory( ([
                MY_OBJ "/key" : 1,
                MY_OBJ "/pitcher" : 1,
                MY_OBJ "/cup" : 1,
                ]) );
}
void init(){
    ::init();
}
