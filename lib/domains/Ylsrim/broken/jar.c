#include <lib.h>

inherit LIB_ITEM;
inherit LIB_CLOSE;
inherit LIB_LIGHT;
inherit LIB_CAPTURE;

int BugDies = 0;

protected void create() {
    AddSave(({ "BugDies" }));
    item::create();
    close::create();
    capture::create();
    light::create();
    SetKeyName("jar");
    SetId( ({ "jar" }) );
    SetShort("一个罐子");
    SetLong("一个带盖子的罐子。盖子上戳了一些小孔。用来抓虫子再合适不过了。");
    SetDestroyOnSell(1);
    SetMass(100);
    SetValue(30);
    SetClosed(1);
    SetMaxCapture(1);
    if( BugDies > 1 ) {
        set_heart_beat(2);
    }
}

protected void heart_beat() {
    BugDies -= 2;
    if( BugDies < 1 ) {
        eventDarken();
    }
}

int direct_light_obj() { // They cannot use the light command
    return 0;
}

mixed CanCapture(object who, object target) {
    if( !target->id("lightning bug") ) {
        return "当你试图捕捉萤火虫以外的东西时，罐子发出了抗议！";
    }
    if( GetLit() ) {
        return "里面已经有一只萤火虫了！";
    }
    if( GetClosed() ) {
        return "罐子必须打开！";
    }
    return 1;
}

mixed eventCapture(object who, object target) {
    mixed tmp = capture::eventCapture(who, "lightning bug");

    if( tmp != 1 ) {
        return tmp;
    }
    target->eventDestruct();
    who->eventPrint("你在罐子里捉到了一只萤火虫！");
    environment(who)->eventPrint(who->GetName() + "用" + possessive(who) + "罐子捉到了一只萤火虫。", who);
    SetLit(1);
    BugDies = 360;
    set_heart_beat(2);
}

mixed eventDarken() {
    object env = environment();

    if( env ) {
        env->eventPrint("%^YELLOW%^萤火虫%^RESET%^死了。");
    }
    if( living(env) && (env = environment(env)) ) {
        env->eventPrint(possessive_noun(environment()->GetName()) +
                "的萤火虫死了，" + possessive(environment()) +
                "的罐子暗了下来。", environment());
    }
    capture::eventFree("lightning bug");
    SetLit(0);
    return 1;
}

mixed eventFree(object who, string target) {
    mixed tmp = capture::eventFree(target);
    object bug;

    if( tmp != 1 ) {
        return tmp;
    }
    if( GetClosed() ) {
        eventOpen(who, "jar");
    }
    SetLit(0);
    environment(who)->eventPrint("一只萤火虫从罐子里飞了出来！");
    bug = new("/realms/ariel/wonder/monsters/lbug");
    bug->eventMove(environment(who));
    return 1;
}

varargs mixed eventOpen(object who, string id, object tool) {
    mixed tmp = close::eventOpen(who, id, tool);

    if( tmp != 1 ) {
        return tmp;
    }
    if( sizeof(GetCaptured()) ) {
        eventFree(who, "lightning bug");
    }
    return 1;
}

string GetShort() {
    string tmp = item::GetShort();

    if( GetLit() ) {
        tmp += "\n里面有一只萤火虫。";
    }
    if( GetClosed() ) {
        tmp += "\n它是关着的。";
    }
    else {
        tmp += "\n它是开着的。";
    }
    return tmp;
}

string GetLong(string str) {
    string tmp = item::GetLong();

    if( GetLit() ) {
        tmp += "\n它在发光。";
    }
    if( GetClosed() ) {
        tmp += "\n它是关着的。";
    }
    else {
        tmp += "\n它是开着的。";
    }
    return tmp;

}
