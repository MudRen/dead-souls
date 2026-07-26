// /domains/Praxis/obj/misc/gallows.c
//  Gallows for the Nightmare Mortal Law system
//  Written by Manny@Nightmare  940823

#include <lib.h>

inherit LIB_ITEM;
object hangman;
void set_hangman(object who);


create() {
    ::create();
    SetKeyName("gallows");
    SetId( ({ "gallows", "noose", "platform" }) );
    SetShort("绞刑架");
    SetLong( (: "long_func" :) );
    SetPreventGet("你不能拿走那个！");
}

string long_func() {
    string str, name;

    str = "一个大型木制平台，有两根直立的木材和"
        "一根横梁，上面挂着绳索和绞索。";
    if(hangman) {
        if(name = capitalize(present("the corpse of "+hangman->query_name(),
                        environment(this_object()))->GetKeyName()))
            str += "\n"+name+"被吊在绞索上。";
        else str += "\n"+hangman->query_cap_name()+"站在"
            "平台上，绞索套在"+hangman->query_possessive()+"脖子上。";
    }
    return str;
}

void set_hangman(object who) { hangman = who; }
