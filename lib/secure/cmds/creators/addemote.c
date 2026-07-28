/*    /secure/cmds/admins/addemote.c
 *    From the Dead Souls Mud Library
 *    A sane command for doing emote addition
 *    Created by Descartes of Borg 961208
 *    Version: @(#) addemote.c 1.2@(#)
 *    Last modified: 96/12/14
 */

#include <lib.h>
#include <daemons.h>
#include <message_class.h>

inherit LIB_DAEMON;

protected void MainMenu();
protected void EditErrorMessage(string emote);
protected void ShowEmote(string emote);
protected void AddEmote(string emote);
protected void AddRule(string rule, string emote);

private void validate() {
    if(!this_player()) return 0;
    if( !(master()->valid_apply(({ "ASSIST" }))) &&
            !member_group(this_player(), "EMOTES") )
        error("Illegal attempt to access addemote: "+get_stack()+" "+identify(previous_object(-1)));
}

protected void EnterEmote(string emote, string* emotes) {
    int x = to_int(emote);
    validate();
    if( x < 1 || x > sizeof(emotes) ) {
        if( member_array(emote, emotes) == -1 ) {
            if( emote[0] == 'q' ) {
                return;
            }
            MainMenu();
            return;
        }
    }
    else {
        emote = emotes[x-1];
    }
    ShowEmote(emote);
}

protected void EnterEditChoice(string str, string* rules, string emote) {
    int x = to_int(str);
    validate();
    if( x < 1 || x > sizeof(rules) ) {
        if( member_array(str, rules) == -1 ) {
            if( !str || str == "" ) {
                MainMenu();
                return;
            }
            if( str[0] == 'q' ) {
                return;
            }
            else if( str[0] == 'e' ) {
                EditErrorMessage(emote);
                return;
            }
            else if( str[0] == 'a' ) {
                this_player()->eventPrint("输入动词规则: ", MSG_PROMPT);
                input_to((: AddRule :), emote);
                return;
            }
            else {
                ShowEmote(emote);
                return;
            }
        }
        AddRule(str, emote);
    }
    else {
        AddRule(rules[x-1], emote);
    }
}

protected void AddAdverbs(string adv, string emote, string* rules,
        string* verbs, string msg) {
    string* adverbs;
    validate();
    if( !adv || adv == "" ) {
        adverbs = ({});
    }
    else {
        adverbs = map(explode(adv, ","), (: trim :));
    }
    foreach(string rule in rules) {
        SOUL_D->AddRule(emote, rule, ({ verbs, msg }), adverbs);
    }
    this_player()->eventPrint("表情 '" + emote + "' 已添加。");
}

protected void AddMessage(string msg, string emote, string* rules,
        string* verbs) {
    validate();
    if( !msg || msg == "" ) {
        this_player()->eventPrint("哪个消息？[q 退出] ", MSG_PROMPT);
        input_to((: AddMessage :), emote, rules, verbs);
        return;
    }
    if( lower_case(msg) == "q" ) {
        this_player()->eventPrint("添加规则已中止。");
        return;
    }
    this_player()->eventPrint("输入副词: ", MSG_PROMPT);
    input_to((: AddAdverbs :), emote, rules, verbs, msg);
}

protected void AddVerbs(string list, string emote, string* rules) {
    string* verbs = map(explode(list, ","), (: trim :));
    validate();

    this_player()->eventPrint("输入消息: ", MSG_PROMPT);
    input_to((: AddMessage :), emote, rules, verbs);
}

protected void AddRule(string rule, string emote) {
    string* rules = map(explode(rule, ","), (: trim :));
    validate();

    if( !sizeof(rules) ) {
        rules = ({ "" });
    }
    this_player()->eventPrint("输入动词: ", MSG_PROMPT);
    input_to((: AddVerbs :), emote, rules);
}

protected void AddErrorMessage(string msg, string emote) {
    validate();
    if( !msg || msg == "" ) {
        this_player()->eventPrint("哪个消息？[q 退出] ", MSG_PROMPT);
        input_to((: AddErrorMessage :), emote);
        return;
    }
    if( !emote || emote == "" ) {
        this_player()->eventPrint("哪个表情？[q 退出] ", MSG_PROMPT);
        input_to((: AddEmote :));
        return;
    }
    emote = lower_case(emote);
    if( lower_case(msg) == "q" ) {
        this_player()->eventPrint("添加表情已中止。");
        return;
    }
    SOUL_D->AddVerb(emote, msg);
    this_player()->eventPrint("输入 " + emote + " 的解析规则: ",
            MSG_PROMPT);
    input_to((: AddRule :), emote);
}

protected void AddEmote(string emote) {
    validate();
    if( !emote || emote == "" ) {
        this_player()->eventPrint("哪个表情？[q 退出] ", MSG_PROMPT);
        input_to((: AddEmote :));
        return;
    }
    emote = lower_case(emote);
    if( emote == "q" ) {
        this_player()->eventPrint("添加表情已中止。");
        return;
    }
    this_player()->eventPrint("输入错误消息: ", MSG_PROMPT);
    input_to((: AddErrorMessage :), emote);
}

