#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("ride");
    SetRules("STR", "into STR" );
    SetErrorMessage("往哪个方向骑行？");
    SetHelp("Syntax: ride <DIRECTION>\n"
            "        ride into <PLACE>\n\n"
            "Moves your mount towards the direction you specify, or "
            "into the place "
            "you specify.  The command \"ride into\" is synonymous with the "
            "\"enter\" command.\n"
            "See also: mount, dismount");
}

mixed can_ride_str(string str) {
    object mount = environment(this_player());
    object where;

    if(mount) where = environment(mount); 
    if(mount && !mount->GetMount()) return "你没有坐骑。";

    if( !mount ) return "你哪里也不在。";
    if( !where ) return "你的坐骑不在任何地方。";
    if( mount->GetStaminaPoints() <3 )
        return "你的坐骑太累了，现在哪儿也去不了。";
    if(!stringp(hobbled(mount))) return "你的坐骑已丧失行动能力。";
    if(str) switch(str){
        case "n" : str = "north"; break;
        case "s" : str = "south"; break;
        case "e" : str = "east"; break;
        case "w" : str = "west"; break;
        case "u" : str = "up"; break;
        case "d" : str = "down"; break;
        case "ne" : str = "northeast"; break;
        case "nw" : str = "northwest"; break;
        case "se" : str = "southeast"; break;
        case "sw" : str = "southwest"; break;
    }
    return where->CanGo(mount, str);
}

mixed can_ride_into_str(string str) {
    object mount = environment(this_player());
    object where;

    if(mount) where = environment(mount);
    if(mount && !mount->GetMount()) return "你没有坐骑。";

    if( !mount ) return "你哪里也不在。";
    if( !where ) return "你的坐骑不在任何地方。";
    if( mount->GetStaminaPoints() <3 )
        return "你的坐骑太累了，现在哪儿也去不了。";
    if(!stringp(hobbled(mount))) return "你的坐骑已丧失行动能力。";
    return where->CanEnter(mount, str);
}

mixed do_ride_str(string str) {
    object mount = environment(this_player());
    if(str) switch(str){
        case "n" : str = "north"; break;
        case "s" : str = "south"; break;
        case "e" : str = "east"; break;
        case "w" : str = "west"; break;
        case "u" : str = "up"; break;
        case "d" : str = "down"; break;
        case "ne" : str = "northeast"; break;
        case "nw" : str = "northwest"; break;
        case "se" : str = "southeast"; break;
        case "sw" : str = "southwest"; break;
    }
    return mount->eventRide(str);
}

mixed do_ride_into_str(string str) {
    object mount = environment(this_player());
    return mount->eventRide("into" + str);
}
