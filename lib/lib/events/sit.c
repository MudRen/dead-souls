/*    /lib/sit.c
 *    From the Dead Souls Mud Library
 *    Handles people sitting down in it
 *    Created by Descartes of Borg 961221
 *    Version: @(#) sit.c 1.1@(#)
 *    Last modified: 96/12/21
 */

#include <position.h>

private int          MaxSitters = 1;
private object* Sitters    = ({});

int GetMaxSitters(){
    return MaxSitters;
}

protected int SetMaxSitters(int x){
    return (MaxSitters = x);
}

object* GetSitters(){
    return copy(Sitters);
}

mixed eventReceiveSit(object who){
    mixed furn = who->GetProperty("furniture");
    if(furn && objectp(furn)){
        write("你已经在使用一件家具了。");
        return 1;
    }
    Sitters = ({ Sitters..., who });
    who->SetProperty("furniture", " on "+this_object()->GetShort());
    who->SetProperty("furniture_object", this_object());
    return 1;
}

mixed eventReleaseStand(object who){
    Sitters -= ({ who });
    Sitters = filter(Sitters, (: objectp($1) :) );
    if(who) who->RemoveProperty("furniture");
    if(who) who->RemoveProperty("furniture_object");
    return 1;
}

mixed direct_sit_word_obj(){
    Sitters = filter(Sitters, (: $1 && $1->GetPosition()==POSITION_SITTING :));
    if( sizeof(Sitters) >= MaxSitters ){
        return "那里没有坐下的空间。";
    }
    if(environment() != environment(this_player())){
        return "那个现在不能用来坐下。";
    }
    return 1;
}

mixed direct_sit_down_word_obj(){
    return direct_sit_word_obj();
}

int CanGet(object who){
    object *sitters = this_object()->GetSitters();
    if(sizeof(sitters)){
        foreach(object wer in sitters){
            if(!wer || environment(wer) != environment()) this_object()->eventReleaseStand(wer);
        }         if(sizeof(this_object()->GetSitters())){
            write(this_object()->GetSitters()[0]->GetName()+"正在使用它。");
            return 0;
        }
        else return 1;
    }
    else return 1;
}
