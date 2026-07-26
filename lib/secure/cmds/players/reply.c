//     /secure/cmds/players/reply.c
//     from the Dead Souls mudlib
//     replies to the person who previously told to you
//     created by Descartes of Borg 06 february 1993

#include <lib.h>
#include <commands.h>
#include <talk_type.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string reply,a,b,msg,machine_message,frm;
    object ob, machine;
    mixed err;

    reply = this_player()->GetProperty("reply");
    if(!reply) reply = "no one";
    if(!str) {
        notify_fail("当前回复对象："+capitalize(reply)+"\n");
        return 0;
    }
    if(reply == "no one") {
        notify_fail("当前没有回复对象。\n");
        return 0;
    }
    this_player()->SetProperty("reply_time", time());
    load_object(CMD_TELL)->cmd(reply+" "+str);
    return 1;
}

string GetHelp(){
    return ("命令格式：reply [消息]\n\n"
            "带消息时，回复最后给你发消息的人。"
            "不带消息时，显示当前回复对象是谁。\n"
            "参见：finger, idle, muds, say, shout, tell, yell");
}
