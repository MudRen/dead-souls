#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

string GetHelp();
mixed var, newval;
object ob;

int CheckVar(string var, object ob){
    mixed *vars;
    if(!var || !ob) return 0;
    vars = variables(ob);
    if(member_array(var, vars) == -1) return 0;
    return 1;
}

int cmd(string str) {
    int i;
    mixed ret;
    string cmd, what, tmpstr;

    if(!this_player() || !archp(this_player())){
        write("抱歉，这是一个 arch 命令。");
        return 1;
    }

    if(!str || str == ""){
        write(GetHelp());
        return 1;
    }

    i = sscanf(str,"%s %s %s", cmd, var, what);

    if(i != 3 || (cmd != "get" && cmd != "set")){
        write(GetHelp());
        return i;
    }

    if(cmd == "set"){
        int tmp;
        i = sscanf(what,"%s %s", newval, what);
        if(i != 2){
            write(GetHelp());
            return i;
        }
        if(sscanf(newval,"%d",tmp)) newval = tmp;
    }

    tmpstr = DEFINES_D->GetDefine(what);
    if(tmpstr) what = tmpstr;

    ob = get_object(what);

    if(!ob){
        string path = this_player()->query_cwd()+"/";
        if(last(what,2) != ".c") what += ".c";
        if(file_exists(what)) ob = load_object(what);
        else if(file_exists(path+what)) ob = load_object(path+what);
    }

    if(!ob){
        write(truncate(what,2)+" 未找到。");
        return 1;
    }

    if(!CheckVar(var, ob)){
        write("该对象中不存在该变量。");
        return 1;
    }

    i = catch( ret = evaluate(bind( (: fetch_variable($(var)) :), ob)) );

    if(i){
        write("变量查询出错。");
        return 1;
    }

    write(var+" in "+identify(ob)+" is "+identify(ret));

    if(cmd == "get"){
        return 1;
    }

    if(cmd == "set"){
        evaluate(bind( (: store_variable($(var), $(newval)) :), ob));
        ret = evaluate(bind( (: fetch_variable($(var)) :), ob));
        write(var+" in "+identify(ob)+" is now "+identify(ret));
        return 1;
    }

    write("出错。");
    return 1;
}

string GetHelp(){
    return ("语法：var get <变量名> <对象或文件>\n"
            "        var set <变量名> <新值> <对象或文件>\n\n"
            "设置或获取对象中变量的值。\n"
            "示例：\n"
            "var get isPK me\n"
            "var set Attackable 0 fighter\n\n"
            "请极其谨慎使用。");
}
