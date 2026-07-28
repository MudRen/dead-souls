#include <lib.h>
#include "include/clan.h"

private class ClanClass Clan;

private int isWelcomed;

protected void create(){
    Clan = new(class ClanClass);
    Clan->leader = 0;
    Clan->name = 0;
    Clan->objectName = 0;
    Clan->skill = 0;
    isWelcomed = 0;
}

protected void init(){
    if(!present(this_object(), this_player())) return;
    if(this_player()->GetClan() != GetClanName()) return;
    if(this_player()->GetKeyName() == GetLeader()){
        add_action("eventBring", "bring");
        add_action("eventInitiate", "initiate");
        add_action("eventRetire", "retire");
    }
    this_player()->eventPrint("\n");
    if(!isWelcomed){
        this_player()->AddChannel(GetClanName());
        eventWelcome(this_player());
        isWelcomed = 1;
    }
}

mixed CanJoin(object ob){ return 1; }

string GetAffectLong(object ob){
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " is a member of the "
        + pluralize(GetClanName()) + ".";
}

string SetLeader(string str){
    if(!user_exists(str)) error("No such user: " + str
            + ". You must have a real leader.");
    if(!stringp(Clan->leader)) 
        Clan->leader = str;
    return Clan->leader;
}

string GetLeader(){ return Clan->leader; }

string SetClanName(string str){
    if(!stringp(Clan->name)) Clan->name = str;
    return Clan->name;
}

string GetClanName(){ return Clan->name; }

string SetClanObject(string str){
    if(!stringp(Clan->objectName)) Clan->objectName = str;
    return Clan->objectName;
}

string GetClanObject(){ return Clan->objectName; }

string SetClanSkill(string str){
    if(!stringp(Clan->skill)) Clan->skill = str;
    return Clan->skill;
}

string GetClanSkill(){ return Clan->skill; }

int eventBring(string str){
    object who;

    if(!str) return notify_fail("带来谁？\n");
    who = find_player(lower_case(str));
    if(!who)
        return notify_fail(who->GetName() + " 无处可寻。\n");
    if(who->GetClan() != GetClanName())
        return notify_fail(who->GetName() + " 不是我们的人！\n");
    if(   environment(who)->GetProperty("no teleport")
            || environment(this_player())->GetProperty("no teleport")
            || environment(this_player())->GetProperty("no magic"))
        return notify_fail("一股魔力阻止了你的法术。\n");
    if(present(who, environment(this_player())))
        return notify_fail(capitalize(str) + " 就在这里。\n");
    if(this_player()->GetMagicPoints() < 70)
        return notify_fail("魔力不足。\n");
    this_player()->AddMagicPoints(-70);
    who->eventPrint("%^CYAN%^你的门派领袖召唤了你。%^RESET%^");
    who->eventMoveLiving(environment(this_player()));
    if(!present(who, environment(this_player())))
        this_player()->eventPrint("%^CYAN%^" + capitalize(str)
                + " 超出了你的能力范围。%^RESET%^");
    return 1;
}

int eventInitiate(string str){
    object initiate;
    object clanObject;
    mixed ret;

    if(!str) return notify_fail("接纳谁？\n");
    initiate = present(lower_case(str), environment(this_player()));
    if(!initiate || !living(initiate))
        return notify_fail("这里没有这样的人。\n");
    if(stringp(ret = CanJoin(initiate))) return notify_fail(ret);
    else if(!ret) return ret;
    if(this_player()->GetMagicPoints() < 300)
        return notify_fail("魔力不足。\n");
    if(initiate->GetClan())
        return notify_fail("你只能接纳没有门派归属的人。\n");
    initiate->SetClan(GetClanName());
    initiate->SetSkill(GetClanSkill(), 1, 1);
    if(clanObject = new(GetClanObject()))
        clanObject->eventMove(initiate);
    this_player()->AddMagicPoints(-300);
    eventJoin(initiate);
    return 1;
}

void eventJoin(object ob){
    ob->eventPrint("%^YELLOW%^你现在是" + pluralize(GetClanName()) + "的一员了。%^RESET%^");
    environment(ob)->eventPrint("%^YELLOW%^" +ob->GetName()
            + " 现在是" + pluralize(GetClanName()) + "的一员了。%^RESET%^", ob);
}

int eventRetire(string str){
    object retiree;
    object clanObject;

    if(!str) return notify_fail("驱逐谁？\n");
    retiree = present(lower_case(str), environment(this_player()));
    if(!retiree || !living(retiree))
        return notify_fail("这里没有这样的人。\n");
    if(retiree->GetClan() != GetClanName())
        return notify_fail(retiree->GetName() + " 不是我们的人！\n");
    clanObject = present(GetClanName() + "_clan_object", retiree);
    if(!clanObject) error("Problem with clan object.");
    clanObject->eventDestruct();
    retiree->SetClan(0);
    //  retiree->SetSkill(GetClanSkill(), 1, 1); We need to remove skill here.
    eventUnjoin(retiree);
    return 1;
}

void eventUnjoin(object ob){
    ob->eventPrint("%^RED%^你不再是" + pluralize(GetClanName()) + "的一员了。%^RESET%^");
    environment(ob)->eventPrint("%^RED%^" + ob->GetName()
            + " 不再是" + pluralize(GetClanName()) + "的一员了。%^RESET%^", ob);
}

void eventWelcome(object ob){
    ob->eventPrint("%^YELLOW%^欢迎，同为" + GetClanName() + "的伙伴。%^RESET%^");
}

