#include <lib.h>
#include <daemons.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("load");
    SetSynonyms("charge", "recharge");
    SetRules("", "OBJ","OBJ with OBJ","OBJ into OBJ","OBJ in OBJ");
    SetErrorMessage("加载什么？");
    SetHelp("语法：load <物品>\n"
            "        load <物品> on <物品>\n"
            "同义词：charge, recharge\n");  
}

mixed can_load() {
    return this_player()->CanManipulate();
}

mixed can_load_obj(mixed foo) {
    return this_player()->CanManipulate();
}

mixed can_load_obj_word_obj(mixed foo) {
    return this_player()->CanManipulate();
}

mixed do_load() {
    write("加载什么？");
    return 1;
}

varargs mixed do_load_obj(mixed foo) {
    return foo->eventLoad();
}

varargs mixed do_load_obj_word_obj(mixed foo, mixed wort, mixed foo2) {
    if(wort == "with"){
        return foo2->eventLoad(this_player(), foo);
    }
    else {
        return foo->eventLoad(this_player(), foo2);
    }
}
