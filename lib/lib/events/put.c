/*    /lib/put.c
 *    from the Dead Souls Mud Library
 *    handles things which may be put into other objects
 *    created by Descartes of Borg 960114
 */

#include <lib.h>

private mixed PreventPut;

// abstract methods
string GetShort();
mixed CanDrop(object who);
mixed eventMove(mixed dest);
// end abstract methods

mixed SetPreventPut(mixed val){
    return (PreventPut = val);
}

mixed GetPreventPut(){
    return PreventPut;
}

varargs mixed CanPut(object who, object what){
    mixed tmp;
    object env;

    if(what) env = environment(what);
    if(!env || env != this_player()){
        return "#你没有那个东西。";
    }
    if( (tmp = CanDrop(who)) != 1 ) return tmp;
    if( !environment() ){ destruct(this_object()); return 1; }
    if( environment() != this_player() &&
            environment() != environment(this_player())) return 0;
    if( !PreventPut ) return 1;
    if( stringp(PreventPut) && PreventPut == "PERMIT" ) return 1;
    if( intp(PreventPut) ) return 0;
    if( stringp(PreventPut) ) return PreventPut;
    if( objectp(PreventPut) ){
        if( PreventPut == who )
            return "你无法把" + GetShort() + "放在任何地方。";
        else return 1;
    }
    else if(functionp(PreventPut)) return evaluate(PreventPut, who);
    else {
        return "看来你现在无法这样做。";
    }
}

varargs mixed eventPut(object who, object storage, string prep){
    int depth;
    if(!prep || prep == "") prep = " into ";
    if(prep == " onto " && !inherits( LIB_SURFACE, previous_object() ) ){
        who->eventPrint("那不是一个可以承重的平面。");
        return 0;
    }

    if(prep == " into " && inherits( LIB_SURFACE, previous_object() ) ){
        who->eventPrint("那是一个平面，请用\"put on\"指令。");
        return 0;
    }

    if((inherits(LIB_SIT,storage) && sizeof(storage->GetSitters())) ||
            (inherits(LIB_LIE,storage) && sizeof(storage->GetLiers()))){
        write("似乎有人挡住了你的路。");
        return 0;
    }


    if( !eventMove(storage) ){
        who->eventPrint(remove_article(this_object()->GetShort())+"仍然留在原处。");
        return 0;
    }
    who->eventPrint("你把" + GetShort() + "放" + prep +
            storage->GetShort() + ".");
    environment(who)->eventPrint(who->GetName() + "把" +
            GetShort() + prep +
            storage->GetShort() + "。", who);
    if(inherits(LIB_STORAGE, this_object())){
        depth = this_object()->GetRecurseDepth();
        if(depth && inherits(LIB_STORAGE, storage)) storage->AddRecurseDepth(depth); 
    }

    return 1;
}

protected void create(){
    PreventPut = 0;
}

mixed direct_put_obj_word_obj(){
    return CanPut(this_player(), this_object());
}

mixed direct_put_wrd_wrd_word_obj(){
    return CanPut(this_player(), this_object());
}

mixed direct_put_obj_obj(){
    return direct_put_obj_word_obj();
}
