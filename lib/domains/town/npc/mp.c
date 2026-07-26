#include <lib.h>
#undef CANDIDATE

inherit LIB_SENTIENT;

int manchurian;

int ProcessTalk(mixed args...){
    string speech = lower_case(args[2]);
    if(sizeof(speech) > 1) speech = truncate(speech,1);
    if(manchurian){
#ifdef CANDIDATE
        call_out( (: eventForce :), 1, speech);
#endif
    }
    if(!manchurian && grepp(speech,"solitaire") && grepp(speech,"play")){
        manchurian = 1;
#ifndef CANDIDATE
        eventForce("say 不了，谢谢。我在执勤。");
#else
        eventForce("nod");
#endif
    }
    return 1;
}

protected void create(){
    sentient::create();
    SetKeyName("gate guard");
    SetId(({"human","guard","mp","soldier","policeman","military policeman"}));
    SetAdjectives(({"military"}));
    SetShort("一名军事门卫");
    SetLong("这是一名军事警察。他经历了数月的艰苦训练，从他的外表来看，他一生中见过不少战斗场面。他身材高大，看起来非常强悍，无论他守卫什么，大概都非常安全。");
    SetInventory(([
                "/domains/town/armor/bdu" : "wear bdu",
                "/domains/town/armor/helmet2" : "wear helmet",
                "/domains/town/weap/m16rifle_mp" : "wield rifle",
                ]));
    SetLevel(20);
    SetRace("human");
    SetClass("fighter");
    SetGender("male");
    SetTalkResponses( ([ "default" : (: ProcessTalk :) ]) );
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}

void init(){
    ::init();
}

