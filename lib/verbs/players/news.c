/*  Lets you replay the login news.
 *  created by Rush@Dead Souls & Kalinash@Dead Souls
 */

#include <lib.h>
#include "include/news.h"

inherit LIB_VERB;

protected void create() {
    ::create();
    SetVerb("news");
    SetRules("", "STR");
    SetErrorMessage("请参阅\"help news\"获取此命令的更多信息。");
    SetHelp("Syntax: news [<classname>|general]\n\n"    
            "This command allows you to replay the login news.");
}

mixed can_news() { return can_news_str("general"); }

mixed can_news_str(string str) {
    if(!str) return 0;
    if(!file_exists(DIR_NEWS + "/" + str)) return "没有" + str + "新闻。";
    if(str == "general" || this_player()->ClassMember(str)) return 1;
    if(str == "welcome") return 1;
    if(str == "creator" && creatorp(this_player())) return 1;
    if(archp(this_player())) return 1;
    return str + "新闻不对你开放。";
}

mixed do_news() { return do_news_str("general"); }

mixed do_news_str(string str) {
    this_player()->eventPage(DIR_NEWS + "/" + str);
    return 1;
}
