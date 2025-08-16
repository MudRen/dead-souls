/*    /lib/inventory.c
 *    from the Dead Souls LPC Library
 *    gives a person information about their inventory
 *    created by Descartes of Borg 950412
 */

#include <lib.h>
#include <rounds.h>
#include <message_class.h>

inherit LIB_DAEMON;

void eventInventory();

mixed cmd(string args) {
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventInventory :), ROUND_OTHER);
    else eventInventory();
    return 1;
}

void eventInventory() {
    mapping borg;
    string *items, *wieldeds, *worns, *shorts;
    string ret;
    int i;

    items = map(filter(all_inventory(this_player()), 
                (: !($1->GetInvis(this_player())) &&
                 !($1->GetWorn()) :)),
            (: $1->GetEquippedShort() :));
    wieldeds = map(filter(all_inventory(this_player()),
                (: !($1->GetInvis(this_player())) &&
                 ($1->GetWielded()) :)),
            (: $1->GetEquippedShort() :));
    worns = map(filter(all_inventory(this_player()),
                (: !($1->GetInvis(this_player())) &&
                 !($1->GetWielded()) && $1->GetWorn() :)),
            (: $1->GetEquippedShort() :));
    shorts = items + wieldeds + worns;
    if( !(i = sizeof(shorts)) ) {
        message("system", "你没有携带任何东西。", this_player());
        return;
    }
    if( i == 1 ) ret = "你只携带了这一个物品：\n";
    else ret = "你携带了以下物品：\n";
    foreach(shorts in ({ items, wieldeds, worns })){
        i = sizeof(shorts);
        if(!i) continue;
        borg = ([]);
        while(i--) if( shorts[i] ) borg[shorts[i]]++;
        i = sizeof(shorts = keys(borg));
        while(i--) ret += capitalize(consolidate(borg[shorts[i]], 
                    shorts[i]))+"\n";
    }
    message("look", ret, this_player());
    if(!this_player()->GetInvis() && 
            !environment(this_player())->GetProperty("meeting room"))
        message(MSG_ANNOYING, this_player()->GetName() + " checks " +
                possessive(this_player()) + " possessions.", 
                environment(this_player()), ({ this_player() }));
}

string GetHelp() {
    return ("语法：inventory\n\n"
            "列出你当前携带的所有物品。如果你在战斗中，"
            "这个命令会占用一轮战斗时间。");
}
