/*   /secure/cmds/player/peer.c
 *   Peer into an adjacent room wihout actually entering
 *   Blitz@Dead SoulsIV
 */

#include <lib.h>

inherit LIB_DAEMON;

string DescribeItems(mixed var);
string DescribeLiving(mixed var);

mixed cmd(string str) {
    int i, err;
    string file;
    object env, *livings, *items;

    if( !sizeof(str) ) return "命令格式：peer <方向>";
    switch(str){
        case "n" : str = "north";break;
        case "ne" : str = "northeast";break;
        case "nw" : str = "northwest";break;
        case "s" : str = "south";break;
        case "se" : str = "southeast";break;
        case "sw" : str = "southwest";break;
        case "e" : str = "east";break;
        case "w" : str = "west";break;
        case "u" : str = "up";break;
        case "d" : str = "down";break;
    }
    env = environment(this_player());
    if( !file = env->GetExit(str) ) file = env->GetEnter(str);
    if( !sizeof(file) )
        return "你无法朝那个方向窥视。";
    if( (i = this_player()->GetEffectiveVision()) > 5 )
        return "光线太强了，无法窥视。";
    if( env->GetDoor(str) && !((env->GetDoor(str))->CanPeer()) ) {
        message("my_action", sprintf("%s挡住了你朝%s方向的视线。",
                    (capitalize(env->GetDoor(str)->GetShort(str))), str),
                this_player() );
        return 1;
    }
    err = catch(env = load_object(file));
    if(err || !env){
        message("my_action", "朝"+str+"方向窥视不安全！", this_player() );
        return 1;
    }
    if(env->GetProperty("no peer")){
        return "你看不到那个方向。";
    }
    if(env->GetProperty("nopeer")){
        return "你看不到那个方向。";
    }
    if( (i = this_player()->GetEffectiveVision(file,1)) > 5 )
        return "那个方向光线太强了。";
    else if( i < 3 )
        return "那里太暗了。";

    items = filter(all_inventory(env),
            (: !$1->GetInvis(this_player()) :) );
    items = items - (livings = filter(items, (: living :)));
    message("my_action", "%^GREEN%^"
            "你朝"+str+"方向窥视，看到了...",
            this_player() );
    message("other_action",
            this_player()->GetCapName()+"朝"+str+"方向窥视。",
            environment(this_player()), this_player() );
    message("room_description",
            ("\n"+env->GetLong(0)+"\n" || "\nA void.\n"),
            this_player() );
    if( sizeof(items) )
        message("room_inventory",
                "%^MAGENTA%^" + DescribeItems(items) + "%^RESET%^\n",
                this_player() );
    if( sizeof(livings) )
        message("room_inventory",
                "%^BOLD%^%^RED%^" + DescribeLiving(livings) + "%^RESET%^",
                this_player() );
    return 1;
}

string DescribeItems(mixed var) {
    mapping m = ([ ]);
    string *shorts, ret;
    int i, max;

    if( !arrayp(var) ) return "";
    i = sizeof( shorts = map(var, (: $1->GetShort() :)) );
    while(i--) {
        if( !sizeof(shorts[i]) ) continue;
        if( m[ shorts[i] ] ) m[ shorts[i] ]++;
        else m[ shorts[i] ] = 1;
    }
    i = max = sizeof( shorts = keys(m) );
    ret = "";
    for(i=0; i<max; i++) {
        if( m[ shorts[i] ] < 2 ) ret += shorts[i];
        else ret += consolidate(m[shorts[i]], shorts[i]);
        if( i == (max - 1) ) {
            if( max>1 || m[ shorts[i] ] > 1 ) ret += "在这里。";
            else ret += "在这里。";
        }
        else if( i == (max - 2) ) ret += "和";
        else ret += "、";
    }
    return capitalize(ret);
}

string DescribeLiving(mixed var) {
    mapping m = ([ ]);
    string *shorts, ret;
    int i;
    if( !arrayp(var) ) return "";
    i = sizeof( shorts = map(var, (: $1->GetShort() :)) );
    while(i--) {
        if( !sizeof(shorts[i]) ) continue;
        if( m[ shorts[i] ] ) m[ shorts[i] ]++;
        else m[ shorts[i] ] = 1;
    }
    ret = "";
    i = sizeof( shorts = keys(m) );
    while(i--) if( m[ shorts[i] ] > 1 )
        ret += (consolidate(m[shorts[i]], shorts[i]) + "\n");
    else ret += (shorts[i] + "\n");
    return ret;
}

string GetHelp(){
    return ("命令格式：peer <方向>\n\n"
            "允许你在不进入房间的情况下窥视相邻的房间。"
            "注意：光线和门会影响你看到的内容。");
}
