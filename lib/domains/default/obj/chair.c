#include <lib.h>

inherit LIB_CHAIR;

protected void create() {
    chair::create();
    SetKeyName("chair");
    SetId("chair");
    SetAdjectives( ({ "swivel", "small", "black" }) );
    SetShort("一个转椅");
    SetLong("这是一个小型转椅， with tasteful and understated black covers。");
    SetMass(1500);
    SetDollarCost(15);
    SetMaxSitters(1);
}
void init(){
    add_action("swivel","swivel");
}

int swivel(string str){
    int hit,i;
    object *dupes;
    dupes = get_dupes(this_object(),environment(this_object()) );
    if(!str || str =="" || str == "in chair" || str == "in the chair"){
        hit = 42;
        for(i=0;i<sizeof(dupes);i++){
            if( member_array(this_player(),dupes[i]->GetSitters()) != -1) hit = 7;
            if( member_array(this_player(),this_object()->GetSitters()) != -1) hit = 7;
        }
        if( hit == 7) {
            write("你在转椅上转来转去！ Whee！");
            say(this_player()->GetName()+"在"+possessive(this_player())+"转椅上转来转去，大喊 \"WHEEEE！！！\"");
            return 1;
        }
        else { write("你没有坐在转椅上。"); }
    }
    if(hit == 42) return 1;
    else return 0;
}

mixed CanGet(object ob) { return "这个椅子纹丝不动。";}
