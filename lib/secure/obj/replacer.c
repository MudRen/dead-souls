// string replacer, by Cratylus.
// Use this carelessly at your own peril.

#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_TURN;

string a1,a2,a3,line;
int n, active;

private void validate() {
    if(!this_player()) return 0;
    if( !(master()->valid_apply(({ "SECURE" }))) || !securep(this_player()))
        error("Illegal attempt to use replacer: "+get_stack()+" "+identify(previous_object(-1)));
}

void create(){
    ::create();
    SetKeyName("string replacer");
    SetId(({"replacer","thing","gadget","string replacer","device"}));
    SetShort("字符串替换器");
    SetLong("这是MUD上最危险的设备。\n"+
            "它允许你替换文件中的字符串。\n"+
            "要使用它，你必须先\"turn on replacer\"\n"+
            "然后你有两个选择：\n"+
            "替换一个文件中的单词：replace <文件名> <旧词> <新词>\n"+
            "替换当前工作目录中每个文件中的单词：\n autorep <旧词> <新词>\n\n"+
            "它不能很好地处理空格或特殊字符。使用带有括号、方括号或"+
            "英语字母以外的任何内容的字符串可能会产生意想不到的结果。"+
            "\n%^RED%^%^BOLD%^仅供管理员使用！%^RESET%^");
    SetMass(20);
    SetValue(10);
    SetVendorType(VT_TREASURE);
    active = 0;
}

void init(){
    add_action("rep_string","replace");
    add_action("autorep","autorep");
}

int eventActivate(){
    validate();
    write("随着一声诡异的轰鸣，字符串替换器启动了。你感到了巨大的危险。");
    write("\n\n警告：你当前的工作目录是：\n\n");
    write(this_player()->query_cwd()+"\n\n");
    say(this_player()->GetName()+"打开了字符串替换器，你听到一声奇异的、不属于人间的轰鸣，大地为之颤抖。");
    active = 1;
    return 1;
}

int eventDeactivate(){
    validate();
    write("字符串替换器伴随着奇特的机械声关闭了。你感觉安全了。");
    say(this_player()->GetName()+"的字符串替换器关闭了。");
    active = 0;
    return 1;
}

varargs mixed eventTurn(string str){
    validate();
    if( this_player() != environment() ) { write("你没有那个物品。"); return 0; }
    write("你把替换器拿在手中翻来覆去。");
    say(this_player()->GetKeyName()+"在手中翻转着字符串替换器。");
    return 1;
}

int eventTurnOn(object ob){
    validate();

    if( this_player() != environment() ) { write("你没有那个物品。"); return 0; }

    if(!creatorp(this_player())) {
        write("此设备非凡人可用。");
        return 0;
    }

    if(active){
        write("它已经打开了。");
        return 0;
    }
    else eventActivate();

    return 1;
}

varargs mixed eventTurnOff(string str){
    validate();
    if( this_player() != environment() ) { write("你没有那个物品。"); return 0; }
    if(!active){
        write("它已经关闭了。");
        return 0;
    }
    else eventDeactivate();

    return 1;
}

int autorep(string str){
    string dir, a1, a2;
    string *listing;

    validate();
    if(!active){
        write("字符串替换器未开启。");
        return 1;
    }

    if( !str || str=="" || sscanf(str,"%s %s",a1,a2) != 2){
        write("语法：autorep <旧词> <新词>\n");
        eventDeactivate();
        return 1;
    }
    dir=this_player()->query_cwd()+"/";
    listing=get_dir(dir);
    foreach(string file in listing){
        if(file_size(dir+file) > 0) this_object()->rep_string(file+" "+str);
    }
    eventDeactivate();
    return 1;
}

int rep_string(string str){
    string dir,file,tempfile,backup;
    int valid_line;

    validate();
    if(!active){
        write("字符串替换器未开启。");
        return 1;
    }

    valid_line=1;
    n=1;
    if( !str || str==""){
        write("语法：replace <文件名> <旧词> <新词>\n");
        eventDeactivate();
        return 1;
    }
    if(sscanf(str,"%s %s %s",a1,a2,a3) == 3){
        dir=this_player()->query_cwd()+"/";
        file=dir+a1;

        if(file_size(file) <= 0 ) {
            write("无效的文件名。");
            eventDeactivate();
            return 1;
        }

        tempfile="/tmp/"+lower_case(this_player()->GetName())+".TempReplace";
        backup="/tmp/"+lower_case(this_player()->GetName())+"."+a1+".bak";
        if(file_size(backup)){ rm(backup); }
        if(file_size(tempfile)){ rm(tempfile); }
        write("在 "+a1+" 中搜索字符串："+a2+"。\n");
        while(valid_line){
            line=read_file(file, n, 1);
            if(!line || line=="") valid_line=0;
            this_object()->replace(line);
            if(line) write_file(tempfile,line);
            n++;
        }
        cp(file, backup);
        cp(tempfile, file);
        if(file_size(backup)){ rm(backup); }
        if(file_size(tempfile)){ rm(tempfile); }
        write("替换完成。文件 "+file+" 已修改。\n");
        if(query_verb() == "replace") eventDeactivate();
        return 1;
    }
    write("语法：replace <文件名> <旧字符串> <新字符串>\n");
    eventDeactivate();
    return 1;
}

int replace(string str){
    string s1,s2;
    validate();
    if(sizeof(str) && sscanf(str,"%s"+a2+"%s",s1,s2)>1){
        line=s1+a3+s2;
        write("在第 "+n+" 行找到字符串。替换为："+a3+"。\n");
        this_object()->replace(line);
    }
    return 1;
}
