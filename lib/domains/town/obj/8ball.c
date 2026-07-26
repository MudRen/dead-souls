#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_SHAKE;
inherit LIB_CONSULT;

string answer = "";

string *answers = ({
        "迹象指向是的。",
        "是的。",
        "很有可能。",
        "毫无疑问。",
        "是的——绝对是。",
        "据我看来，是的。",
        "你可以信赖它。",
        "前景看好。",
        "这是确定的。",
        "确实是这样。",
        "回答模糊，请再试一次。",
        "现在最好不要告诉你。",
        "稍后再问。",
        "集中精神再问一次。",
        "现在无法预测。",
        "我的消息来源说不。",
        "非常可疑。",
        "前景不太好。",
        "我的回答是不。",
        "别指望它。",
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
    write("你摇了摇你的魔法8号球。");
    say(dude->GetName()+"摇了摇"+possessive(dude)+"魔法8号球。");
    answer = answers[random(sizeof(answers))];
    return 1;
}

varargs mixed eventConsult(object dude, string foo){
    write("魔法8号球回答：\n"+answer);
    if(!dude) dude = this_player();
    say(dude->GetName()+"查看了"+possessive(dude)+"魔法8号球。");
    return 1;
}

varargs mixed CanConsult(object who, string component){
    return 1;
}

varargs mixed CanShake(object who, string component){
    return 1;
}
