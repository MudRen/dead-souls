/*    /secure/cmds/admins/removeemote.c
 *    From the Dead Souls Mud Library
 *    Command for removing commands from the soul
 *    Created by Descartes of Borg 961214
 *    Version: @(#) removeemote.c 1.2@(#)
 *    Last modified: 96/12/14
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args){
    string verb, rule;
    if( !(master()->valid_apply(({ "ASSIST" }))) &&
            !member_group(this_player(), "EMOTES") ){
        write("你不是管理员，也不是EMOTES组的成员。");
        return 1;
    }

    if( !args || args == "" ) {
        return "要移除哪个表情？";
    }
    if( sscanf(args, "%s %s", verb, rule) != 2 ) {
        verb = args;
        rule = 0;
    }
    if( !rule ) {
        if( !SOUL_D->RemoveVerb(verb) ) {
            previous_object()->eventPrint("删除动词失败。");
            return 1;
        }
        previous_object()->eventPrint("动词已删除。");
    }
    else {
        if( !SOUL_D->RemoveRule(verb, rule) ) {
            previous_object()->eventPrint("删除规则失败。");
            return 1;
        }
        previous_object()->eventPrint("规则已删除。");
    }
    return 1;
}

string GetHelp(){
    return ("语法: removeemote <表情> [规则]\n\n"
            "允许你从 soul 中移除一个表情或表情的规则。\n"
            "如果指定了规则，只移除该规则。\n"
            "如果未指定规则，则移除整个表情。\n\n"
            "你必须是管理员或 EMOTES 组成员才能使用此命令。\n"
            "另见: addadverb, addemote, removeadverb");
}
