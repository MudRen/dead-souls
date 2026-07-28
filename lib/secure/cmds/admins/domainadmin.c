#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string rep, flag, domain, person;
    string write_perms = read_file("/secure/cfg/write.cfg");
    string *tmp_array = explode(write_perms, "\n");
    string *admin_array = ({});
    mapping DomainsMap = ([]);


    if(!archp(previous_object()) || this_player()->GetForced()){
        return "不。";
    }

    if(!args || args == ""){
        write(this_object()->GetHelp());
        return 1;
    }

    if(sscanf(args,"%s %s %s", flag, domain, person) != 3){
        write(this_object()->GetHelp());
        return 1;
    }

    person = lower_case(person);

    if(!user_exists(person)){
        write("无效的人员。");
        return 1;
    }

    if(!directory_exists("/domains/"+domain)){
        write("无效的域。");
        return 1;
    }

    write_perms = replace_string(write_perms, "\n",";\n");

    foreach(string line in tmp_array){
        string where, admins;
        if(sscanf(line,"(/domains/%s/) %s", where, admins)){
            DomainsMap[where] = admins;
            if(sizeof(DomainsMap[domain])) admin_array = explode(DomainsMap[domain],":");
        }
    }

    if(flag == "-a"){

        if(member_array(person, admin_array) != -1){
            write("该人员已经是该域的管理员。");
            return 1;
        }

        else admin_array += ({ person });

        rep = "(/domains/"+domain+"/) "+implode(admin_array, ":");

        if(grepp(write_perms, "(/domains/"+domain+"/)")){
            write_perms = replace_matching_line(write_perms, "/domains/"+domain, rep);
            write_perms = replace_string(write_perms, ";\n","\n");
        }
        else{
            write_perms = replace_string(write_perms, ";\n","\n");
            write_perms = newline_trim(write_perms);
            write_perms += "\n(/domains/"+domain+"/) "+person+"\n";
        }
    }

    else if(flag == "-d"){
        if(member_array(person, admin_array) == -1){
            write("该人员不是该域的管理员。");
            return 1;
        }

        else admin_array -= ({ person });

        if(!sizeof(admin_array)){
            write_perms = remove_matching_line(write_perms, "(/domains/"+domain+"/)",1);
            write_perms = replace_string(write_perms, ";\n","\n");
        }
        else {
            rep = "(/domains/"+domain+"/) "+implode(admin_array, ":");
            write_perms  = replace_matching_line(write_perms, "/domains/"+domain, rep);
            write_perms = replace_string(write_perms, ";\n","\n");
        }
    }

    else {
        write("无效的标志。");
        return 1;
    }

    write_file("/secure/cfg/write.cfg", write_perms, 1);
    update("/secure/daemon/master");
    write("好的。");
    return 1;
}

string GetHelp(string args) {
    return ("语法：domainadmin [-a | -d] <域> <人员>\n\n"
            "此命令管理指定域的写入权限。例如，要授予名为 Snuffy 的创造者 "
            "/domains/SnuffLand 的写入权限，请输入： "
            "\ndomainadmin -a SnuffLand snuffy\n"
            "要撤销该权限：\n"
            "\domainadmin -d SnuffLand snuffy\n"
            "这允许创造者在域的目录中使用 QCS。 "
            "写入权限列在 /secure/cfg/write.cfg 中。\n"
            "另见：domaincreate, admintool");
}
