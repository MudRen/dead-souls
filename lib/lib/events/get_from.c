/*    /lib/events/get_from.c
 *    From the Dead Souls Mud Library
 *    Handles get from/put in
 *    Created by Descartes of Borg 961221
 *    Version: @(#) get_from.c 1.1@(#)
 *    Last modified: 96/12/22
 */

#include <lib.h>
#include <message_class.h>
#include <daemons.h>

// abstract methods
int AddCarriedMass(int amount);
string GetShort();
// end abstract methods

mixed CanGetFrom(object who, object item){
    int check = GUARD_D->CheckGet(who, this_object());
    if(!check){
        who->eventPrint("你无法拾取它。", MSG_SYSTEM);
        return 0;
    }

    if( !item ){
        return "#你好像有点困惑。";
    }
    if( this_object()->GetClosed() ){
        return "#它是关着的！";
    }
    if( !sizeof(all_inventory(this_object())) ){
        return "#它是空的。";
    }
    //if( environment(item) != this_object() ){
    //    item = present(item->GetKeyName(),this_object());
    //    if(!item) return "#That's not available from there.";
    //}

    if( (environment() != environment(this_player())) &&
            (environment() != this_player()) ){
        return "#" + capitalize(GetShort()) + " 不在你的触及范围内。";
    }
    return 1;
}

mixed CanPutInto(object who, object item){
    object env;

    if((inherits(LIB_SIT,item) && sizeof(item->GetSitters())) ||
            (inherits(LIB_LIE,item) && sizeof(item->GetLiers()))){
        write("好像有人挡着你。");
        return 0;
    }

    if( item == this_object() ){
        return "#你不能改变物理定律。";
    }
    env = environment();
    if( env != this_player() && env != environment(this_player()) ){
        return "#它不在你的触及范围内。";
    }

    if( this_object()->GetClosed() ){
        return "#它是关着的！";
    }
    return 1;
}

mixed CanPutOnto(object who, object item){
    object env;

    if((inherits(LIB_SIT,item) && sizeof(item->GetSitters())) ||
            (inherits(LIB_LIE,item) && sizeof(item->GetLiers()))){
        write("好像有人在阻碍你。");
        return 0;
    }

    if(!inherits( LIB_SURFACE, item ) ){
        return "#那不是一个可承载的表面。";
    }
    if( item == this_object() ){
        return "#你不能改变物理定律。";
    }
    env = environment();
    if( env != this_player() && env != environment(this_player()) ){
        return "#它不在你的触及范围内。";
    }
    return 1;
}


mixed eventGetFrom(object who, object* what){
    object* fin = ({});
    string* shorts;
    mapping mp = ([]);
    string msg;
    int i, maxi;
    mixed tmp;

    if((inherits(LIB_SIT,this_object()) && sizeof(this_object()->GetSitters())) ||
            (inherits(LIB_LIE,this_object()) && sizeof(this_object()->GetLiers()))){
        write("那上面好像有人。");
        return 0;
    }

    foreach(object ob in what ){
        if( environment(ob) != this_object() ){
            continue;
        }
        if( (tmp = ob->CanGet(who)) != 1 ){
            if(stringp(tmp)) write(tmp);
            else write("看起来你现在无法拿起 "+
                    (ob->GetShort() || "那个东西") +"。");
            continue;
        }
        if( !who->CanCarry(ob->GetMass()) ){
            write("看来你拿不动它。");
            continue;
        }
        if( !ob->eventMove(who) ){
            who->eventPrint("你拿起 " +
                    ob->GetShort() + " 时遇到了问题。");
            continue;
        }
        AddCarriedMass( -(ob->GetMass()) );
        fin += ({ ob });
    }
    what = fin;
    if( !(maxi = sizeof(what)) ){
        return 0;
    }
    shorts = map(what, (: $1->GetShort() :));
    for(i=0; i<maxi; i++){
        mp[shorts[i]]++;
    }
    maxi = sizeof(shorts = keys(mp));
    for(i=0, msg = ""; i<maxi; i++){
        if( mp[shorts[i]] < 2 ){
            msg += shorts[i] + "%^RESET%^";
        }
        else {
            msg += consolidate(mp[shorts[i]], shorts[i]) +  "%^RESET%^";
        }
        if( i == maxi-2 ){
            msg += " 和 ";
        }
        else if( i != maxi-1 ){
            msg += ", ";
        }
    }
    send_messages("get", "$agent_name 从 $target_name 中拿出了 " + msg + "。",
            who, this_object(), environment(who));
    return 1;
}

mixed eventPutInto(object who, object what){
    return what->eventPut(who, this_object());
}

mixed eventPutOnto(object who, object what){
    if((inherits(LIB_SIT,this_object()) && sizeof(this_object()->GetSitters())) ||
            (inherits(LIB_LIE,this_object()) && sizeof(this_object()->GetLiers()))){
        write("好像有人挡在那里。");
        return 0;
    }
    return what->eventPut(who, this_object()," onto ");
}


int inventory_accessible(){
    return 1;
}

int inventory_visible(){
    return 1;
}

mixed indirect_get_obj_from_obj(object item, object container){
    if(!item){
        return "#那不在那里。";
    }

    if(!clonep(container)) return "#什么";

    //if(environment(item) != this_object()) return "#That's not in there.";

    return CanGetFrom(this_player(), item);
}

mixed indirect_get_obj_out_of_obj(object item, object container){
    return indirect_get_obj_from_obj(item, container);
}

mixed indirect_get_obj_obj(object item, object container){
    return indirect_get_obj_from_obj(item, container);
}

mixed indirect_get_obs_from_obj(object* items, object storage){
    if( !items ){
        return (storage == this_object() || "#那不在那里。");
    }
    return 1;
}

mixed indirect_get_obs_out_of_obj(object* items, object storage){
    return indirect_get_obs_from_obj(items, storage);
}

mixed indirect_get_obs_obj(object* items, object storage){
    return indirect_get_obs_from_obj(items, storage);
}

mixed indirect_put_obj_word_obj(object what, string word, object storage){
    if( !what ){
        return (storage == this_object());
    }
    return CanPutInto(this_player(), what);
}

mixed indirect_put_obj_obj(object what, string word, object storage){
    return indirect_put_obj_word_obj(what, word, storage);
}

mixed indirect_put_obs_word_obj(object *items, string wrd, object storage){
    if( !items ){
        return (storage == this_object());
    }
    return 1;
}

mixed indirect_put_obs_obj(object *items, string wrd, object storage){
    return indirect_put_obs_word_obj(items, wrd, storage);
}
