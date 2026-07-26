#include <lib.h>
#include <dirs.h>
#include ROOMS_H
#include <virtual.h>
#include <position.h>

inherit LIB_VIRT_LAND;

varargs protected void create(int x, int y) {
    SetNoReplace(1);
    virt_land::create();
    SetClimate("temperate");
    SetAmbientLight(30);
    SetLong("一片毫无特征的虚空。");
    SetShort("一个空旷的地方");
    AddExit("down", ROOM_START);
}
