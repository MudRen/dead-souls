#include <lib.h>
#include "include/use.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("use");
    SetRules("OBJ", "OBJ to STR");
    SetErrorMessage("用什么做什么？");
    SetHelp("语法：use <物品> to <命令>\n\n"
            "某些物品，如卷轴，允许你执行超出"
            "你自然能力的行为。当然，要知道一个物品"
            "是否能赋予你这种力量，唯一的办法要么是尝试它，"
            "要么是设法探测它的魔法。\n\n"
            "参见：detect, discern");
}

mixed can_use_obj(mixed args...){ 
    return 1; 
}

mixed can_use_obj_to_str(mixed args...){ 
    return 1; 
}

mixed do_use_obj_to_str(object ob, string str) {
    if(!ob){
        write("这里没有那个。");
        return 1;
    }
    return ob->eventUse(this_player(), str);
}

mixed do_use_obj(object ob) {
    return do_use_obj_to_str(ob, 0);
}
