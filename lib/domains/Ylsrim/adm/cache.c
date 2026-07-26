/*    /domains/Ylsrim/adm/cache.c
 *    from the Dead Souls Mud Library
 *    room where hidden objects are stored
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetShort( "缓存室");
    SetLong( "东西藏在这里。");
    SetProperties( ([ "storage room" : 1, "logout" : ROOM_START ]) );
}
