/*    /lib/climb.c
 *    from the Dead Souls Mud Library
 *    handles different methods of climbing
 *    created by Descartes of Borg 960120
 *    Version: @(#) climb.c 1.7@(#)
 *    Last modified: 96/12/22
 */

#include <climb.h>
#include <function.h>

nosave private mapping Climb = 0;
int ccc = 0;

// abstract methods
string GetDefiniteShort();
// end abstract methods

mapping GetClimbs(){
    return Climb;
}

int SetCanClimbCarried(int i){
    ccc = i;
    return 1;
}

int GetCanClimbCarried(){
    return ccc;
}

varargs nosave mapping SetClimb(mixed val, int type){
    if( !type ){
        type = CLIMB_UP;
    }
    if( !Climb ){
        Climb = ([ type : val ]);
    }
    else {
        Climb[type] = val;
    }
    return Climb;
}

mixed CanClimb(object who, int type){
    int* tmp;
    object dude;
    string thingname;

    dude=this_player();
    thingname=this_object()->GetKeyName();

    if(present(thingname,dude) && ccc == 0){
        return "你不能在携带它的时候攀爬。";
    }

    if( Climb[type] ){
        return 1;
    }
    tmp = keys(Climb);
    if( !sizeof(tmp) ){
        return 0;
    }
    else {
        type = tmp[0];
    }
    switch(type){
        case CLIMB_UP:
            return "你是不是想爬上去？";

        case CLIMB_DOWN:
            return "你是不是想爬下去？";

        case CLIMB_OUT:
            return "你是不是想爬出来？";

        case CLIMB_INTO:
            return "你是不是想爬进去？";

        case CLIMB_THROUGH:
            return "你是不是想爬过去？";
    }
    return 0;
}

varargs mixed eventClimb(object who, int type, string where){
    mixed dest = Climb[type];
    if(where && where !="") dest = where;

    if( functionp(dest) ){
        if( functionp(dest) & FP_OWNER_DESTED ){
            who->eventPrint("今天没法爬那个了！");
            return 1;
        }
        return evaluate(dest, who, type);
    }
    else {
        string omsg, imsg;

        switch(type){
            case CLIMB_UP:
                omsg = "$N 爬上了 " + GetDefiniteShort() + "。";
                imsg = "$N 爬了进来。";
                break;

            case CLIMB_DOWN:
                omsg = "$N 爬下了 " + GetDefiniteShort() + "。";
                imsg = "$N 爬了进来。";
                break;

            case CLIMB_OUT:
                omsg = "$N 从 " + GetDefiniteShort() + " 爬了出来。";
                imsg = "$N 爬了进来。";
                break;

            case CLIMB_INTO:
                omsg = "$N 爬进了 " + GetDefiniteShort() + "。";
                imsg = "$N 爬了进来。";
                break;

            case CLIMB_THROUGH:
                omsg = "$N 爬过了 " + GetDefiniteShort() + "。";
                imsg = "$N 爬了进来。";
                break;
        }
        who->eventMoveLiving(dest, omsg, imsg);
        return 1;
    }
}

mixed direct_climb_obj(object ob){
    return CanClimb(this_player(), CLIMB_UP);
}

mixed direct_climb_out_of_obj(object ob){
    return CanClimb(this_player(), CLIMB_OUT);
}

mixed direct_climb_out(object ob){
    return CanClimb(this_player(), CLIMB_OUT);
}

mixed direct_climb_word_obj(string word, object ob){
    if( !Climb ){
        return 0;
    }
    switch(word){
        case "up":
            return CanClimb(this_player(), CLIMB_UP);

        case "down":
            return CanClimb(this_player(), CLIMB_DOWN);

        case "out":
            return CanClimb(this_player(), CLIMB_OUT);

        case "in": case "into":
            return CanClimb(this_player(), CLIMB_INTO);

        case "through":
            return CanClimb(this_player(), CLIMB_THROUGH);

        default:
            return 0;
    }
}

mixed direct_climb_word(string word){
    return direct_climb_word_obj(word, this_object());
}
