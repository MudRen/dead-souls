#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

int count = 0;
int interval = 0;
string keepalive = "";

void create(){
    ::create();

    SetKeyName("pinger");
    SetId( ({"pinger"}) );
    SetShort("一个保活器");
    SetLong("这个东西可以设置为定期输出一个字符串，目的是保持不稳定的 telnet 连接。"
            "\n设置间隔：interval <心跳数> \n"
            "设置字符串：vassily <字符串>"
            "\n\n注意：此对象已弃用。请改用 'keepalive' 命令。");
    SetNoCondition(1);
    SetMass(20);
    AddSave( ({ "count", "interval", "keepalive" }) );
    set_heart_beat(1);
}

int SetInterval(string str){
    interval = atoi(str);
    if(!intp(interval)){
        write("那不是一个有效的整数。");
        return 1;
    }

    write("间隔设置为"+interval+"心跳。");
    return 1;
}

int SetKeepalive(string str){
    if(!str || str == "") keepalive = "\n";
    else keepalive = str;
    write("保活设置完成。");
    return 1;
}

void init(){
    ::init();
    add_action("SetInterval","interval");
    add_action("SetKeepalive","vassily");
}

void heart_beat(){
    count++;
    if(interval > 0 && count > interval){
        count = 0;
        if(living(environment(this_object())) &&
                true()){
#ifndef __DSLIB__
            tell_object(environment(this_object()),keepalive);
#else
            send_nullbyte(environment(this_object()));
#endif
        }
    }
}
