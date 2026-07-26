#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_READ;

int TestFunc(object ob,string str){
    if(ob) ob->eventPrint("如果你看到这条消息，你可能是ob。");
    this_player()->eventPrint("什么情况");
    if(str && str !="") write(str);
    if(!str) write("空值字符串。");
    if(str =="") write("空字符串。");
    write("什么情况");
    return 1;
}

void create(){
    ::create();
    SetKeyName("leaflet");
    SetId(({"leaflet","paper","slip"}));
    SetAdjectives(({"small"}));
    SetShort("一张小传单");
    SetLong("这是一张印有消息的纸。");
    SetMass(1);
    SetDollarCost(1);
    SetVendorType(VT_TREASURE);
    SetRead((: TestFunc :));
}

