#include <lib.h>

inherit LIB_STORAGE;

nosave int maxlevel = 5;

string ReadSign(){
    string ret = "只有"+cardinal(maxlevel)+"级及以下的玩家才能从这个箱子里免费取东西。";
    return ret;
}

void create() {
    ::create();
    SetKeyName("charity bin");
    SetId(({"bin"}));
    SetAdjectives(({"large","charity"}));
    SetShort("一个大箱子");
    SetLong("这是一个非常大的箱子，用于存放捐赠给慈善机构的物品。贫困的人可以从里面取东西。");
    SetItems( ([
                ({ "sign" }) : "箱子上的一块告示牌，你可以阅读。",
                ]) );
    SetReads( ([
                "default" : "试试'read label on bin'",
                ({"sign"}) : (: ReadSign :),
                ]) );
    SetPreventGet("它被固定住了。");
    SetMass(5000);
    SetBaseCost("silver",500);
    SetMaxCarry(15000);
    SetCanClose(0);
    SetClosed(0);
    SetPersistent(1);
    RestoreObject();
}

void init(){
    ::init();
}

varargs int eventCalculateBonus(object ob, int take){
    int value, cls, sum, bonus, duration;
    object thingy, who = this_player();
    if(!ob || !this_player()) return 0;
    if(this_player()->GetLevel() <= maxlevel) return 0;
    value = ob->GetBaseCost();
    cls = (ob->GetClass() || 1);
    sum = (value + (cls * 1000) || 1);
    bonus = (sum/10000 || 1);
    duration = bonus * 10;
    if(bonus > 10) bonus = 10;
    if(duration > 1000) duration = 1000;
    if(take && bonus > 0) bonus = -bonus - (to_float(bonus) * 0.1);
    if(bonus > 0 && take) duration = -duration - (to_float(duration) * 0.1);
    if(sum >= 10000 || take){
        thingy = present_bonus("charity_bonus", who);
        if(thingy){
            bonus += thingy->GetStats()["luck"];
            duration += thingy->GetDuration();
            if(bonus > 33) bonus = 33;
            if(duration > 5000) duration = 5000;
        }
        else thingy = new(LIB_BONUS);
        thingy->SetBonusName("charity_bonus");
        thingy->SetStats( ([
                    "luck" : bonus,
                    ]) );
        thingy->SetBonusDuration(duration);
        if(present(thingy, who) || thingy->eventMove(who)){
            object env = environment(this_object());
            object wenv = environment(who);
            if(env && wenv && env == wenv){
                if(!take){
                    write("你体验到一种与世界其他部分融为一体的愉悦感。");
                }
                else {
                    write("你感到自己很吝啬和小气。");
                }
            }
        }
    }
    return 1;
}

int eventReceiveObject(object ob){
    int ret = ::eventReceiveObject(ob);
    if(ret) eventCalculateBonus(ob);
    return ret;
}

int eventReleaseObject(object ob){
    int ret = ::eventReleaseObject(ob);
    if(ret) eventCalculateBonus(ob, 1);
    return ret;
}
