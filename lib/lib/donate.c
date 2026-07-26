/*  /lib/donate.c
 *  a donation box inheritable
 *  created by BillGates@Dead Souls 961023
 */

#include "include/donate.h"
#include <lib.h>

private int TotalAssets;
private string LocalCurrency, Owner;

protected void create(){
    this_object()->AddSave( ({ "TotalAssets" }) );
    TotalAssets = 0;
}

protected void init(){
    if( this_player()->ClassMember(GetOwner()) ||
            this_player()->GetClan() == GetOwner() ){
        add_action( (: eventDonate :) , "donate" );
    }
}

string GetLong(string str){
    string ret = "\n目前里面有 "+TotalAssets+" " +
        "枚金币和钞票。";
    if(TotalAssets) return ret;
    else return "";
}

string SetLocalCurrency(string currency){
    return (LocalCurrency = currency);
}

string GetLocalCurrency(){return LocalCurrency;}

string SetOwner(string owner){return (Owner = owner);}

string GetOwner(){return Owner;}   

int AddAssets(int amount){
    TotalAssets += amount;
    return 1;
}

int GetAssets(){return TotalAssets;}   

int eventDonate(string amt, string type){
    int amount;
    object tp = this_player();   

    if(sscanf(amt,"%d", amount) < 1){
        write("这不是一个正确的金额。");
        return 1;
    }

    if(!valid_currency(type)){
        write("这不是一种有效的货币。");
        return 1;
    }

    if(!amount){
        tp->eventPrint("捐赠多少？\n");
        return 0;
    }   
    if(amount < 0){
        tp->eventPrint("想得美！\n");
        return 0;
    }
    if(tp->GetCurrency(type) < amount){
        tp->eventPrint("你没有那么多 " + type + "！\n");
        return 0;
    }
    tp->AddCurrency(type, -amount);
    AddAssets(amount);
    tp->eventPrint(GetOwner() + " 感谢 "
            "你的捐赠。");
    if(living(this_object())) this_object()->eventForce("say 谢谢！");
    return 1;
}
