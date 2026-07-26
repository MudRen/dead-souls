#include <lib.h>
#include <daemons.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("uninstall");
    SetRules("OBJ","OBJ from OBJ","OBJ in OBJ","OBJ on OBJ");
    SetErrorMessage("卸载什么？");
    SetHelp("语法：uninstall <物品>\n"
            "        uninstall <物品> from <物品>\n"
            "");  
}

mixed can_uninstall() {
    return this_player()->CanManipulate();
}

mixed can_uninstall_obj(mixed foo) {
    return this_player()->CanManipulate();
}

mixed can_uninstall_obj_word_obj(mixed foo...) {
    return this_player()->CanManipulate();
}

mixed do_uninstall() {
    write("卸载什么？");
    return 1;
}

varargs mixed do_uninstall_obj(mixed foo) {
    write("从哪里卸载什么？");
    return 1;
}

varargs mixed do_uninstall_obj_word_obj(mixed foo, mixed foo2, mixed foo3) {
    return foo->eventUninstall(foo3);
}
