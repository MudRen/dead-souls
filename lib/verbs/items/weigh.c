#include <lib.h>
#include <vendor_types.h>
#include <rounds.h>
#include "include/weigh.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("weigh");
    SetRules("OBJ");
    SetErrorMessage("你想称什么？");
    SetHelp("语法：weigh <物品>\n\n"
            "对物品重量的大致估计。"
            "");
}

mixed can_weigh_obj() {
    return 1;
}

mixed do_weigh_obj(object obj) {
    string name, verb = "heft";
    if(!obj) return "你必须称量某个东西。";

    /* Check for presence of objects */
    name = obj->GetShort();
    if( environment(obj) != this_player() ) {
        this_player()->eventPrint("你没有"+name+"。");
        return 1;
    }

    if(obj->GetWorn()) verb = "get a feel for";

    this_player()->eventPrint("你专注地盯着" + name + "，并" +
            verb + "它。");
    environment(this_player())->eventPrint( this_player()->GetName() +
            "看了看" + name + "。", this_player());
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0,
                (: eventWeigh, this_player(), obj :),
                ROUND_OTHER);
    else eventWeigh(this_player(), obj);
    return 1;
}

int eventWeigh(object who, object obj){
    int ret, max, curr, cost, diff;
    float tmp, error;
    string ret_str, name;
    if( !(obj) ) return 0;
    name = obj->GetShort();
    cost = random(3) + 1;
    max = who->GetMaxStaminaPoints();
    curr = who->GetStaminaPoints();
    diff = max - curr;
    if(diff > 0) error = to_float(random(percent(diff, curr)));
    else diff = 0;
    if((environment(obj) != who)){
        who->eventPrint("你必须拥有该物品才能称量它。");
        return 0;
    }
    if(cost > who->GetStaminaPoints()){
        who->eventPrint("你现在太累了，无法称量。");
        environment(who)->eventPrint(
                who->GetName() + "看起来很疲惫。", who);
        return 0;
    }
    who->AddStaminaPoints(-cost);
    ret = obj->GetWeight();
    tmp = to_float(ret) * (error * 0.01);
    ret += to_int(tmp);
    ret /= 100;
    if(ret < 1) ret_str = "不到一磅。";
    else if(ret < 2) ret_str = "大约一磅。";
    else ret_str = "大约" + cardinal(ret) + "磅。";
    write("你粗略估计" + name + "重" +
            ret_str);
    return 1;
} 
