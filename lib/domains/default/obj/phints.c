#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("hintbook");
    SetId( ({"book", "hints", "book of hints"}) );
    SetAdjectives( ({"hint", "player", "players"}) );
    SetShort("玩家提示书");
    SetLong("这是一本提示书。要阅读它，你必须阅读其中的章节。例如，'read chapter 1 in hintbook'，或 'read index in hintbook'");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(3);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetTitle("The Player's Hint Book");
    SetSource("/doc/phints");
    SetDefaultRead("试试 \"read chapter 1 in hintbook\" 或 "
            "\"read index in hintbook\"");
}

void init(){
    ::init();
}
