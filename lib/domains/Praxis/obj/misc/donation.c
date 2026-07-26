inherit "/lib/std/item";
//#include <security.h>
#include <council.h>
#define LOG "/realms/nialson/data/mage_coffer_log"

int loaded, stored_amount;

void init() {
    ::init();
    add_action("donate", "donate");
    add_action("withdraw", "withdraw");
}

void create() {
    ::create();
    loaded=stored_amount=0;
    SetKeyName("donation box");
    SetId( ({ "donation box", "box" }) );
    SetShort("一个捐款箱");
    SetRead("弗罗比茨收藏社财产。");
    SetMass(0);
    SetValue(0);
    SetPreventGet("你不被允许拿走那个。没有人可以。");
    SetNoClean(1);
}

int restore_int(string str) {
    string tmp;
    string repl;
    int value;

    tmp=absolute_path("/realms/nialson/data", str);
    repl=read_file(tmp, 1, 1);
    sscanf(repl, "%d\n", value);
    return value;   
}

void save_int(string str, int value) {
    string tmp;

    tmp=absolute_path("/realms/nialson/data", str);
    rm(tmp);
    write_file(tmp, ""+value+"\n");
}

int donate(string str) {
    int amount;

    if(!str) {
        notify_fail("捐献什么？\n");
        return 0;
    }
    if(sscanf(str, "%d gold", amount) !=1) {
        notify_fail("正确语法：<donate [#] gold>\n");
        return 0;
    }
    if(amount < 1) {
        notify_fail("那确实是个巧妙的把戏！\n");
        return 0;
    }
    if(this_player()->query_money("gold") < amount) {
        notify_fail("你没有那么多金币！\n");
        return 0;
    }
    if (!loaded) {
        stored_amount = restore_int("mage_coffers");
        loaded=1;}
    this_player()->add_money("gold", -1*amount);
    write("你向法师们捐献了"+amount+"枚金币。");
    say(this_player()->query_cap_name()+"捐献了一些金币。", this_player());
    stored_amount += amount;
    write_file(LOG,""+stored_amount+"\t"+
            this_player()->query_name()+" donates ."+amount+"\n");
    save_int("mage_coffers", stored_amount);
    return 1;
}

string GetLong(string junk) {
    if (!loaded) {
        stored_amount = restore_int("mage_coffers");
        loaded=1;}
    return
        "一个中等大小、非常重的箱子，里面装着法师职业的资金。\n"+
        "如果你愿意，你可以 <donate # gold> 来增加这些资金。\n"+
        "金库目前有"+stored_amount+"金币。\n";
}

int withdraw(string str) {
    int amount;
#define TESTERS ({"nialson", "lassondra", "zaknaifen"})
    if((-1==member_array(this_player()->query_name(), TESTERS))&&
            (-1==member_array(this_player()->query_name(), MAGE_COUNCIL))) {
        notify_fail("只有议会成员才能取款。\n");
        return 0; }
    if(!str) {
        notify_fail("取出什么？\n");
        return 0; }
    if(sscanf(str, "%d gold", amount) !=1) {
        notify_fail("正确语法：<withdraw [#] gold>\n");
        return 0; }
    if (!amount) {
        notify_fail("别浪费我和你的时间了。\n");
        return 0; }
    if (amount < 0) {
        notify_fail("不允许负数！\n");
        return 0; }
    if (!loaded) {
        stored_amount = restore_int("mage_coffers");
        loaded=1;}

    write("你从法师金库中取出了"+amount+"枚金币。");
    say(this_player()->query_cap_name()+"取出了一些金币。", this_player());
    stored_amount -= amount;
    this_player()->add_money("gold", amount);
    write_file(LOG,""+stored_amount+"\t"+
            this_player()->query_name()+" withdrew ."+amount+"\n");
    save_int("mage_coffers", stored_amount);
    return 1;
}

