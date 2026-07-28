#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>
mixed mx;
mixed next;
object *dudes;
string filename, args;

varargs mixed reload(mixed ob, int recursive, int quiet){
    mapping StringFellows = ([]);
    int stringed;
    object env;
    mx = 0;

    if(RELOAD_D->GetWarmBootInProgress()){
        reset_eval_cost();
    }

    if(!ob) return 0;
    if(objectp(ob) && inherits(LIB_DAEMON,ob) && !ob->GetDoor()){
        string obname = base_name(ob)+".c";
        ob->eventDestruct();
        if(ob) destruct(ob);
        return load_object(obname);
    }
    if(objectp(ob) && environment(ob)) env = environment(ob);
    if(stringp(ob)) {
        stringed = 1;
        filename = ob;
        if(!grepp(filename,"#") && last(filename,2) != ".c") filename += ".c";
        ob = find_object(filename);
        if(!ob) ob = load_object(filename);
    }

    if(!ob || !objectp(ob)){
        if(!quiet) write("对象不存在。");
        return 0;
    }

    if(ob->GetDoor() && sizeof(ob->GetDoor())) {
        ob = load_object(ob->GetDoor());
    }

    if(!file_exists(base_name(ob))) filename = base_name(ob)+".c";
    else filename = base_name(ob);
    if(!file_exists(filename)){
    }
    if(recursive) args = "-a -r ";
    else args = "-a "; 
    if(!grepp(unguarded( (: read_file(filename) :) ),"void init()" || !grepp(unguarded( (: read_file(filename) :) ),"::init()"))) { 
        if(clonep(ob) && !inherits(LIB_ROOM,ob)){
            if(!strsrch(filename,"/lib/") || ob->isDummy() || inherits(LIB_DAEMON,ob)) true(); 
            else if(!quiet)
                write("此对象缺少有效的 init 函数。"
                        "请尽快对其运行 initfix。");
        }
    }
    if(inherits(LIB_ROOM,ob)){
        dudes = get_livings(ob,1);
        if(dudes) {
            foreach(object fellow in dudes){
                string ubi = fellow->GetProperty("LastLocation");
                if(ubi) StringFellows[fellow->GetKeyName()] = ubi;
            }
        }
        unguarded( (: mx = catch(load_object(CMD_UPDATE)->cmd(args + filename)) :) );
        if(mx && !quiet) {
            write("更新一个或多个文件时似乎出现了问题。");
            write("重载失败。");
        }
        else {
            if(dudes) {
                dudes->eventMove(filename);
                foreach(object fellow in dudes){
                    if(sizeof(StringFellows[fellow->GetKeyName()])){
                        fellow->SetProperty("LastLocation",StringFellows[fellow->GetKeyName()]);
                    }
                }
            }
            if(!quiet) write("重载完成。");
        }
        StringFellows = ([]);
        return 1;
    }
    mx = unguarded( (: load_object(CMD_UPDATE)->cmd(args + " "+ filename) :) );
    if((!mx || !intp(mx) || mx == 0) && !quiet) {
        write("更新一个或多个文件时似乎出现了问题。");
        write("重载失败。");
        return 0;
    }

    if(ob && !inherits(LIB_DOOR, ob) && !stringed && env) {
        unguarded( (: next = clone_object(filename) :) ); 
        ob->eventMove(ROOM_FURNACE);
        if(next && objectp(next) && env) next->eventMove(env);
    }
    if(!quiet && this_player()) write("完成。");
    return 1;
}
