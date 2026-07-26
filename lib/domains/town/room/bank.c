#include <lib.h>
inherit LIB_BANK;

int ReadSign();
protected void create() {
    bank::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("村庄第一银行");
    SetLong("这个简朴的地方是村庄金融活动的中心。虽然算不上什么豪华机构，但村民们信任这家银行，认为它是存放钱财最安全的地方。\n%^GREEN%^这里挂着一块你可以阅读的告示牌。%^RESET%^");
    SetInventory( ([
        "/domains/town/npc/zoe" : ({60, 1})
      ]) );
    SetItems( ([
        "sign" : "一块你可以阅读的告示牌。",
        ({"bank","First Village Bank"}) : "镇上主要的金融机构。",
      ]) );
    SetExits( ([
        "west" : "/domains/town/room/mountain_road.c",
      ]) );
    SetRead( ({"sign","sign hanging here"}) , (: ReadSign :) );
    SetProperty("no attack", 1);
}
int ReadSign(){
    write( @EndText
- This bank requires a minimum balance to open an account.
To use any of the bank's services, you must first open an
account (see below as to how).

- This bank charges for certain transactions, such as
currency exchange.

To conduct business here:

request account from TELLER
request balance from TELLER
ask TELLER to deposit AMOUNT CURRENCY
ask TELLER to withdraw AMOUNT CURRENCY
ask TELLER to exchange AMOUNT CURRENCY for CURRENCY

examples:

request account from zoe
request balance from zoe
ask zoe to deposit 100 silver
ask zoe to withdraw 10 silver
ask zoe to exchange 10 gold for silver

EndText
    );
    return 1;
}

void init(){
    ::init();
}
