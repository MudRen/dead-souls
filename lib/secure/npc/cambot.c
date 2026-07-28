#include <lib.h>
#include <position.h>

inherit LIB_SENTIENT;
inherit LIB_TURN;
int recording;
string baseshort, recfile, gstr, gstr2;
mixed owner;

protected void create() {
    sentient::create();
    SetKeyName("cambot");
    SetId( ({"bot", "robot"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("摄像机器人");
    SetLong("这是一个金属球体，直径约一英尺，表面装有许多镜头。");
    SetPosition(POSITION_FLYING);
    SetLevel(1);
    SetPacifist(1);
    SetNoClean(1);
    SetRace("bot");
    SetClass("observer");
    SetGender("neuter");
    SetPolyglot(1);
    baseshort = GetShort();

}

void init(){
    ::init();
    add_action("SetRecordingFile","setfile");
}

protected mixed SetOwner(mixed foo){
    owner = foo;
    return owner;
}

mixed GetOwner(){
    return owner;
}

int SetRecordingFile(string str){
    string pprefix, filename;
    if(!sizeof(str) && sizeof(recfile)){
        write("当前录制文件为: "+recfile);
        return 1;
    }
    if(!sizeof(str)){
        str = truncate(generate_tmp(),2)+".txt";
    }
    if(directory_exists(str)){
        write("请指定一个文件，而不是目录。");
        return 1;
    }
    pprefix = path_prefix(str);
    if(!directory_exists(pprefix)){
        write("这不是一个有效的路径。");
        return 1;
    }
    filename = last_string_element(str);
    gstr2 = str;
    if(!check_privs(this_player(),str) || !unguarded( (: write_file(gstr2,"New log: "+timestamp()+"\n") :) )){
        write("这不是一个有效的路径。");
        return 1;
    }
    if(last(str,2) == ".c" || last(str,2) == ".h" ||
            last(str,4) == ".cfg"){
        write("该文件的扩展名不支持录制。");
        return 1;
    }
    recfile = str;
    owner = previous_object();
    write("录制文件设置为: "+recfile);
    unguarded( (: write_file(recfile,"New log: "+timestamp()+"\n") :) );
    return 1;
}

void catch_tell( string message ){
    this_object()->receive_message("catch_tell",message);
}

void receive_message(string s1, string s2){
    if(s2){
        gstr = replace_string(s2,"%^CYAN%^","");
        gstr = replace_string(gstr,"%%^^CYAN%%^^","");
        if(recording) unguarded( (: write_file(recfile,timestamp()+": "+gstr+"\n") :) );
    }
}

varargs mixed eventHearTalk(object who, object target, int cls, string verb,
        string msg, string lang) {
    this_object()->receive_message("me",who->GetName()+" "+verb+"s: "+msg) ;
    return;
}

varargs int doPrint(string msg, string msg_class){
    this_object()->receive_message("me again",msg) ;
    return 1;
}

varargs int eventPrint(string msg, string msg_class){
    doPrint( msg, msg_class) ;
    return 1;
}

int eventTurnOn(object ob){
    if(this_player() != environment()  && environment(this_player()) !=environment()) {
        write("它不在您的触及范围内。");
        return 1;
    }
    if(!archp(this_player())){
        write("这是管理员级别的摄像机器人。你不能摆弄它。");
        return 0;
    }
    if(!recording){
        write("你打开了摄像机器人。");
        say(this_player()->GetName()+"打开了摄像机器人。");
        SetShort(baseshort+" %^BOLD%^RED%^%^FLASH%^recording%^RESET%^");
        if(!sizeof(recfile)) recfile = truncate(generate_tmp(),2)+".txt";
        write("录制文件为: "+recfile);
        unguarded( (: write_file(recfile,"New log: "+timestamp()+"\n") :) );
        recording = 1;
        return 1;
    }
    if(recording){
        write("它已经开启了。");
        return 1;
    }
}

varargs mixed eventTurnOff(string str){
    if(this_player() != environment()  && environment(this_player()) !=environment()) { write("它不在您的触及范围内。"); return 1; }
    if(!archp(this_player())){
        write("这是管理员级别的摄像机器人。你不能摆弄它。");
        return 0;
    }
    if(recording){
        write("你关闭了摄像机器人。");
        say(this_player()->GetName()+"关闭了摄像机器人。");
        SetShort(baseshort);
        recording = 0;
        return 1;
    }
    if(!recording){
        write("它已经关闭了。");
        return 1;
    }
}

int eventDestruct(){
    if(!this_player()) return 0;
    if(!archp(this_player())){
        write("这是管理员级别的摄像机器人。您不能摆弄它。");
        return 0;
    }
    else return sentient::eventDestruct();
}

int eventDie(){
    if(!this_player()) return 0;
    if(!archp(this_player())){
        write("这是管理员级别的摄像机器人。您不能摆弄它。");
        this_object()->AddHP(1000);
        return 0;
    }
    else return sentient::eventDie();
}

int eventForce(string str){
    if(!this_player()) return 0;
    if(!archp(this_player())){
        write("这是管理员级别的摄像机器人。您不能摆弄它。");
        return 0;
    }
    else return sentient::eventForce(str);
}

int eventMove(mixed dest){
    if(recording){
        write("摄像机器人在录制模式下无法移动。");
        return 0;
    }
    else return sentient::eventMove(dest);
}

int eventMoveLiving(mixed dest){
    if(recording){
        write("摄像机器人在录制模式下无法移动。");
        return 0;
    }
    else return sentient::eventMoveLiving(dest);
}

