#include <lib.h>
#include <talk_type.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    mapping FluencyMap = ([]);
    string *langs = this_player()->GetLanguages();

    if(str){
        mixed ret = this_player()->CanSpeak(0, TALK_LOCAL, "foo", str);
        if(intp(ret)) {
            this_player()->SetDefaultLanguage(str);
            write("你现在使用 "+capitalize(lower_case(str))+" 交流。");
            return 1;
        }
        else return ret;
    }

    foreach(string lang in langs){
        FluencyMap[lang] = this_player()->GetLanguageLevel(lang);
    }

    if(this_player()->GetPolyglot()){
        write("你以100%的熟练度理解所有语言。");
    }

    write("你会说: ");
    foreach(string key, int val in FluencyMap){
        write(capitalize(key)+" 熟练度 "+val+"%。");
    }
    write("你当前的默认语言是: "+
            this_player()->GetDefaultLanguage()+"。");

    return 1;
}

string GetHelp() {
    return ("用法: language [语言]\n\n"
            "此命令报告你会说和理解哪些语言。\n"
            "如果指定了语言且你了解该语言，它将被设置为你的默认交流语言。\n"
            "参考: languages, speak");
}

