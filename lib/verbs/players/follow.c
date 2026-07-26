/*  Allows players to possibly follow a target into another room
 *  created by Rush@Dead Souls
 */

#include <lib.h>
#include "include/follow.h"

inherit LIB_VERB;

protected void create() {
    ::create();
    SetVerb("follow");
    SetRules("", "LIV");
    SetErrorMessage("你想跟随谁？");
    SetHelp("用法：follow [生物]\n\n"
            "如果指定了生物，此命令允许你开始尾随该生物在 Dead Souls 中移动。\n"
            "否则，将报告你的跟随状态。\n"
            "如果该生物愿意让你跟随，他们可以使用 \"lead\" 命令来避免意外躲避你。\n"
            "另见：evade, lead, tracking, stealth\n");
}

mixed can_follow() { return 1; }

mixed do_follow() {
    object* followers;
    string* obs;
    object leader;
    int size;
    string tmp;

    // Format follow string.
    if(this_player()->CanLead() && leader = this_player()->GetLeader()) {
        tmp = "你正在";
        if(leader->GetFollowed(this_player())) tmp += "跟随";
        else tmp += "尾随";
        tmp += leader->GetName() + "。\n";
    }
    else tmp = "你没有尾随任何人。" + "\n";

    // Get the followers.
    followers = this_player()->GetFollowers();
    if(!followers) followers = ({});

    // Format lead string.
    tmp += "你正在带领";
    obs = map(
            filter(followers, (:this_player()->GetFollowed($1):)),
            (:$1->GetName():));
    size = sizeof(obs);
    if(size) tmp += conjunction(obs);
    else tmp += "无人";
    tmp += "。\n";

    // Format evasion string.
    tmp += "你正在躲避";
    obs = map(
            filter(followers, (:!this_player()->GetFollowed($1):)),
            (:$1->GetName():));
    size = sizeof(obs);
    if(size) tmp += conjunction(obs);
    else tmp += "无人";
    tmp += "。\n";

    this_player()->eventPrint(tmp);
    return 1;
}

mixed can_follow_liv() { return 1; }

mixed do_follow_liv(object ob) {
    object leader;

    if(leader = this_player()->GetLeader()) {
        leader->RemoveFollower(this_player());
        this_player()->eventPrint("你停止尾随" + leader->GetName() + "。");
        return 1;
    }

    if(member_array(this_player(), ob->AddFollower(this_player())) == -1)
        this_player()->eventPrint("你没有被授权跟随" + ob->GetName() + "。");
    else this_player()->eventPrint("你现在正在尾随" + ob->GetName() + "。");

    return 1;
}
