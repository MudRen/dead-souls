#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

string new_config_file = "";
string dudename;

mixed cmd(mixed args) {
    string config_file, str;
    string groupname, s1, s2;
    string *line_array;
    string *top_array;
    string *bottom_array;
    string *cles = ({});
    int reload_player, action = 0;
    mapping GroupsMap = ([]);

    if( !this_player() || !(master()->valid_apply(({ "ASSIST" }))) )
        error("Illegal attempt to access groupmod: "+get_stack()+" "+identify(previous_object(-1)));


    if(!args){
        write(read_file("/secure/cfg/groups.cfg"));
        return 1;
    }

    if(sscanf(args,"%s %s",s1,s2) != 2){
        write("参数不足。尝试：help groupmod");
        return 1;
    }

    if(strsrch(args,"-r ") != -1){
        action = -1;
        args = replace_string(args,"-r ","");
    }
    if(strsrch(args,"-a ") != -1){
        action = 1;
        args = replace_string(args,"-a ","");
    }

    if(strsrch(args,"-d ") != -1){
        action = -2;
        args = replace_string(args,"-d ","");
    }
    if(strsrch(args,"-c ") != -1){
        action = 2;
        args = replace_string(args,"-c ","");
    }

    if(sscanf(args,"%s %s",groupname,dudename) == 2 && (abs(action) > 1) ){
        write("此操作参数过多。请尝试：help groupmod。");
        return 1;
    }

    if(sscanf(args,"%s %s",groupname,dudename) != 2 && (abs(action) < 2) ){
        write("此操作参数不足。请尝试：help groupmod。");
        return 1;
    }

    args = upper_case(args);

    top_array = ({});
    bottom_array = ({});

    unguarded( (: cp("/secure/cfg/groups.cfg","/secure/save/backup/groups."+time()) :) );
    config_file = read_file("/secure/cfg/groups.cfg");
    line_array = explode(config_file, "\n");
    if(groupname) str = upper_case(groupname);
    else str = args;
    if(dudename) dudename=(lower_case(dudename));
    line_array = explode(config_file,"\n");
    foreach(string line in line_array){
        string g,m;
        if(sizeof(line)) line = trim(line);
        if(sscanf(line,"(%s)%s",g,m) != 2) 
            if(sscanf(line,"(%s)",g) != 1) continue;
        if(m){
            GroupsMap[g] = explode(trim(m),":");
        }
        else GroupsMap[g] = ({});
    }
    cles = keys(GroupsMap);
    if(str == "ASSIST" || str == "SECURE" ) {
        if(!securep(this_player())){
            write("只有完全管理员才能执行此操作。");
            return 1;
        }
        reload_player = 1;
    }

    if(!GroupsMap[str] && (abs(action) < 2)){
        write("没有这样的组。");
        return 1;
    }

    if(!action){
        write("我不理解您的意图。请指定");
        write("您想要的操作：-r、-a、-d 或 -c");
        return 1;
    }

    if(action == 1){
        if(member_array(dudename,GroupsMap[str]) != -1){
            write("该人员已经是该组的成员。");
            return 1;
        }
        if(member_array(str,cles) != -1 && !sizeof(GroupsMap[str])) GroupsMap[str] = ({});
        GroupsMap[str] += ({ dudename });
        write("组 "+str+" 现在包含以下成员：\n "+
                implode(GroupsMap[str],":"));
    }

    if(action == -1){
        if(member_array(dudename,GroupsMap[str]) == -1){
            write("该人员已经不是该组的成员。");
            return 1;
        }
        if((str == "ASSIST" || str == "SECURE") && dudename == this_player()->GetKeyName() ) {
            write("此命令不允许您将自己从 SECURE 或 ASSIST 组中移除。");
            return 1;
        }
        GroupsMap[str] -= ({ dudename });
        write("组 "+str+" 现在包含以下成员：\n "+
                implode(GroupsMap[str],":"));
    }

    if(action == -2){
        if(member_array(args,cles) == -1){
            write("该组不存在。");
            return 1;
        }
        if(args == "ASSIST" || args == "SECURE" ) {
            write("我不会执行此操作。您需要手动清理您的MUD。");
            return 1;
        }
        map_delete(GroupsMap,args);
        write("组已删除。");
    }

    if(action == 2){
        if(member_array(args,cles) != -1){
            write("该组已存在。");
            return 1;
        }
        GroupsMap[args] = ({});
        write("组已添加。");
    }

    foreach(string key, mixed val in GroupsMap){
        new_config_file += "("+key+") "+implode(GroupsMap[key],":")+"\n";
    }
    unguarded( (: write_file("/secure/cfg/groups.cfg",new_config_file,1) :) );
    load_object("/secure/cmds/creators/update")->cmd("/secure/daemon/master");
    load_object("/secure/cmds/creators/update")->cmd("/secure/lib/connect");
    if(str == "SNOOPER") SNOOP_D->SnoopClean();
    new_config_file = "";
    if(reload_player){
        object player = unguarded((: find_player(dudename) :));
        if(player){
            tell_player(player, "您的组成员身份发生了重要变更。\n\n"+
                    "您的用户对象将在稍后被重新加载。\n\n");
            RELOAD_D->eventReload(player, 3);
        }
    }
    dudename = "";
    return 1;
}

string GetHelp() {
    return ("语法：groupmod [-a|-r] <组名> <人名> \n"
            "        groupmod [-c|-d] <组名>\n\n"
            "修改 /secure/cfg/groups.cfg 中的组信息。\n"
            "创建名为 MUDKIPZ 的组：groupmod -c mudkipz\n"
            "将 Yotsuba 添加为该组成员："
            "groupmod -a mudkipz yotsuba");
}
