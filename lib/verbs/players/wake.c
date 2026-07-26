#include <lib.h>

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("wake");
    SetRules("");
    SetErrorMessage("醒来？");
    SetSynonyms(({"wake up","awaken","unsleep"}));
    SetHelp("用法：wake\n"
            "如果睡着了，你会变得清醒一些。");
}

mixed can_wake(){
    if( this_player()->GetAlcohol() > 70 ) {
        return "你喝得太醉了，现在醒不来。";
    }
    if(this_player()->GetSleeping() < 1) {
        return "你已经醒了。";
    }
    return 1;
}

mixed do_wake(){
    if(creatorp(this_player())){
        this_player()->SetSleeping(0);
        tell_player(this_player(),"你从睡梦中醒来。");
        tell_room(environment(this_player()), this_player()->GetName()+
                "从"+possessive(this_player())+"睡梦中醒来。", ({this_player()}) );
        return 1;
    }
    if(this_player()->GetSleeping() > 1){
        tell_player(this_player(),"你变得清醒了一些。");
        tell_room(environment(this_player()), this_player()->GetName()+
                "似乎从"+possessive(this_player())+"睡梦中清醒了一些。", ({this_player()}) );
        return this_player()->SetSleeping(this_player()->GetSleeping() - 1);
    }
    else tell_player(this_player(),"你快要完全清醒了...");
    return 1;
}
