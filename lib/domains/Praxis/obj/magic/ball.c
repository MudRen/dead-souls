#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void init() {
    ::init();
    add_action("scry", "scry");
}

void create() {
    ::create();
    SetKeyName("ball");
    SetId( ({ "ball", "base", "crystal ball", "honor_quest_ob" }) );
    SetShort( "%^CYAN%^一个水晶球%^RESET%^");
    SetLong("底部有一些文字。");
    SetRead("来自你祖父的爱。");

    SetMass(190);
    SetValue(50);
    SetVendorType(VT_MAGIC);
    SetProperty("magic item", ({"scry"}) );
    true();
}

int scry(string str) {
    object ob, env;

    if(!str) return notify_fail("占卜什么？\n");
    write("你凝视着水晶球。");
    if(this_player()->query_mp() < 5) {
        write("你的魔法力量太弱了，无法帮助你。");
        return 1;
    }
    if(!(ob = find_living(str)) || creatorp(ob)) {
        write("我们的世界中没有这个人。");
        return 1;
    }
    if(!environment(ob)) return notify_fail("咕噜咕噜咕噜。\n");
    if(environment(ob)->GetProperty("no scry"))
    {
        write("有什么东西在干扰你的注意力。");
        return 1;
    }
    this_player()->add_mp(-5);
    if(!(env = environment(ob))) {
        write(ob->query_cap_name()+"迷路了。");
        return 1;
    }
    write("你在水晶球中找到了"+ob->query_cap_name()+"，在：\n");
    write(env->GetShort()+"\n");
    return 1;
}
