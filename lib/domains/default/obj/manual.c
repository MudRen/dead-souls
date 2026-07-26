#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("creator's manual");
    SetId( ({"manual", "book", "creators manual"}) );
    SetAdjectives( ({"creator", "creators", "coder", "coders"}) );
    SetShort("创造者手册");
    SetLong("这是创造者和管理员的手册。要阅读它，你必须阅读其中的章节。例如，\"read chapter 1 in manual\"。\n如果你是编程新手，你应该从第31章开始。");
    SetNoCondition(1);
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetTitle("The Coder's Manual");
    SetSource("/doc/manual");
    SetDefaultRead("试试 \"read chapter 1 in manual\" 或 "
            "\"read index in manual\"\n"
            "新创造者应该特别阅读快速创建系统文档，从第31章开始");
}
void init(){
    ::init();
}
