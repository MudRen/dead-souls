/*    /verbs/items/sell.c
 *    From the Dead Souls Mud Library
 *    Allows a player to sell stuff to a vendor
 *    Created by Descartes of Borg 9602??
 *    Version: @(#) sell.c 1.2@(#)
 *    Last modified: 97/01/03
 */

#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("sell");
    SetRules("OBS to LIV", "LIV OBS");
    SetErrorMessage("卖给谁什么东西？");
    SetHelp("用法：sell <物品> to <生物>\n\n"
            "在商人面前，你可以买卖与该商人经营类型匹配的商品。"
            "\"sell\" 命令允许你将物品卖给感兴趣的商人。\n\n"
            "另见：ask, sell, vendors");
}

mixed can_sell_obj_to_liv() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

mixed can_sell_liv_obs() {
    return can_sell_obj_to_liv();
}

mixed do_sell_obj_to_liv(object ob, object vendor) {
    if(ob->GetWorn()){
        write("请先卸下或解除装备再尝试出售。");
        return 1;
    }
    return vendor->eventBuy(this_player(), ({ ob }));
}

mixed do_sell_liv_obj(object vendor, object item) {
    return do_sell_obj_to_liv(item, vendor);
}

mixed do_sell_obs_to_liv(object* items, object vendor) {
    object *obs, *eligible;

    obs = filter(items, (: objectp :));
    if( !sizeof(obs) ) {
        mixed* ua;

        ua = unique_array(items, (: $1 :));
        foreach(string* list in ua) {
            this_player()->eventPrint(list[0]);
        }
        return 1;
    }
    eligible=filter(obs, (: (!($1->GetWorn()) && environment($1) == this_player()) :));
    if(!sizeof(eligible)){
        write("请先卸下或解除装备再尝试出售。");
        eligible = ({});
        return 1;
    }

    return vendor->eventBuy(this_player(), eligible);
}

mixed do_sell_liv_obs(object vendor, object* items) {
    return do_sell_obs_to_liv(items, vendor);
}
