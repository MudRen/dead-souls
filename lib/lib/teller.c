/*   /lib/teller.c
 *   from the Dead Souls Object Library
 *   npc interface which handles banking transactions
 *   created by Blitz@Dead Souls 960105
 *   Version: @(#) teller.c 1.3@(#)
 *   Last Modified: 96/10/22
 */

#include <lib.h>
#include <daemons.h>
#include "include/teller.h"

inherit LIB_SENTIENT;
inherit LIB_MANYCOINS;

string BankName, LocalCurrency;
string *Currencies;
int LocalFee, NonLocalFee, OpenFee;
float ExchangeFee;

protected void create(){
    sentient::create();
    BankName = "Town Trust";
    LocalCurrency = "silver";
    LocalFee = 1;
    NonLocalFee = 5;
    OpenFee = 5;
    Currencies = ({ "copper", "silver", "electrum", "gold", "platinum" });
    SetCommandResponses( ([
                "default" : (: cmdParse :),
                ]) );
    SetRequestResponses( ([
                "default" : (: cmdParse :),
                ]) );
}

string SetBankName(string str){ return (BankName = str); }

string SetLocalCurrency(string str){ return (LocalCurrency = str); }

int SetLocalFee(int x){ return (LocalFee = x); }

int SetNonLocalFee(int x){ return (NonLocalFee = x); }

int SetOpenFee(int x){ return (OpenFee = x); }

float SetExchangeFee(float x){ return (ExchangeFee = x); }

mixed SetCurrencies(mixed var){
    if( arrayp(var) ){
        if( member_array(LocalCurrency, var) == -1 )
            var += ({ LocalCurrency });
        return (Currencies = var);
    }
    else error("Bad argument 1 to SetCurrencies()");
}

int GetLocalFee(){ return LocalFee; }

int GetNonLocalFee(){ return NonLocalFee; }

int GetExchangeFee(){ return ExchangeFee; }

int GetOpenFee(){ return OpenFee; }

mixed GetCurrencies(){ return copy(Currencies); }

string GetBankName(){ return BankName; }

string GetLocalCurrency(){ return LocalCurrency; }

mixed CanBank(object who){
    if( !who->GetAccountInfo( GetBankName() ) )
        return "你必须先在"+GetBankName()+"开设一个账户。";
    return 1;
}

int AddSurcharge(object who, string currency, int amount){
    int charge;
    string type;

    if( who->GetTown() == GetTown() ){
        type = "standard";
        charge = GetLocalFee();
    } else {
        type = "non-residential";
        charge = GetNonLocalFee();
    }
    if( !charge ) return amount;
    if( amount > charge ){
        amount -= charge;
        who->eventPrint(sprintf("银行收取了 %d %s 的%s手续费。", charge, currency, type));
        return amount;
    }
    else {
        who->eventPrint(sprintf("你付不起 %d %s 的%s手续费。", charge, currency, type));
        return 0;
    }
    return amount;
}

int eventBalance(object who){
    string str, ret, *tmp;
    mapping mp;
    float val;
    int total;

    mp = who->GetAccountInfo( GetBankName() );
    if( !mp ) return 0;
    environment()->eventPrint( who->GetName() + " 查询了当前余额。", ({ who }) );
    ret = "你在"+GetBankName()+"的账户开立于"+ctime(mp["open"])+"。\n";
    ret += "此分行的默认货币是"+GetLocalCurrency()+"。\n\n";
    tmp = filter(keys(mp), (: member_array($1, Currencies) > -1 :));
    total = 0;
    if( !sizeof(tmp) )
        ret += "你没有任何存款。\n";
    else foreach(str in tmp){
        if( mp[str] < 1 ) continue;
        ret += sprintf("%-20s : %d\n", str+"", mp[str]);
        if( str == GetLocalCurrency() ) total += mp[str];
        else if( mp[str] ){
            if( currency_rate(str) )
                val = query_value(mp[str],str,GetLocalCurrency()); 
            else val = 0;
            if(val) total += val;
        }
    }
    ret += sprintf("%-20s ----------\n%-22s %d",
            "", GetLocalCurrency()+" 总计", total);
    if( mp["last time"] )
        ret += sprintf("\n\n上次交易：%s，时间：%s。",
                mp["last trans"], ctime(mp["last time"]) );
    who->eventPage(explode(ret, "\n"), "info");
    return 1;
}

