#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "银行金库");
    SetLong(
            "普拉克西斯银行将所有现金都存放在这个原本空无一物的金库里。"
            "南端的门通往大厅。");
    SetExits( 
            (["south" : "/domains/Praxis/bank"]) );
}

void reset() {
    object money;

    ::reset();
    if(!present("money")) {
        money = new("/std/lib/pile");
        money->SetCurrency("platinum", random(10));
        money->SetCurrency("gold", random(100));
        money->SetCurrency("electrum", random(200));
        money->move(this_object());
    }
}
void init(){
    ::init();
}
