#include <lib.h>
#include "include/shell.h"
#include <vendor_types.h>
inherit LIB_ITEM;
private int caliber,millimeter;
private string firearmtype,ammotype;
void create(){
    ::create();
    if(!firearmtype) firearmtype = "firearm";
    SetKeyName("shell");
    SetId(({"shell","casing","shell casing"}));
    SetShort("一个用过的"+firearmtype+"弹壳");
    SetLong("这是一颗已发射子弹的空弹壳。");
    SetMass(1);
    SetValue(0);
    SetVendorType(VT_TREASURE);
}
int SetFirearmType(string str){firearmtype=str; return 1; }
int SetAmmoType(string str){ammotype=str; return 1; }
int SetCaliber(int x){ caliber=x; return 1; }
int SetMillimeter(int x){ millimeter=x; return 1; }
int GetMillimeter(){ return millimeter; }
int GetCaliber(){ return caliber; }
string GetFirearmType(){ return firearmtype; }
string GetAmmoType(){ return ammotype; }
