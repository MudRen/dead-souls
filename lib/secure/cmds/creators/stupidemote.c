/*    /secure/cmds/admins/stupidemote.c
 *    From the Dead Souls Mud Library
 *    Adds lame emotes
 *    Created by Descartes of Borg 961214
 *    Version: @(#) stupidemote.c 1.4@(#)
 *    Last modified: 96/12/15
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args){
    string* rules = ({ "", "STR" });
    string* adverbs;
    string emote, xtra, prep;
    if( !(master()->valid_apply(({ "ASSIST" }))) &&
            !member_group(this_player(), "EMOTES") ){
        write("你不是管理员，也不是EMOTES组的成员。");
        return 1;
    }

    if( !args || args == "" ) {
        return "要添加哪个表情？";
    }
    if( sscanf(args, "%s %s", emote, xtra) != 2 ) {
        emote = args;
        xtra = 0;
    }
    if( xtra ) {
        if( xtra == "LIV" || xtra == "LVS" ) {
            prep = 0;
        }
        else {
            string token;

            if( strlen(xtra) < 5 ) {
                return "表达式 " + xtra + " 无意义。";
            }
            prep = xtra[0..<5];
            token = xtra[<3..];
            if( member_array(prep, master()->parse_command_prepos_list()) ==
                    -1 ) {
                return "介词 " + prep + " 无效。";
            }
            if( member_array(token, ({ "LIV", "LVS" })) == -1 ) {
                return "标记 " + token + " 无效。";
            }
            rules = ({ rules..., token });
        }
        rules = ({ rules..., xtra, "STR " + xtra, xtra + " STR" });
    }
    else {
        prep = 0;
    }
    if( !SOUL_D->AddVerb(emote, capitalize(emote) + " how?") ) {
        previous_object()->eventPrint("创建表情失败。");
        return 1;
    }
    foreach(string rule in rules) {
        string msg;

        if( rule == "" ) {
            msg = "$agent_name $agent_verb.";
            adverbs = 0;
        }
        else if( rule == "STR" ) {
            msg = "$agent_name $agent_verb $adverb.";
            adverbs = ({ "-" });
        }
        else if( rule == "LIV" || rule == "LVS" || rule == xtra ) {
            if( prep ) {
                msg = "$agent_name $agent_verb " + prep + " $target_name.";
            }
            else {
                msg = "$agent_name $agent_verb $target_name.";
            }
        }
        else {
            if( prep ) {
                msg = "$agent_name $agent_verb $adverb " + prep +
                    " $target_name.";
            }
            else {
                msg = "$agent_name $agent_verb $target_name $adverb.";
            }
        }
        if( adverbs ) {
            SOUL_D->AddRule(emote, rule, ({ ({ emote }), msg }), adverbs);
        }
        else {
            SOUL_D->AddRule(emote, rule, ({ ({ emote }), msg }));
        }
    }
    previous_object()->eventPrint("简单表情已添加。");
    return 1;
}

string GetHelp(){
    return ("语法: stupidemote <表情> [规则]\n\n"
            "你必须是管理员或 EMOTES 组成员才能使用此命令。\n"
            "此命令允许你直接从命令行添加最常见的表情类型。\n"
            "使用第一种语法，你可以添加简单的无目标表情。例如，\n"
            "执行 <stupidemote cheese> 会创建一个表情，\n"
            "允许玩家执行 <cheese> 和 <cheese 副词>，\n"
            "消息类似于 \"Descartes cheeses.\"\n"
            "第二种语法用于有目标的表情。你需要指定一个目标规则。\n"
            "目标规则可以是以下之一:\n"
            "\t* LIV（单个生物）\n"
            "\t* LVS（多个生物）\n"
            "\t* 介词 LIV\n"
            "\t* 介词 LVS\n"
            "LIV 和 LVS 的区别在于表情是面向单个生物还是多个生物。\n"
            "例如，添加 \"smile\" 表情:\n"
            "> stupidemote smile at LVS\n\n"
            "另见: addadverb, addemote, removeadverb, removeemote");
}
