/*  /daemon/notify.c
 *  created by Blitz@Dead Souls 960115
 *  notification daemon which displays notices to all cres who login
 */

#include <lib.h>
#include <save.h>
#include "include/notify.h"
#define MaxTime  (3600 * 24 * 60)

inherit LIB_DAEMON;

private mixed * Notes;
nosave string SaveFile;

protected void create() {
    int x;
    daemon::create();
    SaveFile = save_file(SAVE_NOTIFY);
    SetNoClean(1);
    Notes = ({});
    if( unguarded((: file_exists(SaveFile) :) ) ){
        RestoreObject(SaveFile);
    }
    x = sizeof(Notes);
    while( sizeof(Notes) && (time() - Notes[0][Date]) > MaxTime )
        Notes -= ({ Notes[0] });
    if( x != sizeof(Notes) ) eventSaveNotices();
    SaveObject(SaveFile);
}

protected int eventSaveNotices() {
    if( !archp(this_player()) ) return 0;
    else return SaveObject(SaveFile);
}

int eventAddNotice(object who, string msg) {
    object * obs;
    if( !who || !sizeof(msg) ) return 0;
    Notes += ({ ({ time(), who->GetName(), msg }) });
    if( sizeof(obs = filter(users() - ({ who }), (: creatorp :))) )
        obs->eventPrint("["+who->GetName()+" 添加了新通知]");
    if( eventSaveNotices() ) return (sizeof(Notes));
    else return 0;
}

int eventRemoveNotice(int x) {
    mixed var = copy(Notes);
    if( x < 0 || x > sizeof(Notes) - 1 ) return 0;
    Notes -= ({ Notes[x] });
    if( !eventSaveNotices() ) return (Notes = var), 0;
    else return 1;
}

int eventPrintNotices(object who, int start_time) {
    mixed str = ({ "[ %^YELLOW%^"+mud_name()+" 创造者通知 %^RESET%^]", "" });
    int y = sizeof(Notes);
    int x = y - 1;
    if( x < 0 || start_time > Notes[x][Date] ) return 0;
    while( x > 0 && Notes[x - 1][Date] > start_time ) x--;
    do str += ({ sprintf("%s添加于 %s 由 %s [编号 #%d]:\n\t%s%s",
                "%^RESET%^", ctime(Notes[x][Date]), Notes[x][Author], x,
                "%^CYAN%^", Notes[x][Message]), "" });
    while( ++x < y );
    who->eventPage(str);
    return 1;
}

int eventWriteNotices(string file, int start_time) {
    string str = "Dead Souls 通知文本导出。\n\n";
    mixed var;
    int x = sizeof(Notes) - 1;
    if( !archp(this_player()) ) return 0;
    if( x < 0 || start_time > Notes[x][Date] ) return 0;
    while( x > 0 && Notes[x - 1][Date] > start_time ) x--;
    foreach(var in Notes[x..])
        str += sprintf("添加于 %s 由 %s\n\t%s\n\n", ctime(var[Date]),
                var[Author], var[Message]);
    return write_file(file, str);
}