protected void MainMenu() {
    string* emotes = SOUL_D->GetEmotes();
    string* display = allocate(sizeof(emotes));
    int* screen = this_player()->GetScreen() || ({ 80, 25 });
    string tmp;
    int i;
    validate();

    tmp = center("Dead Souls 表情编辑器", screen[0]) + "\n";
    for(i=0; i<sizeof(display); i++) {
        display[i] = "[" + (i+1) + "] " + emotes[i];
    }
    tmp += format_page(display, screen[0]/17) + "\n";
    this_player()->eventPrint(tmp, MSG_SYSTEM);
    this_player()->eventPrint("输入表情编号或 'q' 退出: ", MSG_PROMPT);
    input_to((: EnterEmote :), emotes);
}

protected void EditErrorMessage(string emote) {
    validate();
    this_player()->eventPrint("输入新的错误消息: ", MSG_PROMPT);
    input_to(function(string str, string emote) {
            if( str && str != "" ) {
            SOUL_D->SetErrorMessage(emote, str);
            }
            ShowEmote(emote);
            }, emote);
}

protected void ShowEmote(string emote) {
    string err = SOUL_D->GetErrorMessage(emote);
    mapping rules = SOUL_D->GetRules(emote);
    int* screen = this_player()->GetScreen() || ({ 80, 25 });
    string tmp = center("Dead Souls Emote Editor", screen[0]) + "\n\n";
    string tmp2 = "";
    string* rule_array = allocate(sizeof(rules));
    int i = 0;
    validate();

    tmp += "%^GREEN%^表情%^RESET%^: " + emote + "\n";
    tmp += "%^GREEN%^错误消息%^RESET%^: " + err + "\n";
    tmp += "%^GREEN%^规则%^RESET%^:\n";
    foreach(string rule, mixed* data in rules) {
        rule_array[i] = rule;
        tmp += "[" + (i+1) + "] \"" + rule + "\": " + data[1][1] + "\n";
        tmp += "  副词: " + wrap(item_list(data[0]), screen[0]) + "\n";
        i++;
    }
    //Following fix courtesy of Alecksy
    this_player()->eventPage(explode(tmp,"\n"), MSG_SYSTEM);
    tmp2 = "输入要编辑的规则编号，'a' 添加规则，'e' 编辑错误消息，'q' 退出: ";
    this_player()->eventPrint(tmp2,MSG_PROMPT);
    input_to( (: EnterEditChoice :), rule_array, emote );
}

mixed cmd(string args) {
    if( !(master()->valid_apply(({ "ASSIST" }))) &&
            !member_group(this_player(), "EMOTES") ){
        write("你不是管理员，也不是EMOTES组的成员。");
        return 1;
    }

    if( !args || args == "" ) {
        this_player()->eventPrint("输入表情名称: ", MSG_PROMPT);
        input_to((: AddEmote :));
    }
    else if( args[0] == '-' ) {
        if( args == "-edit" ) {
            MainMenu();
        }
        else if( args == "-add") {
            this_player()->eventPrint("输入表情名称: ", MSG_PROMPT);
            input_to((: AddEmote :));
        }
        else {
            MainMenu();
        }
    }
    else {
        if( member_array(args, SOUL_D->GetEmotes()) == -1 ) {
            AddEmote(args);
        }
        else {
            ShowEmote(args);
        }
    }
    return 1;
}

string GetHelp(){
    return ("语法: <addemote>\n"
            "        <addemote 表情>\n"
            "        <addemote -edit>\n"
            "        <addemote -add>\n\n"
            "你必须是管理员或 EMOTES 组成员才能使用此命令。\n\n"
            "用于在 soul daemon 中添加和编辑表情，使用复杂的规则\n"
            "和 Dead Souls 消息系统。要使用此命令添加新表情，\n"
            "你需要了解以下信息:\n"
            "\t* 动词解析规则\n"
            "\t* 消息中需要变位的动词\n"
            "\t* 消息系统的通用消息格式\n"
            "\t* 消息支持的特殊副词\n\n"
            "动词解析规则是一组控制命令输入方式的标记。\n"
            "soul 支持的标记有: LIV（单个生物）、LVS（多个生物）\n"
            "和 STR（任意字符串）。此外，规则可以包含介词，\n"
            "如 to、at、on、about 等。\n"
            "例如，允许玩家执行 <smile at descartes>，\n"
            "需要解析规则 <at LIV> 或 <at LVS>。\n"
            "<smile oddly at descartes> 则是 <STR at LIV> 或 <STR at LVS>。\n\n"
            "下一步是定义消息中需要变位的动词。\n"
            "以 smile 表情为例，唯一的动词是 \"smile\"。\n"
            "但更复杂的表情可能有多个需要变位的动词。\n"
            "以逗号分隔列表输入即可。\n"
            "例如，如果表情消息是 \"Descartes rants and raves.\"，\n"
            "需要输入动词 rant 和 rave:\n"
            "输入动词: rant,rave\n\n"
            "下一步是指定要显示的消息。消息使用占位符（标记）\n"
            "来代表根据视角变化的部分。\n"
            "完整的标记列表见 <help messaging>，都以 $ 开头。\n"
            "重要的是，消息中 $agent_verb 或 $target_verb 标记的数量\n"
            "必须与你指定的变位动词数量完全相同。\n"
            "输入消息: $agent_name $agent_verb and $agent_verb.\n\n"
            "最后需要输入副词列表。与其他列表一样，用逗号分隔。\n"
            "如果不输入任何内容，则该规则不使用副词。\n"
            "你必须在规则中指定 STR 标记副词才有效。\n"
            "输入的副词被视为此规则的特殊副词。\n"
            "如果希望通用副词列表也可用，输入 - 作为副词之一。\n"
            "如果希望玩家能输入任何想到的副词，输入 *:\n"
            "输入副词: -");
}
