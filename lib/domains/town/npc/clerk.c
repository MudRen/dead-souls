#include <lib.h>
#include <objects.h>

inherit  LIB_CLERK;
void create(){
    ::create();
    SetKeyName("clerk");
    SetId("clerk");
    SetAdjectives("town");
    SetGender("male");
    SetRace("human");
    SetShort("镇书记官");
    SetLong("一位看起来很官僚的书记官。他有权主持公共记录的仪式。你可以\"ask clerk to marry me and 某人\"来结婚，以及\"ask clerk for a divorce\"来离婚。");
    SetLocalCurrency("silver");
    SetClass("cleric");
    SetLevel(4);
    SetTax(5);
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}
void init() {
    ::init();
    SetSmell(([  "default" : "一股相当奇怪的霉味。"]));
    SetListen(([  "default" : "书记官嘟囔着什么关于税收基数小得离谱的话。"]));
}
