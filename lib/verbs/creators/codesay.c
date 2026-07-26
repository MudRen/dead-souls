/*    /verbs/common/codesay.c
 *    from the Dead Souls  Object Library
 *    codesay
 *    codesay STR
 */

#include <lib.h>
#include <talk_type.h>
#include <commands.h>
#include "include/codesay.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("codesay");
    SetRules("STR");
}

mixed can_codesay() { return "说什么？"; }

mixed can_codesay_str(string str) {
    if( !str ) return 0;
    else return 1;
}

varargs mixed do_codesay_str(string str) {
    string filename = DIR_TMP + "/" + this_player()->GetKeyName() + ".codesay";
    if( !str ) {
        write("什么？");
        return 1;
    }
    if(!creatorp(this_player())) {
        write("这是管理员专用命令。");
        return 1;
    }
    if(strsrch(str,";") == -1){
        write("你代码说道："+"%^BOLD%^CYAN%^"+str+"%^RESET%^");
        say(this_player()->GetCapName()+" 代码说道："+
                "%^BOLD%^CYAN%^"+str+"%^RESET%^");
    }
    else {
        str = replace_string(str, ";", ";\n");
        str = replace_string(str, "{", "{\n");
        str = replace_string(str, "}", "}\n");
        write_file(filename,str,1);
        write_file(filename+"_rule","I",1);
        load_object(CMD_LSED)->cmd(filename+"_rule "+filename);
        write("你代码说道：");
        say(this_player()->GetCapName()+" 代码说道：");
        tell_room(environment(this_player()),"\n"+
                "%^BOLD%^CYAN%^"+read_file(filename)+"%^RESET%^");
    }
    return 1;
}

mixed do_codesay() { return do_codesay_str(); }

string GetHelp() {
    return ("语法：codesay <消息>\n\n"
            "发送一条房间内所有人可见的消息。"
            "此消息会去除普通标点符号，"
            "使需要逐字显示的文本不会引起混淆。"
            "如果消息中包含分号，此命令会尝试"
            "以缩进的LPC风格格式化它。"
            "\n"
            "参见：shout, speak, reply, tell, whisper");
}
