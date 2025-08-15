#include <lib.h>
inherit LIB_BANK;

int ReadSign();
protected void create() {
    bank::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("第一村庄银行");
    SetLong("这个简单的地方是村庄金融活动的中心。虽然完全不是一个华丽的机构，但这家银行被市民们信任为保管他们钱财最安全的地方。\n%^GREEN%^这里挂着一个你可以阅读的标牌。%^RESET%^");
    SetInventory( ([
        "/domains/town/npc/zoe" : ({60, 1})
      ]) );
    SetItems( ([
        "sign" : "一个你可以阅读的标牌。",
        ({"bank","First Village Bank"}) : "镇上的主要金融机构。",
      ]) );
    SetExits( ([
        "west" : "/domains/town/room/mountain_road.c",
      ]) );
    SetRead( ({"sign","sign hanging here"}) , (: ReadSign :) );
    SetProperty("no attack", 1);
}
int ReadSign(){
    write( @EndText
- 这家银行需要最低余额才能开设账户。
要使用银行的任何服务，你必须先开设一个账户（见下文如何操作）。

- 这家银行对某些交易收费，比如货币兑换。

在这里办理业务：

request account from 出纳员
request balance from 出纳员
ask 出纳员 to deposit 金额 货币
ask 出纳员 to withdraw 金额 货币
ask 出纳员 to exchange 金额 货币 for 货币

示例：

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
