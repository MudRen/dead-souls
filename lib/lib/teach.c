#include <lib.h>

private nosave mapping Teaching = ([]);
private nosave int OfferExpires = 60;

int direct_teach_str_to_liv(){ return 1;}
int direct_teach_liv_to_str(){ return 1;}

varargs int CanTeach(object whom, string what){
    if(whom == this_object()){
        write("你不是自学公会的成员。");
        return 0;
    }
    if(member_array(what, keys(this_object()->GetSpellBook())) != -1){
        int magpoint = this_object()->GetMagicPoints();
        int maxmagpoint = this_object()->GetMaxMagicPoints();
        if(magpoint < maxmagpoint){
            write("你的法力必须全满才能教授魔法。");
            return 0;
        }
        return 1;
    }
    return 0;
}

int eventOfferTeaching(object who, string what){
    if(!CanTeach(who, what)){
        write("你无法教授那个。");
        return 0;
    }
    //if(!Teaching[who] || !Teaching[who][0] || Teaching[who][0] != what){
    tell_player(who,this_object()->GetName()+
            " 提出要教你 "+what+"。");
    tell_player(this_object(),"你提出要教 "+who->GetName()+
            " 学习 "+what+"。");
    //}
    Teaching[who] = ({ what, time() });
    return 1;
}

int eventTeach(object who, string what){
    int magpoint = this_object()->GetMagicPoints();
    if(!CanTeach(who, what)){
        write("他们无法教授那个。");
        return 0;
    }
    if(!Teaching[who]){
        write("他们没有兴趣教你任何东西。");
        return 0;
    }
    if(time() - Teaching[who][1] > OfferExpires){
        write("太迟了。他们教你的时间已经过了。");
        map_delete(Teaching,who);
        return 0;
    }
    if( !who->eventLearnSpell(what) ){
        write("你还没有准备好学习那个法术！");
        return 0;
    }

    who->eventPrint(this_object()->GetName() + "触碰了你的额头，传授给你" + what + "的知识。");
    environment()->eventPrint(this_object()->GetName() + "触碰了" +
            possessive_noun(who) +
            "额头，传授给" +
            objective(who) + what + "的知识。",
            ({ who, this_object() }));
    this_object()->eventPrint("你触碰了"+possessive_noun(who) +
            "额头，传授给" + objective(who) + what + "的知识。");
    if(!creatorp(this_object())){
        this_object()->AddMagicPoints(-magpoint);
    }
    map_delete(Teaching,who);
    return 1;
}
