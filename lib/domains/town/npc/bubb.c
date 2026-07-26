#include <lib.h>

inherit  LIB_TEACHER;
void create(){
    ::create();
    SetKeyName("bubb");
    SetId( ({"teacher","orc","schoolteacher","bubb the schoolteacher"}) );
    SetGender("male");
    SetRace("orc");
    SetNativeLanguage("english");
    SetTeachingFee(100);
    SetLocalCurrency("silver");
    SetShort("教师巴布");
    SetLong("这是一个以教你东西为工作的人。"+
            "例如，'ask teacher to teach Tangetto'会让他开始教你"+
            "Tangetto语言课程，前提是他知道这种语言，"+
            "而且你有足够的他偏好的货币。");
    SetLevel(1);
    SetLanguage("Tangetto", 100);
    AddTeachingLanguages( ({"Tangetto", "English" }) );
}
void init() {
    ::init();
}
