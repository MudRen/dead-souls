#include <lib.h>
#include <vendor_types.h>
#include <vision.h>
inherit LIB_ITEM;

varargs string translate_vision(object ob){
    int vision;
    string ret = " ";
    if(!ob) vision = this_player()->GetEffectiveVision();
    else vision = ob->GetEffectiveVision();
    switch(vision){
        case 0 : ret = "等级0：失明。";break;
        case 1 : ret = "等级1：太暗了。";break;
        case 2 : ret = "等级2：黑暗。";break;
        case 3 : ret = "等级3：昏暗。";break;
        case 4 : ret = "等级4：清晰。";break;
        case 5 : ret = "等级5：明亮。";break;
        case 6 : ret = "等级6：耀眼。";break;
        case 7 : ret = "等级7：太亮了。";break;
        default : ret = "未知。";
    }
    return ret;
}

varargs mixed EvaluateRadiantLight(object ob, int report){
    int x = 0;
    string rep = "";
    string subrep = "";
    if(!ob) ob = this_player();
    foreach(object guy in get_livings(environment(ob))){
        if(guy->GetRadiantLight())
            rep += guy->GetName()+"'s radiant light is: "+guy->GetRadiantLight()+".\n";
        foreach(object item in all_inventory(guy)){
            x += item->GetRadiantLight();
            if(item->GetRadiantLight()){
                subrep += guy->GetName()+"'s "+item->GetName()+"'s radiant light is: "+
                    item->GetRadiantLight()+".\n";
            }
        }
    }
    if(!report) return x;
    else return "生物：\n"+rep+"\n物品：\n"+subrep;
}

string DefaultReading(){
    write("这个小设备是一个便携式光线计。它告诉你可用的光线情况。");
    write("这里的环境光线是："+environment(this_player())->GetAmbientLight());
    write("这里的总辐射光线是："+EvaluateRadiantLight());
    write("你的视觉范围是："+this_player()->GetEffectiveVision(environment(this_player()),1));
    write("\n你的有效视觉是"+translate_vision());
    write("\n完整辐射细节：\n"+EvaluateRadiantLight(this_player(),1));
    return "";
}

varargs mixed eventUse(mixed arg){
    return DefaultReading();
}

void create(){
    ::create();
    SetKeyName("light meter");
    SetAdjectives( ({"light"}) );
    SetId( ({"meter", "lightmeter"}) );
    SetShort("一个光线计");
    SetLong( (: DefaultReading :) );
    SetProperties(([
                "no steal" : 1,
                ]));
    SetNoCondition(1);
    SetMass(20);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
