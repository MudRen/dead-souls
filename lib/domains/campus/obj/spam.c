#include <lib.h>
#include <vendor_types.h>
#define DIR_TXT "/domains/campus/txt"
inherit LIB_ITEM;
int Spam(string spam);
string SpamSpam(string spamspam);
int SpamSpamSpam(string spamspamspam);
string spam1, spam2;
void create(){
    ::create();
    SetKeyName("spam can");
    SetId(({"spam","can"}));
    SetAdjectives(({"can of","can","spam"}));
    SetShort("午餐肉罐头");
    SetLong( (: SpamSpam :) );
    SetMass(20);
    SetDollarCost(10);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
    add_action("SpamSpamSpamSpam","spam");
}

string SpamSpam(string spamspam){
    string spamspamspam;
    spamspamspam=read_file("/domains/campus/txt/spam.txt");
    return spamspamspam;
}
int SpamSpamSpamSpam(string spam){
    string spamspam;
    object ob;
    if(!spam || spam == ""){
        this_object()->Spam();
        return 1;
    }
    if(!sscanf(spam,"%s with %s",spam1,spam2)){
        write("你想用什么东西向谁扔午餐肉？");
        say(this_player()->GetName()+"笨拙地摆弄着"+possessive(this_player())+
                "午餐肉罐头。\n");
        return 1;
    }
    ob=present(spam1,environment(this_player()));
    if(!ob){
        write("这里没有那样的东西可以扔午餐肉！\n");
        say(this_player()->GetName()+"四处张望想找点什么东西来扔午餐肉。\n");
        return 1;
    }
    if(!living(ob)){
        write(ob->GetShort()+"对午餐肉不为所动。\n");
        say(this_player()->GetName()+"傻乎乎地到处扔午餐肉。\n");
        return 1;
    }
    if(file_size(DIR_TXT+"/"+spam2+".txt") == -1){
        write("你不能那样向"+ob->GetName()+"扔午餐肉。你看起来很傻。\n");
        say(this_player()->GetName()+"试图用错误的方式扔午餐肉，看起来很傻。\n");
        return 1;
    }
    spamspam=unguarded((: read_file(DIR_TXT+"/"+spam2+".txt") :));
    say(this_player()->GetName()+"用一块巨大的"+spam2+"向"+ob->GetName()+"扔了过去。\n");
    tell_object(ob, this_player()->GetName()+"向你扔了午餐肉：\n"+spamspam+"\n");
    write("你用一块巨大的"+spam2+"向"+ob->GetName()+"扔了过去！\n");
    return 1;
}
int Spam(string spamspamspamspam){
    string but_I_dont_like_spam;
    but_I_dont_like_spam=unguarded((:read_file("/secure/obj/txt/spam.txt") :));
    this_player()->SetLong("$N is a can of spam:\n\n"+but_I_dont_like_spam);
    this_player()->AddTitle("the can of spam (Spammy!)");
    write("你把午餐肉弄了自己一身！\n");
    say(this_player()->GetName()+"把午餐肉弄了"+objective(this_player())+"自己一身！\n");
    return 1;
}
