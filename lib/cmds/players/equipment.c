#include <lib.h>
#include <rounds.h>

inherit LIB_DAEMON;

void eventInventory();

mixed cmd(string args) {
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventInventory :), ROUND_OTHER);
    else eventInventory();
    return 1;
}

void eventInventory() {
    object *weapons = filter(all_inventory(this_player()), (: $1->GetWielded() :) );
    string *bare_limbs = filter(this_player()->GetLimbs(), (: !sizeof(this_player()->GetWorn($1)) :) );
    object *armors = filter(all_inventory(this_player()), 
            (: $1->GetWorn() && !($1->GetWielded()) :) );
    string ret = "你正在使用: \n";

    foreach(object weapon in weapons){
        string tmp = capitalize(weapon->GetShort());
        string *limbs = ({});
        foreach(string limb in weapon->GetWorn()){
            limbs += ({ "你的"+limb });
        }
        tmp += " 握在 "+item_list(limbs)+" 中。\n";
        ret += tmp+"\n";
    }

    foreach(object armor in armors){
        string tmp = capitalize(armor->GetShort());
        string *limbs = ({});
        foreach(string limb in armor->GetWorn()){
            limbs += ({ "你的"+limb });
        }
        tmp += " 穿在 "+item_list(limbs)+" 上。\n";
        ret += tmp;
    }

    if(sizeof(bare_limbs)){
        ret +="\n你的以下身体部位未装备: \n";
        ret += capitalize(item_list(bare_limbs)+"。");
    }

    write(ret);
}

string GetHelp(){
    return ("用法: equipment\n\n"
            "列出你当前穿戴或使用的所有物品。"
            "如果你正在战斗中，此命令会占用一个战斗回合。");
}
