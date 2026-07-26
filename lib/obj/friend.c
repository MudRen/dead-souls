#include <lib.h>
#include <damage_types.h>

inherit LIB_NPC;

void SetStuff(int level);
void SetType(string what);
int count;

protected void create(int level) {
    string type;
    npc::create();
    SetId(({"blob"}));
    if(level < 40) type = "rodent";
    if(level > 39 && level < 50) type = "bear";
    if(level > 49 && level < 70) type = "golem";
    if(level > 69 && level < 90) type = "unicorn";
    else type = "dragon";
    count = level;
    SetType(type);
}

void SetType(string what) {
    SetRace(what);
    if(!SetClass("monk")) SetClass("fighter");
    SetLevel(to_int(count/12));
    SetGender(({"female","male"})[random(2)]);
    switch(what) {
        case "rodent":
            SetLong("一只可爱的小花栗鼠。");
            SetShort("花栗鼠");
            SetKeyName("chipmunk");
            SetId(({"chipmunk"}));
            break;
        case "bear":
            SetLong("一只大黑熊。");
            SetShort("黑熊");
            SetId(({"bear"}));
            SetKeyName("bear");
            break;
        case "golem":
            SetLong("一个面目狰狞的石魔像。");
            SetShort("石魔像");
            SetId(({"golem"}));
            SetKeyName("golem");
            break;
        case "unicorn":
            SetLong("一只高贵的独角兽。");
            SetShort("独角兽");
            SetId(({"unicorn"}));
            SetKeyName("unicorn");
            break;
        case "dragon":
            SetLong("一条面目狰狞的巨大龙。");
            SetShort("巨龙");
            SetId(({"dragon"}));
            SetKeyName("dragon");
            break;
    }
}

void heart_beat() {
    ::heart_beat();
    count--;
    if(count <= 10) send_messages("flicker","$agent_name $agent_verb.",
            this_object(),0,environment());
    if(count <= 0) {
        send_messages("flicker","$agent_name slowly $agent_verb out"
                " of existence...",this_object(),0,environment());
        eventDestruct();
    }
}



