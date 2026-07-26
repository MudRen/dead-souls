inherit "/lib/std/item";

int has_ball;

void init() {
    ::init();
    add_action("place", "place");
}

void clean_up() { return; }

void create() {
    ::create();
    has_ball=0;
    SetKeyName("pedestal");
    SetId( ({ "pedestal" }) );
    SetShort("一个基座");
    SetLong(
            "这个小（侏儒高度）基座由一种黑暗、神秘的石头制成。"+
            "平坦的顶部有一个小凹痕，好像有一个圆形物体"+
            "应该放在那里。");
    SetRead("由威尔逊郡和子公司的科林斯柱专家制造。");
    SetMass(10000);
    SetValue(0);
}

int place(string str)
{
    string this;
    object ths;

    if (!stringp(str) || sscanf(str,"%s on pedestal", this) != 1) return 0;
    if (has_ball) {
        if (!(ths=present(this,this_player()))) return 0;
        if (!ths->id("crystal ball")) return 0;
        write("基座上已经有一个水晶球了。");
        return 1;}
    if (!(ths=present(this,this_player()))) {
        notify_fail("你没有携带"+this+"。");
        return 0;}
    if (!ths->id("crystal ball")) {
        notify_fail("那没有意义。");
        return 0;}
    ths->remove();
    write("你把水晶球放在基座上，看着它融合到位。");
    say("把水晶球放在基座上。球与基座融合了。");
    SetShort("一个带水晶球的基座。");
    SetLong(
            "这个小（侏儒高度）基座由一种黑暗、神秘的石头制成。"
            "一个水晶球紧紧地嵌入顶部的凹痕中。"
            "当你注视它时，你注意到从石头到水晶球有几乎难以察觉的力量线条。"
            "看来你辨别魔法力量的课程已经见效了。");
    add_action("view", "view");
    has_ball=1;
    return 1;
}

int view(string str)
{
    int i;
    string desc;
    object ob, env, *inv;

    write("你凝视着水晶球。");
    if(this_player()->query_mp() < 5) {
        write("你的魔法力量太弱了，无法帮助你。");
        return 1;
    }
    if(!(ob = find_living(str))
#if 0
            || creatorp(ob)
#endif
      ) {
        write("我们的世界中没有这个人。");
        return 1;
    }
    this_player()->add_mp(-5);
    if(!(env = environment(ob))) {
        write(ob->query_cap_name()+"迷路了。");
        return 1;
    }
    write("你在水晶球中找到了"+ob->query_cap_name()+"："); 
    ob=environment(ob);
    desc = ob->GetLong()+"\n";
    inv = all_inventory(ob);
    for(i=0; i<sizeof(inv); i++) {
        if(inv[i]->query_invis()) continue;
        desc += "\n"+inv[i]->GetShort()+" "; }
    write(desc);
    return 1;
}
