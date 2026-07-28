#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

string GetHelp();
object ob;
string ele;

mixed cmd(string str) {
    int i;
    mixed justvars, tmp;
    string cmd, what, ret = "";;

    if(!this_player() || !archp(this_player())){
        write("抱歉，这是一个 arch 命令。");
        return 1;
    }

    if(!str || str == ""){
        return GetHelp();
    }

    tmp = DEFINES_D->GetDefine(str);
    if(tmp) str = tmp;

    what = str;
    ob = to_object(what);

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

    justvars = variables(ob);

    foreach(ele in justvars){
        string thing = replace_string(str," ","_");
        thing = replace_string(thing,"/","_");
        i = catch( tmp = evaluate(bind( (: fetch_variable($(ele)) :), ob)) );
        if(!i){
            write(ele + " " + identify(tmp));
            write_file("/secure/tmp/"+thing, ele + " " + identify(tmp)+"\n");
        }
    }
    return 1;
}

string GetHelp(){
    return ("语法：vars <对象或文件>\n\n"
            "输出对象的所有变量及其值。\n"
            "示例：\n"
            "vars kim\n"
            "vars /daemon/classes\n"
            "另见：var, variables");
}