int eventDeposit(object who, string currency, int amount){
    int i;
    if( amount < 1 ){
        eventForce("speak " + who->GetName() + "，这笔交易不可接受。");
        return 1;
    }
    if( !currency ) currency = GetLocalCurrency();
    if( !(i = who->GetCurrency(currency)) ){
        eventForce("speak 你身上没有任何"+currency+"。");
        return 1;
    }
    if( amount > i ){
        eventForce("speak 你没有那么多"+currency+"。");
        return 1;
    }
    who->eventPrint(sprintf("你将 %d %s 存入了你的账户。", amount, currency));
    environment()->eventPrint(who->GetName() + " 存了一笔钱。", ({ who }) );
    who->AddCurrency(currency, -amount);
    who->AddBank(GetBankName(), currency, amount);
    return 1;
}

int eventWithdraw(object who, string currency, int amount){
    int i, x, charge;

    x = amount;
    if( amount < 1 ){
        eventForce("speak 提取负数可不是个明智的主意，"+ who->GetName() +"。");
        return 1;
    }
    if( !currency ) currency = GetLocalCurrency();
    if( !(i = who->GetBank(GetBankName(), currency)) ){
        eventForce("speak 你的账户里没有"+currency+"。");
        return 1;
    }
    if( amount > i ){
        eventForce("speak 你的账户里没有那么多"+currency+"。");
        return 1;
    }
    if( !(amount = AddSurcharge(who, currency, amount)) ) return 1;
    charge = x - amount;
    if( who->AddCurrency(currency, x) < 0 ){
        eventForce("speak 你携带不了那么多"+currency+"！");
        who->eventPrint("银行从你的账户中扣除了手续费。");
        return 1;
    }
    who->AddCurrency(currency, -charge);
    who->AddBank(GetBankName(), currency, -x);
    who->eventPrint(sprintf("你从账户中提取了 %d %s。",
                amount, currency));
    environment()->eventPrint(sprintf("%s 提取了一些%s。",
                who->GetName(), currency), ({ who }));
    return 1;
}

int eventExchange(object who, int amount, string str1, string str2){
    int i, x, charge;
    float val;

    if( amount < 0 ){
        amount = who->GetCurrency(str1);
    }
    if( amount < 1 ){
        eventForce("speak " + who->GetName() + "，该交易无法完成。");
        return 1;
    }
    if( amount > who->GetCurrency(str1) ){
        eventForce("speak 你没有那么多该种货币可以兑换。");
        return 1;
    }
    if( str1 == str2 ){
        eventForce("speak 那样做毫无意义。");
        return 1;
    }
    if( member_array(str1, GetCurrencies()) == -1 ){
        eventForce("speak 你无法兑换那种货币。");
        return 1;
    }
    if( member_array(str2, GetCurrencies()) == -1 ){
        eventForce("speak 你无法兑换那种货币。");
        return 1;
    }
    val = query_base_value(str1,amount);
    x = to_int( (amount * 0.01) + amount );
    i = val / currency_rate(str2);
    if( GetExchangeFee() )
        charge = to_int(i / (100 / GetExchangeFee()));
    else charge = 0;
    if( charge ) i -= charge;
    if( i < 1 ){
        eventForce("speak 那些东西连一" + str2 + "都不值！");
        return 1;
    }
    if( who->AddCurrency(str2, i) < 0 ){
        eventForce("speak 你携带不了那么多"+str2+"，" +
                who->GetName()+"。");
        return 1;
    }
    who->AddCurrency(str1, -amount);
    who->eventPrint(sprintf("你将 %d %s 兑换为 %d %s。",
                amount, str1, i, str2));
    if( charge )
        who->eventPrint(sprintf("你被收取了 %d %s 的手续费。",
                    charge, str2) );
    environment()->eventPrint(who->GetName()+" 将一些"+
            str1+"兑换成了"+str2+"。", who);
    return 1;
}

