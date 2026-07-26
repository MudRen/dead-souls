#include <lib.h>
#include <dirs.h>
#include <rooms.h>
#include <virtual.h>
#include <position.h>
#define __DIR__ "/domains/learning/virtual/"

inherit LIB_VIRT_LAND;

varargs protected void create(int x, int y) {
    SetNoReplace(1);
    virt_land::create();
    SetClimate("temperate");
    SetAmbientLight(30);
    SetLong("一片毫无特色的虚空。");
    SetShort("空旷之地");
    AddExit("down", ROOM_START);
}
