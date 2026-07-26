//      /obj/monument.c
//      from the Nightmare mudlib
//      The time keeper of Krasna Square
//      created by Daroki@Nightmare

#include <lib.h>
#include <daemons.h>

#define DONATORS_LIST ({ "Kalinash", "Kazmandu", "Ariel", "Mikla", "Ninja",\
        "Shambere", "Cair", "Drittz", "Beorn", "Vilesilencer", "Elwin", "Silenus",\
        "Corvar", "Lassondra", "Bohemund", "Maria", "Arugess", "Drakken", "Dana",\
        "Soong", "Slade", "Rearden", "Stonehenge", "Shadowwolf", "Descartes",\
        })

inherit LIB_ITEM;

void GetLong_time();
string query_hour();

void create() {
    ::create();
    SetKeyName("monument");
    SetId( ({ "monument", "tower", "clock" }) );
    SetLong(
            "这座纪念碑矗立在普拉克西斯的中心，提醒每个人"
            "那些让这个世界成为可能的人们。纪念碑的一面是一个"
            "显示普拉克西斯时间的时钟。其他各面都刻着"
            "为这个世界捐款的人的名字。<read clock> 会告诉你时间。"
            "<read names> 可以查看所有捐赠者，请感谢他们。"
           );    SetMass( 0);

    SetNoClean(1);
}

void init() {
    add_action("read", "read");
}

int read(string str) {
    if(str == "clock") {
        GetLong_time();
        return 1;
    }
    else if (str == "names") {
        message("Ninfo", "这些人捐款使噩梦世界成为可能：\n"+
                format_page(sort_array(DONATORS_LIST, "alpha", this_object()), 5)
                ,this_player());
        return 1;
    }
    notify_fail("读什么？\n");
    return 0;
}

void GetLong_time() {
    write(capitalize(season(time()))+"笼罩着"+mud_name()+"，今天是"+
            month(time())+year(time())+"年NM历，第"+
            date(time())+ordinal(date(time()))+"天。\n"
         );
    write("钟面显示 "+query_hour()+"。\n");
}

string query_hour() {
    int tmp, tmp2;
    string str;

    tmp = hour(time());
    if(!tmp) tmp =10;
    else if(tmp > 10) tmp -= 10;
    tmp2 = minutes(time());
    str = (hour(time()) < 10 ? "am" : "pm");
    return tmp + ":" + (tmp2 > 9 ? tmp2 : "0"+tmp2)+" "+str;
}


int get() { return 0; }

string affect_environment() return "一座宏伟的纪念碑耸立在广场上。"; }

int alpha(string a, string b) { return strcmp(a,b); }
