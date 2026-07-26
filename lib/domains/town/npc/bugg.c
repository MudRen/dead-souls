#include <lib.h>

inherit  LIB_TEACHER;

void create(){
    ::create();
    SetKeyName("bugg");
    SetId( ({"teacher","dwarf","schoolteacher","bugg the schoolteacher"}) );
    SetGender("male");
    SetRace("dwarf");
    SetNativeLanguage("common");
    SetShort("教师巴格");
    SetLong("这是一个以教你东西为工作的人。"+
            "例如，'ask teacher to teach Malkierien'会让他开始教你"+
            "Malkierien语言课程，前提是他知道这种语言，"+
            "而且你有足够的训练点数。如果你缺少训练点数，"+
            "那就去冒险并获得升级。升级后你会"+
            "获得训练点数。要了解更多关于巴格能教什么：ask bugg for help"); 
    SetLevel(1);
    SetLanguage("Malkierien", 100);
    SetLanguage("English", 100);
    SetLanguage("Edhellen", 100);
    SetLanguage("Tangetto", 100);
    SetLanguage("Poleepkwa", 100);
    AddTeachingLanguages( ({"Malkierien", "English", "Common",
                "Edhellen", "Tangetto", "Poleepkwa" }) );
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}
void init() {
    ::init();
}
