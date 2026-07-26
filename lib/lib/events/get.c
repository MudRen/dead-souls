/*    /lib/get.c
 *    from the Dead Souls Mud Library
 *    handles the picking up of objects
 *    created by Descartes of Borg 960114
 *    Version: @(#) get.c 1.3@(#)
 *    Last Modified: 96/12/21
 */

#include <message_class.h>
#include <daemons.h>

private mixed PreventGet;

// abstract methods
int GetMass();
mixed GetProperty(string key);
string GetShort();
string GetKeyName();
mixed eventMove(mixed dest);
// end abstract methods

mixed GetPreventGet(){
    return PreventGet;
}

mixed SetPreventGet(mixed val){
    return (PreventGet = val);
}

mixed CanGet(object who){
    int check = GUARD_D->CheckGet(who, this_object());
    if(!check){
        who->eventPrint("你无法拾取它。", MSG_SYSTEM);
        return 0;
    }
    if( !(who->CanCarry(GetMass())) ) return "它对你来说太重了！";
    if( !PreventGet && !GetProperty("keep") ) return 1;
    if( stringp(GetProperty("keep")) ){
        if( who->GetKeyName() == GetProperty("keep") ){
            if( !PreventGet ) return 1;
        }
        else return "神秘的力量阻止你拾取 " + this_object()->GetShort() + "。";
    }
    if( PreventGet && intp(PreventGet) ) return 0;
    if( stringp(PreventGet) ) return PreventGet;
    if( objectp(PreventGet) ){
        if( PreventGet == who )
            return capitalize(this_object()->GetShort()) + " 根本不想被拿走。";
        else return 1;
    }
    else{
        return evaluate(PreventGet, who);
    }
}

mixed eventGet(object who){
    if( !eventMove(who) ){
        who->eventPrint("你没能拾取它。");
        return 1;
    }
    if(living(this_object())){
        if(this_object()->GetProperty("mount")){
            this_object()->RemoveProperty("mount");
        }
        if(this_object()->GetProperty("furniture_object")){
            this_object()->RemoveProperty("furniture_object");
            this_object()->RemoveProperty("furniture");
        }
        who->SetMount(1);
        who->eventMount(this_object(), 1, 1);
    }
    send_messages("get", "$agent_name $agent_verb $target_name.",
            who, this_object(), environment(who));
    return 1;
}

protected void create(){
    PreventGet = 0;
}

mixed direct_get_obj(object target){
    if(environment() == this_player())
        return "#你已经拿着它了。";
    if( environment() != environment(this_player()) ){
        string str = this_object()->GetShort();

        if( !str ) str = "It";
        else str = capitalize(str);
        return "#你可能需要靠近一点。也许 "+
            "试试 \"get "+this_object()->GetKeyName()+" from\" 某个东西？";
    }
    return CanGet(this_player());
}

mixed direct_get_obj_out_of_obj(object target, object src){
    object env;
    string str;

    env = environment();
    if( !(str = this_object()->GetShort()) ) str = "It";
    else str = capitalize(str);
    if( env==this_player() || env ==environment(this_player()) || living(env) ){
        return "#你现在不能那样做。";
    }
    return CanGet(this_player());
}

mixed direct_get_obj_from_obj(object target, object src){
    return direct_get_obj_out_of_obj(target, src);
}

mixed direct_get_obj_obj(object target, object src){
    return direct_get_obj_out_of_obj(target, src);
}
