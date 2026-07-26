/*    /verbs/items/buy.c
 *    From the Dead Souls Mud Library
 *    Allows players to buy things from living vendors
 *    Created by Descartes of Borg sometime in 1996
 *    Version: @(#) buy.c 1.2@(#)
 *    Last modified: 97/01/03
 */

#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("buy");
    SetSynonyms("purchase");
    SetRules("STR from LIV");
    SetErrorMessage("向谁买什么？");
    SetHelp("用法：buy <物品> from <商人>\n\n"
            "在商人面前，你可以买卖与该商人经营类型匹配的商品。"
            "\"buy\" 命令允许你购买商人出售的物品。\n\n"
            "同义词：purchase\n\n"
            "另见：ask, sell, vendors");
}

mixed can_buy_str_from_liv(string str) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

mixed do_buy_str_from_liv(string str, object vendor) {
    return vendor->eventSell(this_player(), remove_article(lower_case(str)));
}
