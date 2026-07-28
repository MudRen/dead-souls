/*    /lib/undead.c
 *    From Dead Souls Object Library
 *    This differs from the NM LPmud version
 *    copyright (c) 1995 Dead Souls LPMud
 *    Created by Descartes of Borg 961025
 *    Version: @(#) undead.c 1.8@(#)
 *    Last modified: 96/10/27
 */

#include <daemons.h>
#include <damage_types.h>

private int           Undead      = 0;
private string        UndeadType  = 0;

// These methods are defined in other objects which inherit this
string GetName();
varargs string eventPrint(string message, mixed args...);
varargs int eventReceiveDamage(object agent, int type, int amt, int ins,
        mixed limbs);
int eventCompleteHeal(int x);
int GetHealthPoints();
int eventMoralAct(int x);
string GetRace();
void NewBody(string str);
// end virtual method section

/*****            Data manipulation              *****/
string GetUndeadType(){
    return UndeadType;
}

string SetUndeadType(string str){
    return (UndeadType = str);
}

/* int SetUndead(int x)
 * int x - 0 for living, 1 for undead
 *
 * description
 * makes the living body undead if "x" is 1 or living if "x" is 0
 *
 * returns the current status of the body
 */

int GetUndead(){
    return Undead;
}

int SetUndead(int x){
    if( GetUndead() == x ){
        return x;
    }
    if( x ){
        SetUndeadType("ghost");
    }
    else {
        SetUndeadType(0);
    }
    return (Undead = x);
}

/*****                  Events                   *****/
mixed eventBite(object target){
    return 0;
}

mixed eventTurn(object who){
    if( who ){
        environment()->eventPrint(GetName() + " 被驱逐出了生者的世界。", this_object());
        eventPrint(who->GetName() + " 将你驱逐出了生者的世界。");
        who->eventDestroyEnemy(this_object());
    }
    else {
        environment()->eventPrint(GetName() + " 被驱逐出了生者的世界。", this_object());
        eventPrint("你被驱逐出了生者的世界。");
    }
    return 1;
}

protected void heart_beat(){
    string type;

    if( !GetUndead() ){
        return;
    }
    type = GetUndeadType();
    if( random(100) + 1 > 90 ){
        if( type == "ghost" || type == "phantom" ){
            eventPrint("你悲伤地哀嚎。");
            environment()->eventPrint(GetName() + " wails mournfully.",
                    this_object());
        }
        else if( type == "zombie" || type == "ghoul" ){
            eventPrint("你痛苦地呻吟。");
            environment()->eventPrint(GetName() + " groans painfully.",
                    this_object());
        }
    }
}

int GetGhost(){
    if(GetUndeadType() == "ghost") return 1;
    else return 0;
}

