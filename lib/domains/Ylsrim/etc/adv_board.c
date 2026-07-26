/*    /domains/Ylsrim/etc/adv_board.c
 *    from the Dead Souls Mud Library
 *    created by Rush@Dead Souls
 */

#include <lib.h>

inherit "/lib/bboard";

protected void create()
{
    ::create();
    SetKeyName("bulletin board");
    SetId( ({"board", "bulletin board"}) );
    SetAdjectives("stupid");
    SetShort("一块公告板");
    SetLong("经过伊尔斯利姆的冒险者们在这里发布他们的想法。");
    set_board_id("ylsrim");
}