int eventOpenAccount(object who){
    if( who->GetAccountInfo( GetBankName() ) ){
        eventForce("speak 你已经在"+GetBankName()+"有账户了，" +
                who->GetName()+"！");
        return 1;
    }
    if( who->GetCurrency( GetLocalCurrency() ) < OpenFee ){
        eventForce(" speak "+ sprintf("你至少需要 %d %s 才能在%s开户，%s。", GetOpenFee(),
                    GetLocalCurrency(), GetBankName(), who->GetName()));
        return 1;
    }
    if( OpenFee < 1 ) return 0;
    who->AddCurrency(GetLocalCurrency(), -OpenFee);
    who->AddBank(GetBankName(), GetLocalCurrency(), OpenFee);
    who->eventPrint(sprintf("你存入了 %d %s 并在%s开设了账户。", OpenFee, GetLocalCurrency(), GetBankName()) );
    eventBalance(who);
    environment()->eventPrint(who->GetName() + " 开设了一个账户。", who);
    eventForce("smile "+who->GetKeyName());
    return 1;
}

int cmdParse(object who, string cmd, string str, mixed args...){
    int x;
    string s1, s2, honorific;
    mixed err;

    if( cmd != "account" && stringp(err = CanBank(who)) ){
        who->eventPrint(err);
        return 1;
    }
    switch(cmd){
        case "balance" :
            return eventBalance(who);
            break;
        case "deposit" :
            if( !str ){
                eventForce("speak 多少？什么货币？");
                return 1;
            }
            if(str == "all"){
                if(!sizeof(this_player()->GetCurrencies())){
                    who->eventPrint("你没有钱可以存入。");
                    return 1;
                }
                foreach(string dinero in this_player()->GetCurrencies()){
                    if(this_player()->GetCurrency(dinero) > 0)
                        eventDeposit(who, dinero, this_player()->GetCurrency(dinero));
                }
                return 1;
            }
            sscanf(str, "%d %s", x, s1);
            if( member_array(s1, Currencies) < 0 ){
                who->eventPrint("那不是有效的货币。");
                return 1;
            }
            return eventDeposit(who, s1, x);
            break;
        case "withdraw" :
            if( !str ){
                eventForce("speak 多少？什么货币？");
                return 1;
            }
            if(str == "all"){
                eventForce("speak 抱歉，取款必须明确指定货币类型和数量。");
                return 1;
            }
            sscanf(str, "%d %s", x, s1);
            if( member_array(s1, Currencies) < 0 ){
                if(!s1) who->eventPrint("请指定一种货币。");
                else who->eventPrint(s1 + " 此处不支持！");
                return 1;
            }
            return eventWithdraw(who, s1, x);
            break;
        case "exchange" :
            if( !str ){
                eventForce("speak 用什么兑换什么？");
                return 1;
            }
            if(sscanf(str, "%d %s for %s", x, s1, s2) < 3){
                x = -1;
                sscanf(str, "%s for %s", s1, s2);
            }        
            if(s1 == "all"){
                int ret = 0;
                foreach(string curr in (who->GetCurrencies() - ({ s2 }))){
                    if(who->GetCurrency(curr) < 1) continue;
                    ret += eventExchange(who, -1, curr, s2);
                }
                return ret;
            }
            else return eventExchange(who, x, s1, s2);
            break;
        case "account" :
            return eventOpenAccount(who);
            break;
        default:
            eventForce("speak " + who->GetName() + "，我不明白你想要什么。");
            eventForce("whisper to " + who->GetKeyName() + " 如果困惑，试试\"help banking\"。");

    }
    return 1;
}
