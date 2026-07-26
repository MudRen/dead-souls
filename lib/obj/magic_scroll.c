// magic_scroll.c
// This scroll contains a spell, which a player can learn by casting
// the read spell on the scroll.
// Mobydick@TMI-2, 3-24-93.

#include <mudlib.h> 

inherit OBJECT ;

void create() {
    ::create();
    set ("id", ({ "scroll" }) ) ;
    set ("short", "魔法卷轴") ;
    set ("long",
            "这是一张可以在上面书写法术的魔法卷轴。目前它是空白的。\n") ;
    set ("mass", 10) ;
    set ("bulk", 4) ;
}

void init() {
    add_action ("write_scroll", "write") ;
    add_action ("read_scroll", "read") ;
    add_action ("help", "help") ;
}

void set_spell (string str) {
    //if (member_array(str,SPELLS)==-1) {
    //		write ("Error: tried to set an unknown spell.\n") ;
    //		return ;
    //	}
    //	set ("spell", str) ;
    //	set ("short", "A scroll of "+str) ;
    set ("long",
            "这是一张写有"+str+"法术的魔法卷轴。\n") ;
}

int write_scroll (string str) {

    string *known ;

    //	known = this_player()->query("spells") ;
    //	if (member_array(str,known)==-1) {
    //		notify_fail ("You don't know any "+str+" spell to write.\n") ;
    //		return 0 ;
    //	}
    write ("你将"+str+"法术写在了卷轴上。\n") ;
    //	set_spell(str) ;
    return 1 ;
}

int read_scroll (string str) {
    if (!query("spell")) {
        write("你还没有在卷轴上写任何法术。\n");
        return 1;
    }
    //	if (str!="scroll" && str!="scroll of "+query("spell")) return 0 ;
    //	write ("You begin reading the scroll....\n") ;
    //	write ("You begin casting the "+query("spell")+" spell!\n") ;
    //	write ("On whom do you wish to cast it? (CR for yourself or current attacker) : ") ;
    //	input_to ("cast_args") ;
    return 1 ;
}

int cast_args (string str) {

    string name ;

    //	if (!str || str == "") str="NONE" ;
    //	name = PATH+query("spell")+EXTENSION ;
    //	name->cast(str, 1) ;
    //	remove() ;
    return 1 ;
}

int help (string str) {
    if (str!="scroll") return 0 ;
    write ("如果你会阅读法术，你可以对卷轴施放它，\n"+
            "你将学会卷轴上写的法术（如果有的话）。\n"+
            "如果你不会阅读法术，你应该找一个能教你的人。\n"+
            "你也可以直接\"阅读\"卷轴并施放上面写的法术，\n"+
            "但这样做你不会学会该法术。\n") ;
    return 1 ;
}
