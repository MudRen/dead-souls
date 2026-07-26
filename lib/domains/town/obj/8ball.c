#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_SHAKE;
inherit LIB_CONSULT;

string answer = "";

string *answers = ({
        "Signs point to yes.",
        "Yes.",
        "Most likely.",
        "Without a doubt.",
        "Yes - definitely.",
        "As I see it, yes.",
        "You may rely on it.",
        "Outlook good.",
        "It is certain.",
        "It is decidedly so.",
        "Reply hazy, try again.",
        "Better not tell you now.",
        "Ask again later.",
        "Concentrate and ask again.",
        "Cannot predict now.",
        "My sources say no.",
        "Very doubtful.",
        "Outlook not so good.",
        "My reply is no.",
        "Don't count on it.",
});

void create(){
    ::create();
    SetKeyName("magic 8 ball");
    SetId( ({"ball","8ball","8-ball","8 ball"}) );
    SetAdjectives( ({"giant","billiard","black","magic"}) );
    SetShort("一个魔法8号球");
    SetLong("这是一个塑料球体，大约手掌大小，黑色。一侧画着一个白色圆圈，中间有数字8，就像一个巨大的台球。球体的另一侧有一个小透明窗口。看起来人们摇动这个球，然后向它咨询以获得建议。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    answer = answers[random(sizeof(answers))];
    SetRead( (: eventConsult :) );
}

void init(){
    ::init();
}

varargs mixed eventShake(object dude, string foo){
    write("You shake your magic 8 ball.");
    say(dude->GetName()+" shakes "+possessive(dude)+" magic 8 ball.");
    answer = answers[random(sizeof(answers))];
    return 1;
}

varargs mixed eventConsult(object dude, string foo){
    write("The magic 8 ball answers: \n"+answer);
    if(!dude) dude = this_player();
    say(dude->GetName()+" consults "+possessive(dude)+" magic 8 ball.");
    return 1;
}

varargs mixed CanConsult(object who, string component){
    return 1;
}

varargs mixed CanShake(object who, string component){
    return 1;
}
