#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>


inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("dest");
    SetRules("OBS");
    SetErrorMessage("dest什么？");
    SetHelp("语法: dest <OBJ>\n\n"
            "销毁一个对象。\n"
            "另见: zap");
}

mixed can_dest_obj(string str){
    if(!builderp(this_player())) return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed can_dest_str(string str){
    if(!creatorp(this_player())){
        return "对象未找到。";
    }
    return can_dest_obj(str);
}

mixed do_dest_obj(object ob){
    string name, kn, msg;
    if(base_name(ob) == LIB_DUMMY) {
        write(capitalize(ob->GetShort())+"不是普通的可销毁物品。它保持原位。");
        return 1;
    }
    if(archp(ob) && !archp(this_player())){
        write("你不能销毁管理员。");
        tell_player(ob, this_player()->GetName()+"刚刚试图销毁你。");
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(ob), homedir(this_player()))){
        write("作为建造者，你只能销毁你自己创建的物品。");
        return 1;
    }
    if(!living(ob)) name = ob->GetShort();
    else {
        name = ob->GetName();
        if(interactive(ob)) kn = ob->GetKeyName();
    }
    if(kn){
        catch( ob->save_player(kn) );
    }
    msg = this_player()->GetMessage( "dest", ob );
    ob->eventDestruct();
    if(ob) destruct(ob);
    if(!ob){
        write("你销毁了"+name+"。");
        say(msg);
    }
    else {
        write("销毁失败。");
    }
    return 1;
}

mixed do_dest_obs(object *obs) {
    foreach(object ob in obs){
        if(!interactive(ob)) do_dest_obj(ob);
    }
    write("销毁完成。");
    return 1;
}

mixed do_dest_str(string str){
    object ob;
    string tmp;
    if(last(str,2) == "_D"){
        tmp = DEFINES_D->GetDefine(str);
        if(!undefinedp(tmp)) str = tmp;
    }
    tmp = str;
    if(!file_exists(tmp)) tmp += ".c";
    if(!file_exists(tmp)) {
        tmp = this_player()->query_cwd()+"/"+str;
    }
    if(!file_exists(tmp)) tmp += ".c";
    if(!file_exists(tmp)){
        write("对象未找到。");
        return 1;
    }
    ob = find_object(tmp);
    if(!ob){
        write("对象未加载。");
        return 1;
    }
    write("对象: "+identify(ob));
    ob->eventDestruct();
    if(ob) destruct(ob);
    if(ob){
        write("销毁失败。");
        return 1;
    }
    write(str+"已销毁。");
    return 1;
}
