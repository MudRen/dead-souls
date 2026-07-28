#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("drive");
    SetRules("STR", "into STR" );
    SetErrorMessage("往哪个方向驾驶？");
    SetHelp("Syntax: drive <DIRECTION>\n"
            "        drive into <PLACE>\n\n"
            "Moves your vehicle towards the direction you specify, or into the place "
            "you specify.  The command \"drive into\" is synonymous with the "
            "\"enter\" command.\n"
            "See also: mount, dismount");
}

mixed can_drive_str(string str) {
    object vehicle = environment(this_player());
    object where;

    if(vehicle) where = environment(vehicle); 
    if(vehicle && !vehicle->GetMount()) return "你没有载具。";

    if( !vehicle ) return "你哪里也不在。";
    if( !where ) return "你的载具不在任何地方。";
    if( vehicle->GetStaminaPoints() <3 )
        return "你的载具缺少燃料。";
    if(!stringp(hobbled(vehicle))) return "你的载具已瘫痪。";
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
    return where->CanGo(vehicle, str);
}

mixed can_drive_into_str(string str) {
    object vehicle = environment(this_player());
    object where;

    if(vehicle) where = environment(vehicle); 
    if(vehicle && !vehicle->GetMount()) return "你没有载具。";

    if( !vehicle ) return "你哪里也不在。";
    if( !where ) return "你的载具不在任何地方。";
    if( vehicle->GetStaminaPoints() <3 )
        return "你的载具燃料不足。";
    if(!stringp(hobbled(vehicle))) return "你的载具已瘫痪。";
    return where->CanEnter(vehicle, str);
}

mixed do_drive_str(string str) {
    object vehicle = environment(this_player());
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
    return vehicle->eventDrive(str);
}

mixed do_drive_into_str(string str) {
    object vehicle = environment(this_player());
    return vehicle->eventDrive("into" + str);
}
