/*    /cmds/player/body.c
 *    from the Dead Souls LPC Library
 *    gives player a report based on limb damage
 *    created by Blitz@Dead Souls
 */



#include <lib.h>
#include <rounds.h>

inherit LIB_VERB;

varargs void eventCheckBody(object ob, object receiver);

protected void create() {
    verb::create();
    SetVerb("body");
    SetRules("", "LIV");
}

nosave string *DamageDegree = ({
        "处于濒危状态！",
        "伤痕累累，面目全非。",
        "伤势严重",
        "受到严重损伤。",
        "状态很差。",
        "正在疼痛。",
        "有几处淤伤。",
        "状态尚可。",
        "状态良好。",
        "状态极佳。",
        });

int livings_are_remote() { return 1; }

mixed can_body() {
    return 1;
}

mixed can_body_liv() {
    if( !creatorp(this_player()) )
        return "试试：help body";
    return 1;
}

mixed do_body() {
    message("other_action", this_player()->GetName()+"检查"+
            reflexive(this_player())+"的伤势。",
            environment(this_player()), this_player() );
    eventCheckBody(this_player());
    return 1;
}

mixed do_body_liv(object ob) {
    eventCheckBody(ob, this_player());
    return 1;
}

varargs void eventCheckBody(object ob, object receiver) {
    string ret, name;
    string *limbs;
    mapping mp;
    int i, damage;
    int *key;

    mp = ([ ]);
    if( !ob ) return;
    if( !receiver ) receiver = ob;
    i = sizeof(limbs = ob->GetLimbs());
    while(i--) {
        damage = to_int( percent( ob->GetHealthPoints(limbs[i]),
                    ob->GetMaxHealthPoints(limbs[i]) ));
        if( !mp[damage] ) mp[damage] = ({ limbs[i] });
        else mp[damage] += ({ limbs[i] });
    }
    i = sizeof(key = sort_array(keys(mp), 1));
    name = (ob == receiver ? "你的" : capitalize(possessive(ob)));
    ret = possessive_noun(ob->GetCapName()) + "身体伤害"
        "报告：\n\n";
    foreach(damage in key) {
        string str;
        string color;
        int x;
        i = sizeof(limbs = mp[damage]);
        while(i--) {
            switch(damage) {
                case 0..3: color = "%^BOLD%^%^RED%^"; break;
                case 4..10: color = "%^RED%^";        break;
                case 11..20: color = "%^YELLOW%^";    break;
                default: color = "";
            }
            if( damage > 97 )
                str = name +" "+ limbs[i] + "状态完好。";
            else if( damage < 4 )
                str = name+" "+ limbs[i] +"快要掉了！";
            else {
                x = damage / 10;
                if(x>9) x = 9;
                str = name +" "+ limbs[i] +" "+ DamageDegree[x];
            }
            if( creatorp(receiver) )
                ret += sprintf("%s%-45s %s(%d / 100%%)%s\n", color, str, 
                        "", damage,"%^RESET%^");
            else ret += (color + str + "%^RESET%^\n");
        }
    }
    if( i = sizeof(limbs = ob->GetMissingLimbs()) ) {
        ret += "\n"+(ob == receiver ?
                "你失去了" : ob->GetName()+"失去了");
        switch(i) {
            case 0: break;
            case 1: ret += limbs[0]+"。"; break;
            case 2: ret += limbs[0]+"和"+limbs[1]+"。"; break;
            default:  ret += implode(limbs[0..(i-2)], "、")+"和"
                      +limbs[i-1]+"。";
        }
    }
    receiver->eventPage(explode(ret, "\n"), "info");
    return;
}

string GetHelp(string str) {
    if( creatorp(this_player()) )
        return "用法：body [生物]\n\n"
            "此命令将显示指定生物的当前肢体伤害统计数据。";
    else
        return "用法：body\n\n"
            "此命令将显示你当前的肢体伤害统计数据。"
            "肢体将按伤害程度从高到低显示。";
}
