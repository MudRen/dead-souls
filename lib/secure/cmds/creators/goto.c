/*    /cmds/creator/goto.c
 *    from the Dead Souls LPC Library
 *    a command to take a cre anywhere in the game
 *    created by Descartes of Borg 930906
 *    modified for NM IV 950331
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    object ob, dude;
    int err;
    string tmp;

    if(!str) return "去哪里？";
    tmp = DEFINES_D->GetDefine(str);
    if(tmp) str = tmp;
    ob = find_player(lower_case(str));
    if(ob) dude = ob;
    if(ob && objectp(ob) && (!ob->GetInvis() || !archp(ob)) && 
            ob = room_environment(ob)) {
        if(ob == room_environment(this_player())) {
            message("my_action", "你抽动了一下。", this_player());
            if(hiddenp(this_player())) return 1;
            message("other_action", this_player()->GetName()+
                    "抽动了一下。", ob, ({ this_player() }));
            return 1;
        }
    }
    if(ob && ob->GetInvis() && creatorp(ob) && !archp(this_player())) ob = 0;
    if(!ob) str = absolute_path(this_player()->query_cwd(), str);
    if(ob) {
        this_player()->eventMoveLiving(ob);
        return 1;
    }

    if(last_string_element(path_prefix(path_prefix(str)),"/") != "virtual"){
        int x, y, z;
        string file = last_string_element(str,"/");
        if(sscanf(file,"%d,%d,%d", x, y, z) != 3)
            sscanf(file,"%d,%d", x, y);
        if(!undefinedp(x) && !undefinedp(y)){
            mixed rmap = ROOMS_D->GetGrid(file);
            if(rmap && rmap["room"]){
                if(!file_exists(str) && !file_exists(str + ".c")){
                    str = rmap["room"];
                }
            }
        }
        else if(!file_exists(str) && !file_exists(str + ".c")){
            str == lower_case(str);
            if(str == "home" || str == "workroom"){
                write("试试: help home");
            }
            else write("未找到该位置。");
            return 1;
        }
    }

    err = catch( ob = load_object(str) );
    if(err || !ob) {
        write("\n\n无法加载该位置。");
        return 1;
    }
    else this_player()->eventMoveLiving(ob);
    return 1;
}

string GetHelp() {
    return ("语法: goto [生物|文件]\n\n"
            "此命令会将你移动到指定生物所在的位置（如果能找到的话），\n"
            "否则搜索指定文件并尝试将你移入该文件。\n"
            "另见: home, move, trans, expel");
}
