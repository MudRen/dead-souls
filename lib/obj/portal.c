/*  /verbs/spells/obj/portal.c
 *  created by Blitz@Dead Souls 960417
 *  used with the portal spell
 */

#include <lib.h>
#include "include/portal.h"

inherit LIB_ITEM;

nosave int LifeSpan = 0;
nosave string Caster = "Blitz",
              LinkRoom;

protected void create() {
    item::create();
    SetKeyName("portal");
    SetId("portal");
    SetAdjectives("pulsating", "shimmering");
    SetShort("%^YELLOW%^闪烁的传送门%^RESET%^");
    SetLong((: eventShowPortal :));
    SetPreventGet("传送门是纯粹的魔法，没有实体。");
    SetPreventPut("传送门是纯粹的魔法，没有实体。");
    SetMass(0);
    SetValue(0);
}

string eventShowPortal() {
    string str;
    str = "一个闪烁的魔法传送门，散发着不同深浅的白色和蓝色光芒。"
        "它是由塔利玛为她忠实的仆人" + Caster + "所创造的。";
    if( sizeof(LinkRoom) ) {
        object ob = load_object(LinkRoom);
        if( !ob ) return "这个传送门出了问题。";
        str += "凝视着它深邃的内部，你偶尔能隐约看到" + ob->GetShort() + "的景象。";
    }
    else str += "你在它的深处什么也看不到。";
    return str;
}

int SetLink(mixed dest) {
    if( stringp(dest) ) {
        dest = load_object(dest);
        if( !dest ) return 0;
    }
    else if( !objectp(dest) ) error("Invalid argument 1 to SetLink!");
    LinkRoom = base_name(dest);
    return 1;
}

string GetLink() { return LinkRoom; }

int SetLifeSpan(int x) {
    if( LifeSpan ) return 0;
    call_out((: eventDestruct :), x);
    return (LifeSpan = x);
}

int GetLifeSpan() { return LifeSpan; }

string SetCaster(string str) { return (Caster = str); }

string GetCaster() { return Caster; }

mixed CanEnter(object who, string what) {
    if( !sizeof(LinkRoom) ) return "传送门无法使用。";
    else return 1;
}

int eventEnter(object who) {
    if( !who ) return 0;
    who->eventPrint("%^RED%^%^BOLD%^你踏入传送门，感觉周围的现实在扭曲。");
    who->eventMoveLiving(LinkRoom,
            "%^GREEN%^$N踏入传送门，消失了。",
            "%^GREEN%^$N从闪烁的传送门中走了出来。");
    return 1;
}

int eventDestruct() {
    object env = environment();
    if( env ) {
        env->eventPrint("一个闪烁的传送门消失了。");
    }
    ::eventDestruct();
}
