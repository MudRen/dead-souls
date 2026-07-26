#include <position.h>
#include <lib.h>
inherit LIB_SIT;

private int          MaxLiers = 1;
private object* Liers    = ({});

int GetMaxLiers(){
    return MaxLiers;
}

protected int SetMaxLiers(int x){
    return (MaxLiers = x);
}

object* GetLiers(){
    return copy(Liers);
}

mixed eventReceiveLay(object who){
    mixed furn = who->GetProperty("furniture");
    if(furn && objectp(furn)){
        write("你已经在使用一件家具了。");
        return 1;
    }
    Liers = ({ Liers..., who });
    who->SetProperty("furniture", " on "+this_object()->GetShort());
    who->SetProperty("furniture_object", this_object());
    return 1;
}

mixed eventReleaseStand(object who){
    Liers -= ({ who });
    Liers = filter(Liers, (: objectp($1) :) );
    sit::eventReleaseStand(who);
    return 1;
}

mixed direct_lie_word_obj(){
    Liers = filter(Liers, (: $1 && $1->GetPosition()==POSITION_LYING :));
    if( sizeof(Liers) >= MaxLiers ){
        return "那里没有躺下的空间。";
    }
    if(environment() != environment(this_player())){
        return "那个现在不能用来躺下。";
    }
    return 1;
}

mixed direct_lie_down_word_obj(){
    return direct_lie_word_obj();
}

int CanGet(object who){
    object *liers = this_object()->GetLiers();     if(sizeof(liers)){
        foreach(object wer in liers){             if(!wer || environment(wer) != environment()) this_object()->eventReleaseStand(wer);
        }
        if(sizeof(this_object()->GetLiers())){
            write(this_object()->GetLiers()[0]->GetName()+"正在使用它。");
            return 0;
        }
        else return sit::CanGet(who);
    }
    else return sit::CanGet(who);
}
