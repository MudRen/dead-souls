#include <lib.h>
inherit LIB_NPC;

protected void create(){
    npc::create();
    SetKeyName("money tree");
    SetId(({"tree","money tree","arborus argentum"}));
    SetShort("一棵摇钱树");
    SetLong("这棵健壮的、4英尺高的树就是传说中的摇钱树。它的叶子是崭新的钞票，它的种荚里装满了各种各样的硬币，几乎要爆开了。从树上获取<数量><货币>一点都不麻烦...看来你中大奖了！");
    SetPacifist(1);
    SetCanBite(0);
    SetLevel(99);
    SetRace("tree");
    SetHealthPoints(99999);
    SetMaxHealthPoints(99999);
    SetPreventGet(1);
}

void init(){
    ::init();
    add_action("make_money","get");
}

int make_money(string str){
    int d1;
    string s1,s2;
    if(!creatorp(this_player()) && !member_group(this_player(),"TEST")) {
        write("你的手似乎从树上滑了下来...好像它 somehow 知道这些钱不应该落入你贪婪的手中。");
        return 1;
    }
    if(!str){ write("获取什么？\n"); return 1; }
    if(sscanf(str,"%d %s from %s",d1,s1,s2) > 0){
        if(s1 !="electrum" && s1 != "platinum" &&
                s1 !="gold" && s1 !="cents" &&
                s1 !="dollars" && s1 !="copper" &&
                s1 !="silver"){
            write("那种钱可不是从树上长出来的！\n");
            return 1;
        }
        if(s2=="tree" || s2=="the tree" ||
                s2=="the money tree" || s2=="arborus argentum"){
            if(d1 > 1000000){
                write("一次从树上获取那么多钱太多了。\n");
                return 1;
            }
            this_player()->AddCurrency(s1, d1);
            write("你从摇钱树上获得了"+d1+" "+s1+"。");
            say(this_player()->GetCapName()+"从摇钱树上获取了钱。");
            return 1;
        }
        return 0;
    }
}
