/* memo pad by Cratylus @ Frontiers
 * Sep 21 2005
 */

int read_memo(string str);
int help_msg();

string ReadFun(mixed args...){
    help_msg();   
    return "";
} 

#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
int dirchecked;
string ownerstr,capownerstr,fileread;
object ownerob;
void create(){
    ::create();
    SetKeyName("memo pad");
    SetId( ({"pad","memo","memo pad","notepad"}) );
    SetShort("黄色便签本");
    SetLong("一本可以写备忘录的黄色便签本。上面似乎写着使用说明。");
    SetMass(20);
    SetVendorType(VT_TREASURE);
    SetItems(([ ({"instruction", "instructions", "words"}) : "解释如何使用便签本的文字。试试：read instructions on notepad。",
                ]) );
    SetRead( ([ ({"instruction", "instructions", "words"}) : (: ReadFun :),
                "default" : (: read_memo :),
                ]) );
}

void init(){
    ::init();
    add_action("memo","memo");
    add_action("clean_memo","fresh");
    add_action("erase_memo","erase");
    ownerob=environment(this_object());
    if(living(ownerob)) capownerstr=capitalize(ownerob->GetKeyName());
    if(capownerstr) ownerstr=lower_case(capownerstr);
    dirchecked=0;
}
int memo(string str){
    if(!dirchecked){
        this_object()->checkdir();
    }
    if(!str){
        write("你没有在便签本上写任何东西。\n");
        return 1;
    }
    write_file(homedir(this_player())+"/log/memo",str+"\n");
    write("你在便签本上添加了一条备忘录。\n");
    say(capownerstr+"在"+possessive(this_player())+"便签本上涂写着。");
    return 1;
}
int read_memo(mixed str...){
    if(!dirchecked){
        this_object()->checkdir();
    }
    fileread=read_file(homedir(this_player())+"/log/memo");
    if(!fileread){
        write("便签本是空白的。\n");
        write("查看说明：read instructions on memo pad");
        return 1;
    }
    write("便签本上写着：\n"+fileread+"\n");
    say(capownerstr+"翻阅着"+possessive(this_player())+"的便签本。\n");
    return 1;
}
int help_msg(){
    write("便签本背面写着：\n\n"+
            "cReMem 便签本，满足你的笔记需求！便签本命令：\n"+
            "----------\n"+
            "memo <内容>   : 将<内容>写入便签本。\n"+
            "read memo      : 阅读便签本的内容。\n"+
            "----------\n");
    say(capownerstr+"阅读着便签本的背面。\n");
    return 1;
}
int checkdir(){
    if(file_size(homedir(this_player())+"/log") != -2) mkdir(homedir(this_player())+"/log");
    dirchecked=1;
    return 1;
}
