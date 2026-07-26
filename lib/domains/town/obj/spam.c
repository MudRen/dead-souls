#include <lib.h>
#include <vendor_types.h>
#define DIR_TXT "/domains/town/txt"
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
    SetShort("一罐午餐肉");
    SetLong( (: SpamSpam :) );
    SetNoCondition(1);
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetRetain(1);
}

void init(){
    ::init();
    add_action("SpamSpamSpamSpam","spam");
}

string SpamSpam(string spamspam){
    string spamspamspam;
    spamspamspam=read_file("/domains/town/txt/spam.txt");
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
        write("你想用什么来砸谁？");
        say(this_player()->GetName()+"笨拙地摆弄着"+possessive(this_player())+
                "一罐午餐肉。\n");
        return 1;
    }
    ob=present(spam1,environment(this_player()));
    if(!ob){
        write("这里没有这样的东西可以砸！\n");
        say(this_player()->GetName()+"四处张望想找东西来砸。\n");
        return 1;
    }
    if(!living(ob)){
        write("那个东西对午餐肉不感兴趣。\n");
        say(this_player()->GetName()+"愚蠢地乱扔午餐肉。\n");
        return 1;
    }
    if(file_size(DIR_TXT+"/"+spam2+".txt") == -1){
        write("你不能那样砸"+ob->GetName()+"。你看起来很傻。\n");
        say(this_player()->GetName()+"尝试错误地砸午餐肉，看起来很傻。\n");
        return 1;
    }
    spamspam=unguarded((: read_file(DIR_TXT+"/"+spam2+".txt") :));
    say(this_player()->GetName()+"用一个巨大的"+spam2+"砸了"+ob->GetName()+"。\n", ob);
    tell_object(ob, this_player()->GetName()+"用以下东西砸了你：\n"+spamspam+"\n");
    write("你用一个巨大的"+spam2+"砸了"+ob->GetName()+"！\n");
    return 1;
}
int Spam(string spamspamspamspam){
    string but_I_dont_like_spam;
    but_I_dont_like_spam=unguarded((:read_file("/secure/obj/txt/spam.txt") :));
    this_player()->SetLong("$N is a can of spam:\n\n"+but_I_dont_like_spam);
    this_player()->AddTitle("the can of spam (Spammy!)");
    write("你把午餐肉弄了自己一身！\n");
    say(this_player()->GetName()+"把午餐肉弄了"+objective(this_player())+"一身！\n");
    return 1;
}
