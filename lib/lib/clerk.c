#include <lib.h>
#include <objects.h>

mixed performMarriage(object spouse1, object spouse2) ;
int performDivorce(object ob1);
int MarriageRequest(mixed arg1, mixed arg2, mixed arg3);
int eventRequestDivorce(mixed arg1, mixed arg2, mixed arg3);

inherit  LIB_MAYOR;
void create(){
    ::create();
    SetKeyName("clerk");
    SetId("clerk");
    SetAdjectives("town");
    SetGender("male");
    SetRace("human");
    SetShort("镇上的文书");
    SetLong("一位看起来很官僚的文书。");
    SetLocalCurrency("silver");
    SetClass("priest");
    AddCommandResponse("marry", (: MarriageRequest :));
    AddCommandResponse("wed", (: MarriageRequest :));
    AddCommandResponse("join", (: MarriageRequest :));
    AddCommandResponse("divorce", (: eventRequestDivorce :));
    SetLevel(4);
    SetTax(5);
}

int eventRequestDivorce(mixed arg1, mixed arg2, mixed arg3){
    this_object()->performDivorce(arg1);
    return 1;
}

int MarriageRequest(mixed arg1, mixed arg2, mixed arg3){
    string s1, s2, dudename;
    object ob1, ob2;
    if(strsrch(arg2,"divorce") != -1){
        this_object()->performDivorce(arg1);
        return 1;
    }

    if(sscanf(arg3,"%s and %s", s1, s2) !=2 &&
            sscanf(arg3,"%s to %s", s1, s2) !=2){
        eventForce("say "+arg1->GetName()+", 你把我搞糊涂了。");
        return 1;
    }

    dudename = arg1->GetKeyName();
    if(s1 == "me" || s1 == "i") s1 = dudename;
    if(s2 == "me" || s2 == "i") s2 = dudename;

    if(s1 != dudename && s2 != dudename ){
        eventForce("say 那些人得自己决定 "+
                "是否结婚。这不关 "+
                "你的事。");
        return 1;
    }

    if( s1 == s2){
        eventForce("say 我们这里不办理单人婚姻。");
        return 1;
    }
    if(! ob1 = present(s1, environment(this_object()))){
        eventForce("say "+capitalize(s1)+" 不在这里。");
        return 1;
    }
    if(! ob2 = present(s2, environment(this_object()))){
        eventForce("say "+capitalize(s2)+" 不在这里。");
        return 1;
    }

    if(!living(ob1) || !living(ob2)){
        eventForce("say 我不会为无生命的物体主持婚礼。");
        return 1;
    }
    this_object()->performMarriage(ob1, ob2);
    return 1;
}

mixed performMarriage(object spouse1, object spouse2){
    mixed tmp;
    eventForce("say hmmm...");
    tmp = environment(this_player())->CanMarry(this_player(),
            spouse1, spouse2);
    if( !tmp ){
        this_player()->eventPrint("这个地方对你来说并不神圣。");
        return 1;
    }
    else if( stringp(tmp) ){
        this_player()->eventPrint(tmp);
        return 1;
    }
    tmp = environment(this_player())->eventMarry(this_player(),
            spouse1, spouse2);
    if( tmp == 1 ){
        object ring;

        ring = new(OBJ_WED_RING);
        ring->SetSpouse(spouse2->GetCapName());
        ring->eventMove(spouse1);
        ring = new(OBJ_WED_RING);
        ring->SetSpouse(spouse1->GetCapName());
        ring->eventMove(spouse2);
    }
}

int performDivorce(object ob1){
    string spouse1, spouse2;
    object ring1, ring2, ob2;

    spouse1 = ob1->GetKeyName();
    if(!ob1->GetSpouse()){
        eventForce("say 你好像没有结婚。");
        return 1;
    }
    spouse2 = lower_case(ob1->GetSpouse());
    ob2 = find_player(spouse2);

    if(!ob1->CanDivorce(ob1)){
        eventForce("say 我无法办理这次离婚。你确定 "+
                "你们还是已婚状态吗？");
        return 1;
    }

    if(!find_player(spouse1) || !ob1 ){
        eventForce("say 很抱歉。离婚需要 "+
                "双方都在线才能办理。");
        return 1;
    }

    ob1->eventDivorce(ob1);
    ob2->eventDivorce(ob2);

    ring1 = present("official wedding ring",ob1);
    ring2 = present("official wedding ring",ob2);

    if(ring1) ring1->eventDestruct();
    if(ring2) ring2->eventDestruct();

    eventForce("say 离婚手续已完成。");
    tell_player(spouse1,"%^RED%^你已经与 "+capitalize(spouse2)+" 离婚了%^RESET%^！");
    tell_player(spouse2,"%^RED%^你已经与 "+capitalize(spouse1)+" 离婚了%^RESET%^！");
    eventForce("shout 本办事处正式记录并公告 "+capitalize(spouse1) +" 已与 "+capitalize(spouse2)+" 离婚！");
    return 1;
}


