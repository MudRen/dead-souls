#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("donate");
    SetRules("STR STR", "STR STR to STR");
    SetErrorMessage("donate <数量> <货币>");
    SetHelp("语法：donate <数量> <货币>\n\n"
            "捐赠命令用于捐赠金钱。");
}

mixed can_donate_str_str(string amount, string currency){
    return this_player()->CanManipulate();
}

mixed can_donate_str_str_to_str(string amount, string currency, string foo){
    return can_donate_str_str(amount, currency);
}

mixed do_donate_str_str(string amount, string currency) {
    object *stuff;
    object *donate_boxes;

    donate_boxes = ({});

    stuff = all_inventory(environment(this_player()));

    foreach(object thing in stuff){
        if(inherits(LIB_DONATE,thing)){
            donate_boxes += ({ thing });
        }
    }

    if(sizeof(donate_boxes)){
        donate_boxes[0]->eventDonate(amount, currency);
    }

    else write("没有地方可以捐赠这个。");

    return 1;
}

mixed do_donate_str_str_to_str(string amount, string currency, string foo){
    return do_donate_str_str(amount, currency);
}
