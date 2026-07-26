#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("satyr");
    SetAdjectives( ({"wild", "ferocious", "looking", "male", "humanoid", "creature"}) );
    SetId( ({"male", "humanoid", "creature"}) );
    SetShort("一个萨提尔");
    SetLong("这是一个外表狂野凶猛的人形雄性，上半身是人类，但下半身是山羊般的、毛茸茸的，他的腿是有蹄动物的。角从他头上狂野的鬃毛下长出。无论他的脸多么像人类，他的表情和举止都清楚地表明这不是一个被驯化的人，而是一个未被驯服的森林生物。");
    SetLevel(1);
    SetMelee(1);
    SetRace("satyr");
    SetGender("male");
}
void init(){
    ::init();
}
