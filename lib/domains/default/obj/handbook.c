#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("player's handbook");
    SetId( ({"book", "handbook", "players handbook"}) );
    SetAdjectives( ({"player", "players"}) );
    SetShort("玩家手册");
    SetLong("这是玩家手册。要阅读它，你必须阅读其中的章节。例如，'read chapter 1 in handbook'，或 'read index in handbook'");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(3);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetTitle("The Player's Handbook");
    SetSource("/doc/hbook");
    SetDefaultRead("试试 \"read chapter 1 in handbook\" 或 "
            "\"read index in handbook\"");

}
void init(){
    ::init();
}
