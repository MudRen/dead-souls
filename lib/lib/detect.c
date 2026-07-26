/* /lib/detect.c
 * from the Dead Souls LPC Library
 * inheritable object for all tangible game objects
 * created by Descartes of Borg 950207
 */

#include <dirs.h>
#include "include/detect.h"

int direct_detect_wrd_in_obj(string word){
    if( environment() != this_player() &&
            environment() != environment(this_player()) ){
        this_player()->eventPrint("你需要更好的接触方式。");
        return 0;
    }
    else return 1;
}

mixed eventDetect(object who, string str, int ability){
    mixed magic;

    magic = GetProperty("magic item");
    if( str == "magic" ){
        if( !magic ){
            if( random(ability) > 50 ){
                who->AddSkillPoints("conjuring", random(ability * 2 + 1));
                message("my_action", "你确信 " + GetShort() + " 中没有魔法。",
                        who);
                return 1;
            }
            else {
                string *spells;
                string spell;

                if( random(ability) > 50 ){
                    who->AddSkillPoints("conjuring", random(ability));
                    message("my_action", "你没有在 " + GetShort() + " 中检测到任何魔法。",
                            who);
                    return 1;
                }
                who->AddSkillPoints("conjuring", random(5));
                spells = map(get_dir(DIR_SPELL_VERBS + "/*.c"), (: $1[0..<3] :));
                spell = spells[random(sizeof(spells))];
                message("my_action", "你隐约感觉到 \"" + spell + "\"。",
                        who);
                return 1;
            }
        }
        else {
            string *spells;
            string spell;

            if( random(ability) > 20 ){
                who->AddSkillPoints("conjuring", random(1 + 2* ability));
                if( arrayp(magic) ) magic = magic[random(sizeof(magic))];
                if( random(ability) > 50 )
                    message("my_action", "你明确感觉到 \"" +
                            magic + "\"。", who);
                else message("my_action", "你隐约感觉到 \"" + magic +
                        "\"。", who);
                return 1;
            }
            who->AddSkillPoints("conjuring", random(5) + 1);
            if( random(ability) > 50 ){
                message("my_action", "你没有在 " + GetShort() + " 中检测到任何魔法。",
                        who);
                return 1;
            }
            spells = map(get_dir(DIR_SPELL_VERBS + "/*.c"), (: $1[0..<3] :));
            spell = spells[random(sizeof(spells))];
            message("my_action", "你隐约感觉到 \"" + spell + "\"。", who);
            return 1;
        }
    }
    if( !magic ){
        if( random(ability) > 20 ){
            who->AddSkillPoints("conjuring", random(ability) + 5);
            message("my_action", "你没有感觉到 " + str + "。", who);
        }
        else {
            who->AddSkillPoints("conjuring", random(5));
            message("my_action", "你完全无法确定。", who);
        }
        return 1;
    }
    if( (arrayp(magic) && member_array(str, magic) != -1) ||
            (stringp(magic) && str == magic) ){
        if( random(ability) > 10 ){
            who->AddSkillPoints("conjuring", random(ability));
            message("my_action", "你在 " + GetShort() + " 中感觉到 " + str + "。",
                    who);
        }
        else {
            who->AddSkillPoints("conjuring", random(5));
            message("my_action", "你脑子里一片模糊。", who);
        }
        return 1;
    }
    if( random(ability) > 10 ){
        who->AddSkillPoints("conjuring", random(ability));
        message("my_action", "你在 " + GetShort() + " 中没有感觉到 " + str + "。",
                who);
        return 1;
    }
    who->AddSkillPoints("conjuring", random(5));
    message("my_action", "你脑子里一片模糊。", who);
    return 1;
}
