#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_READ;

string ReadFun(){
    string ret = "Kuroganetko,\n";
    ret += "Find it in your heart to forgive the hard tone of "+
        "my orders. It grieves me to deny you, old friend, and I feel "+
        "bound by my love for you to explain them in proper terms here. "+
        "We are in disarray and rout. Your outpost may be the last "+
        "one with able soldiers along the eastern coast. Our foe here "+
        "is savage and possessed of magic weaponry we cannot match. You "+
        "and I and the outposts that have already fallen are serving our "+
        "people by buying them time. The settlements to our west are "+
        "being evacuated, and they may yet live thanks to our sacrifice.\n\n"+
        "May we die well, beloved friend. And may we meet again in the "+
        "halls of honour.\n\n"+
        "-Ikomotko"; 
    return ret;
}

void create(){
    ::create();
    SetKeyName("letter");
    SetId(({"letter","sheet","paper","sheet of paper"}));
    SetAdjectives(({"small"}));
    SetShort("一封信");
    SetLong("这是一张上面写着消息的纸。");
    SetMass(1);
    AddItem("message","写在纸上的一条消息。");
    SetRead("default", (: ReadFun :) );
    SetRead(({"message"}), (: ReadFun :) );
    SetLanguage("Tangetto");
}

void init(){
    ::init();
}
