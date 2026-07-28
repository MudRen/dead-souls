#include <lib.h>

inherit LIB_VERB;

protected void create() {
    ::create();
    SetVerb("befriend");
    SetRules("LIV");
    SetErrorMessage("你想和谁交朋友？");
    SetHelp("Syntax: befriend <LIVING>\n\n"
            "If a living object is specified, this command allows "
            "you to try to make friends. This is a prerequisite to " 
            "successfully mounting an animal. Note that if your "
            "charisma is low "
            "enough, you may fail. Also beware that someone with higher "
            "charisma may steal your mount.\n"
            "See also: mount, dismount, abandon");
}

mixed can_befriend_liv() { return 1; }

mixed do_befriend_liv(object ob) {
    ob->eventBefriend(this_player());
    return 1;
}
