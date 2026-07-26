/*    /verbs/common/mail.c
 *    from the Dead Souls Mud Library
 *    mail
 *    mail STR
 *    created by Descartes of Borg 950113
 */



#include <lib.h>
#include <objects.h>
#include "include/mail.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("mail");
    SetRules("","STR");
}

mixed can_mail() { return can_mail_str(""); }

mixed can_mail_str(string str) {
    if( !str ) return 0;
    else if( str == "" ) str = 0;
    if( !creatorp(this_player()) ) {
        mixed tmp;

        tmp = environment(this_player())->CanMail(this_player(), str);
        if( !tmp ) return "这里看起来像邮局吗？";
        else return tmp;
    }
    return 1;
}

mixed do_mail() { return do_mail_str(0); }

mixed do_mail_str(string str) {
    object ob;

    if( !creatorp(this_player()) )
        return environment(this_player())->eventMail(this_player(), str);
    if( !(ob = new(OBJ_POST)) ) {
        this_player()->eventPrint("加载邮件对象失败！");
        return 1;
    }
    if( !(ob->eventMove(this_player())) ) {
        this_player()->eventPrint("你似乎无法携带邮件对象。");
        return 1;
    }
    this_player()->eventPrint("%^RED%^注意！%^RESET%^要结束邮件，请在空行上输入一个句号，然后按回车。");
    ob->start_post(str);
    return 1;
}

string GetHelp(string str) {
    return ("用法：mail\n"
            "      mail <玩家>\n"
            "      mail <群组>\n"
            "      mail <玩家@MUD>\n\n"
            "允许你向本游戏的其他玩家发送邮件。不带参数时，你将阅读邮件。"
            "带参数时，你将创建要发送的邮件。你只能在家乡阅读邮件。"
            "邮件系统会将你发送的邮件正确路由到目标玩家的家乡。\n"
            "另见：mudlist");
}
