#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
string patient;

void create(){
    ::create();
    SetKeyName("regeneration slip");
    SetId( ({"slip","leaf","paper","healer token"}) );
    SetAdjectives( ({"regeneration","medical","paper"}) );
    SetShort("一张再生纸条");
    SetLong("这是一张脆弱的小纸片，甚至可能是一片树叶。上面写着一些神秘的文字。");
    SetMass(1);
    SetBaseCost("silver",1200);
    SetVendorType(VT_HERB);
    SetItems( ([
                ({"script","writing","scribbling"}) : "There is writing on the slip."
                ]) );
    SetRead( ([
                ({"script","writing","scribbling"}) : "The slip reads: \"etaoin\""
                ]) );
    SetDefaultRead("default", "The slip reads: \"etaoin\"");
    SetProperty("problem","regenerate");
}

void init(){
    ::init();
    if( living(environment()) && environment()->GetKeyName() != "clepius"){
        patient = environment()->GetKeyName();
    }
}

int SetPatient(string str){
    if(str) patient = str;
    return 1;
}

string GetPatient(){
    if(patient) return patient;
    else return "none";
}

