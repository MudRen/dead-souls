/*    /verbs/items/drink.c
 *    from the Dead Souls Mud Library
 *    drink
 *    drink OBJ
 *    created by Descartes of Borg 951113
 */



#include <lib.h>
#include <rounds.h>
#include "include/drink.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("drink");
    SetRules("OBJ", "from OBJ");
    SetErrorMessage("喝什么？");
    SetHelp("用法：drink <液体>\n"
            "      drink from <容器>\n\n"
            "允许你饮用液体物质。这些物质通常以咖啡因、酒精和普通饮料的形式出现。"
            "不同类型的饮料对你有不同的效果，你将通过实验来了解。\n\n"
            "另见：bait, cast, eat, fish");
    SetSynonyms("quaff");
}

mixed can_drink_obj(string verb) { return this_player()->CanManipulate(); }

mixed can_drink_from_obj(string verb) { return this_player()->CanManipulate(); }

mixed do_drink_obj(object ob) {
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventDrink, this_player(), ob :),
                ROUND_OTHER);
    else eventDrink(this_player(), ob);
    return 1;
}

mixed do_drink_from_obj(object ob, string id) {
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventDrink, this_player(), ob, id :),
                ROUND_OTHER);
    else eventDrink(this_player(), ob, id);
    return 1;
}

varargs void eventDrink(object who, object what, string id) {
    return what->eventDrink(who, id);
}
