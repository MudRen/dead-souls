/*    /domains/Praxis/etc/basement_door.c
 *    from Dead Souls LPMud
 *    created by Descartes of Borg 951027
 */

#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();
    SetId("north", "door");
    SetShort("north", "一扇精致橡木制成的门");
    SetLong("north", "这是一扇华丽的门，标志着战士职业大厅的入口。");
    SetLockable("north", 1);
    SetKeys("north", "special_key_id");
    SetId("south", "door");
    SetShort("south", "一扇精致橡木制成的门");
    SetLong("south", "这是一扇华丽的门，通往招募区。");
    SetLockable("south", 1);
    SetKeys("south", "special_key_id");
    SetClosed(1);
    SetLocked(0);
}
