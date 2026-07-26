/*    /verbs/items/put.c
 *    from the Dead Souls Mud Library
 *    put OBJ in OBJ
 *    put OBJ into OBJ
 *    created by Descartes of Borg 950114
 *    Version: @(#) put.c 1.2@(#)
 *    Last modified: 96/12/31
 */

#include <lib.h>
#include "include/put.h"

inherit LIB_VERB;
string *eligible;

protected void create() {
    verb::create();
    SetVerb("put");
    SetSynonyms("place", "stick");
    SetRules("OBS in OBJ", "OBS into OBJ", "OBS on OBJ", "OBS onto OBJ", "OBS OBJ",
            "WRD WRD in OBJ", "WRD WRD into OBJ", "WRD WRD on OBJ", "WRD WRD onto OBJ");
    SetErrorMessage("把什么放到哪里？");
    SetHelp("用法：put <物品> into <容器>\n"
            "      put <物品> onto <表面>\n\n"
            "允许你将物品放入其他物品中。\n\n"
            "同义词：place, stick\n\n"
            "另见：get, give, drop");
}


mixed can_put_obs_word_obj(object *foo1, string wrd, object foo2) {
    if(check_light()) return this_player()->CanManipulate();
    else return 0;
}

mixed can_put_obs_obj(object *foo1, string wrd, object foo2){
    return can_put_obs_word_obj(foo1, wrd, foo2);
}

mixed can_put_obj_word_obj(object target, string wrd, object storage) {
    object *target_arr;
    if(target) target_arr = ({ target });
    return can_put_obs_word_obj(target_arr, wrd, storage);
}

mixed can_put_obj_obj(object target, string wrd, object storage){
    return can_put_obj_word_obj(target, wrd, storage);
}

//mixed can_put_wrd_wrd_word_obj(string num, string curr,string wrd, mixed container) {
mixed can_put_wrd_wrd_word_obj(mixed args...) {
    int amt;
    string num, curr, wrd;
    mixed container;
    object ob1, ob2;

    num = args[0];
    curr = args[1];
    wrd = args[2];
    container = args[3];

    ob1 = get_object(num+" "+curr);
    ob2 = get_object(implode(args[6..]," "));

    if(ob1 && ob2) return can_put_obj_word_obj(ob1, wrd, ob2);

    if( !num || !curr ) return 0;
    if( (amt = to_int(num)) < 1 ) return "你不能那样做！";
    if( this_player()->GetCurrency(curr) < amt )
        return "你没有那么多" + curr + "。";
    if(newbiep(this_player())){
        return "新手不能丢弃金钱。";
    }
    if(wrd == "on" || wrd == "onto"){
        if(container && !inherits( LIB_SURFACE, container ) ) return "#那不是一个可承载的表面。";
    }
    if(container && container->GetClosed()){
        return "#那是关着的。";
    }
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed do_put_obj_word_obj(object what, string wrd, object storage) {
    if(storage && storage->GetClosed()){
        write(capitalize(storage->GetShort())+"是关着的。");
        return 1;
    }
    if(wrd == "in" || wrd == "into") return storage->eventPutInto(this_player(), what);
    if(wrd == "on" || wrd == "onto") return storage->eventPutOnto(this_player(), what);
}

mixed do_put_obj_obj(object what, object storage){
    string prepo;
    if(storage && inherits(LIB_SURFACE,storage)) prepo = "onto";
    else prepo = "into";
    return do_put_obj_word_obj(what, prepo, storage);
}

mixed do_put_obs_word_obj(mixed *res, string wrd, object storage) {
    object *obs;
    obs = filter(res, (: objectp :));

    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(res, (: $1 :));
        foreach(string *lines in ua) {
            if(storage && storage->GetClosed())
                write(capitalize(storage->GetShort())+"是关着的。");
            else write("现在似乎不可能这样做。");
            return 1;
        }
        if(storage && storage->GetClosed())
            write(capitalize(storage->GetShort())+"是关着的。");
        else write("现在似乎不可能这样做。");
        return 1;
    }
    if(!sizeof(filter(obs, (: environment($1) == this_player() :)))){
        write("你似乎没有那个东西。");
        eligible = ({});
        return 1;
    }
    eligible=filter(obs, (: (!($1->GetWorn()) && environment($1) == this_player()) :));
    if(!sizeof(eligible)){
        write("请先卸下或解除装备再尝试放置。");
        eligible = ({});
        return 1;
    }
    if(wrd == "in" || wrd == "into") {
        foreach(object ob in eligible)
            storage->eventPutInto(this_player(), ob);
    }
    if(wrd == "on" || wrd == "onto") {
        foreach(object ob in eligible)
            storage->eventPutOnto(this_player(), ob);
    }
    eligible = ({});
    return 1;
}

mixed do_put_obs_obj(mixed *res, object storage){
    string prepo;
    if(storage && inherits(LIB_SURFACE,storage)) prepo = "onto";
    else prepo = "into";
    return do_put_obs_word_obj(res, prepo, storage);
}

//mixed do_put_wrd_wrd_word_obj(string num, string curr, mixed wort, object ob) {
mixed do_put_wrd_wrd_word_obj(mixed args...) {
    object pile, env;
    int amt;
    string num, curr, wort;
    mixed container;
    object ob, ob1, ob2;

    num = args[0];
    curr = args[1];
    wort = args[2];
    ob = args[3];

    ob1 = get_object(num+" "+curr);
    ob2 = get_object(implode(args[6..]," "));

    if(ob1 && ob2) return do_put_obj_word_obj(ob1, wort, ob2);

    if(wort == "on") wort = "onto";
    if(wort == "in") wort = "into";

    if(wort == "onto" && !inherits( LIB_SURFACE, ob ) ) {
        write("那不是一个可承载的表面。");
        return 1;
    }
    if(wort == "into" && inherits( LIB_SURFACE, ob ) ) {
        write("那是一个表面。试试 \"put on\"");
        return 1;
    }

    if((inherits(LIB_SIT,ob) && sizeof(ob->GetSitters())) ||
            (inherits(LIB_LIE,ob) && sizeof(ob->GetLiers()))){
        write("似乎有人挡住了你的去路。");
        return 0;
    }


    amt = to_int(num);
    env = environment(this_player());
    pile = new(LIB_PILE);
    pile->SetPile(curr, amt);
    if( !(pile->eventMove(ob)) ||
            this_player()->AddCurrency(curr, -amt) == -1 ) {
        this_player()->eventPrint("某些事情阻碍了你的行动。");
        pile->eventDestruct();
        return 1;
    }
    this_player()->eventPrint("你把" + amt + "个" + curr +
            "放"+wort+ob->GetShort()+"里。");

    environment(this_player())->eventPrint(this_player()->GetName() +
            "把一些" + curr + "放"+wort+ob->GetShort()+"里。",
            this_player());
    return 1;
}

mixed eventCheckLight(object who) {
    return check_light(who);
}
