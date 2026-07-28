/*    /secure/cmds/creator/update.c
 *    from the Dead Souls LPC Library
 *    destroys an object then reloads it
 *    created by Descartes of Borg 950330
 *    - added recursive update option (blitz 960711)
 *    Version: @(#) update.c 1.2@(#)
 *    Last modified: 96/12/17
 */

#include <lib.h>
#include ROOMS_H
#include <daemons.h>

inherit LIB_DAEMON;
inherit LIB_HELP;

#define U_RECURSIVE       (1 << 1)
#define U_INTERACTIVE     (1 << 2)
#define U_AUTOMATED       (1 << 3)

mapping LocationsMap = ([]);

varargs protected int eventUpdate(string args, int flags, string virt);

protected void CacheAndCarry(object *obs){
    if(!sizeof(obs)) return;
    foreach(object fellow in obs){
        string ubi = fellow->GetProperty("LastLocation");
        if(ubi) LocationsMap[fellow->GetKeyName()] = ubi;
        fellow->eventMove(ROOMS_D->GetVoid(fellow));
    }
}

protected void ReturnAndRelease(object *dudes, string file){
    if(!sizeof(dudes)) return;
    if(!file) return;
    dudes->eventMove(file);
    foreach(object fellow in dudes){
        if(sizeof(LocationsMap[fellow->GetKeyName()])){
            fellow->SetProperty("LastLocation",LocationsMap[fellow->GetKeyName()]);
        }
    }
}

protected void create() {
    SetHelp("语法: update [-r] [文件列表]\n\n"
            "销毁指定文件的主副本，然后尝试重新加载新版本。\n"
            "-r 标志尝试更新目标继承树中的所有文件。");
}

mixed cmd(string args) {
    object *obs, ob, mount;
    string *files, *tmpfiles;
    mixed tmp;
    string file, virt;
    int i, flags, err, ret;
    if( sizeof(args) ) {
        string str = args;
        args = "";
        foreach(string foo in explode(str, " ")) {
            if(!sizeof(foo)) continue;
            switch(foo) {
                case "-r" : flags |= U_RECURSIVE; break;
                case "-e" : flags |= U_INTERACTIVE; break;
                case "-a" : flags |= U_AUTOMATED; break;
                default: args += " " + foo;
            }
        }
    }
    if( args == "" || !args ) {
        if(!this_player()) return "没有玩家。";
        ob = room_environment(this_player());
        if( !ob ) return "你没有所在环境。";
        file = base_name(ob);
        if(ob->GetVirtual()){
            virt = path_prefix(file);
        }
        this_player()->eventPrint("正在更新环境");
        obs = filter(all_inventory(ob), (: userp :));
        if(mount) obs += ({ mount });
        if( sizeof(obs) ) CacheAndCarry(obs);
        err = catch( ret = eventUpdate(file, flags, virt) );
        if( err || !ret ) {
            obs->eventPrint("你的周围剧烈崩塌，你被抛入了虚空。");
            return "重新加载环境时出错。";
        }
        obs = filter(obs, (: $1 :));
        if( sizeof(obs) ) ReturnAndRelease(obs, file);
        return 1;
    }
    if(this_player()){
        tmpfiles = map(explode(args, " "),
                function(string x) {
                string tmp = this_player()->query_cwd();
                if( x[<2..] != ".c" ) x = x + ".c";
                return absolute_path(tmp, x);
                });
        tmpfiles = map(tmpfiles,
                (: ((file_size($1) == -2) ?
                    (($1[<1] == '/') ? ($1 + "*.c") : ($1 + "/*.c")) : $1)
                 :));
        i = sizeof(tmpfiles);
        files = ({});
        while(i--) {
            if( sizeof(tmp = wild_card(tmpfiles[i])) )
                files += tmp;
            else {
                this_player()->eventPrint(tmpfiles[i] + ": 文件未找到。");
            }
        }
        i = sizeof(files);
        while(i--) eventUpdate(files[i], flags);
    }
    return 1;
}

varargs protected int eventUpdate(string args, int flags, string virt) {
    object ob;
    string tmp;

    if( flags & U_RECURSIVE ) {
        string *ancestors;
        int i;

        if( !eventUpdate(args, flags ^ U_RECURSIVE) ) return 0;
        if( !(ob = find_object(args)) ) return 0;
        ancestors = deep_inherit_list(ob);
        if(this_player() && (flags & U_RECURSIVE) && !(flags & U_AUTOMATED))
            this_player()->eventPrint("(%^CYAN%^递归更新: " + args + "%^RESET%^)\n");
        i = sizeof(ancestors);
        while(i--) if( !eventUpdate(ancestors[i], flags ^ U_RECURSIVE) ) {
            if(this_player())
                this_player()->eventPrint("递归更新失败。");
            return 0;
        }
    }
    if( args[<2..] == ".c" ) args = args[0..<3];
    if(virt){
        object virtual = find_object(virt);
        if(virtual) virtual->eventDestruct();
        if(virtual) destruct(virtual);
    }
    ob = find_object(args);
    if(!ob) ob = load_object(args);
    if( ob ) {
        if(this_player() && inherits(LIB_ROOM,ob)){
            string coords = ROOMS_D->GetCoordinates(ob);
            MAP_D->RemoveCache(coords);
        }
        if( tmp = catch( ob->eventDestruct()) && this_player() )
            this_player()->eventPrint(args + ": eventDestruct() 出错");
        if( ob ) destruct(ob);
        if( ob && this_player())
            this_player()->eventPrint(args + ": 销毁旧对象失败。");
    }
    if( args == base_name(this_object()) && this_player() ) {
        this_player()->eventPrint("销毁后无法重新加载更新。\n"
                "它将在下次引用时重新加载。");
        return 0;
    }
    if(!sizeof(args)){
        write("更新错误。");
        return 1;
    }
    tmp = catch(call_other(args, "???"));
    if(this_player() && !(flags & U_AUTOMATED) ){
        if( !tmp )
            this_player()->eventPrint(args + ": 完成");
        else this_player()->eventPrint(args + ": 更新出错\n" + tmp);
    }
    return 1;
}
