#include <lib.h>
inherit  LIB_MAYOR;
void create(){
    ::create();
    SetKeyName("mayor");
    SetId("mayor");
    SetGender("male");
    SetRace("human");
    SetShort("镇长");
    SetLong("这位看起来有些邋遢、相当古怪的男人"+
            "履行着这个镇首席行政官的职责。"+
            "大多数时候，人们向他申请公民身份，费用是5银币。");
    SetLocalCurrency("silver");
    SetTax(5);
}
//funs
//snuf
void init() {
    ::init();
    SetSmell(([  "default" : "一股相当奇怪的霉味。"]));
    SetListen(([  "default" : "镇长嘟囔着什么关于税收基数小得离谱的话。"]));
}
