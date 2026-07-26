/*    /lib/chapel.c
 *    from the Dead Souls  Object Library
 *    allows people to marry
 *    created by Descartes of Borg 951210
 *    Version: @(#) chapel.c 1.2@(#)
 *    Last modified: 96/10/09
 */

#include <lib.h>
#include "include/chapel.h"

inherit LIB_ROOM;

private int AllowSacrifice, SacrificeType;
private string* Classes, *Religion, *Deities, *DeityIds;

/*     **********  /lib/chapel.c apply methods  **********     */
protected void create(){
    room::create();
    Classes = ({});
    Religion = allocate(2);
    Deities = ({});
    DeityIds = ({});
    AllowSacrifice = 0;
    SacrificeType = 0;
}

/*     **********  /lib/chapel.c modal methods  **********     */
mixed CanMarry(object who, object spouse1, object spouse2){
    mixed tmp;

    if( (tmp = spouse1->CanMarry(who, spouse2)) != 1 ){
        if( tmp ) return tmp;
        else return spouse1->GetName() + " 无法结婚。";
    }
    if( (tmp = spouse2->CanMarry(who, spouse1)) != 1 ){
        if( tmp ) return tmp;
        else return spouse2->GetName() + " 无法结婚。";
    }
    if( archp(who) ){
        return 1;
    }
    return 1;
}

mixed CanSacrifice(object who, object what, string deus){
    if( who->GetReligion(1) != Religion[1] )
        return "你必须信仰 " + Religion[1] + " 才能这样做。";
    if( !(what->GetVendorType() & SacrificeType) )
        return "你不能在这里献祭那样东西。";
    if( member_array(deus, DeityIds) == -1 )
        return "你不信仰名为 \"" + deus + "\" 的神灵。";
    return AllowSacrifice;
}

mixed eventMarry(object who, object spouse1, object spouse2){
    mixed tmp;

    if( (tmp = spouse1->eventMarry(who, spouse2)) != 1 ) return tmp;
    if( (tmp = spouse2->eventMarry(who, spouse1)) != 1 ){
        spouse1->SetMarried(0);
        return tmp;
    }
    spouse1->eventPrint(who->GetName() + " 将你许配给了 " +
            spouse2->GetName() + "。");
    spouse2->eventPrint(who->GetName() + " 将你许配给了 " +
            spouse1->GetName() + "。");
    who->eventPrint("你将 " + spouse1->GetName() + " 和 " +
            spouse2->GetName() + " 结为夫妻。");
    this_object()->eventPrint(who->GetName() + " 将 " +
            spouse1->GetName() + " 和 " +
            spouse2->GetName() + " 结为夫妻。",
            ({ spouse1, spouse2, who }));
    who->AddSkillPoints("faith", random(100));
    return 1;
}

mixed eventSacrifice(object who, object what, string deus){
    who->eventPrint("你尝试进行献祭，但什么也没有发生。");
    return 1;
}

/*     **********  /lib/chapel.c event methods  **********     */
int SetAllowSacrifice(int x){ return (AllowSacrifice = x); }

int GetAllowSacrifice(){ return AllowSacrifice; }

string *SetClasses(string *rc){ return (Classes = rc); }

string *GetClasses(){ return Classes; }

string *SetDeities(string *deities){
    string *ids = ({});

    Deities = deities;
    foreach(string deus in deities)
        ids += explode(lower_case(deus), " ");
    DeityIds = ids;
    return Deities;
}

string *GetDeities(){ return Deities; }

string *SetReligion(string adj, string noun){
    Religion[0] = adj;
    Religion[1] = noun;
    return Religion;
}

varargs string GetReligion(int flag){ return Religion[flag]; }

int SetSacrificeType(int x){ return (SacrificeType = x); }

int AddSacrificeType(int x){ return (SacrificeType |= x); }

int GetSacrificeType(){ return SacrificeType; }
