mixed hobbled(object ob){
    string *missings;
    string *total;
    int foot,leg;
    mapping ret;

    missings = ob->GetMissingLimbs();
    if(!sizeof(missings)) return "没有缺失的肢体。";

    foot = 0;
    leg = 0;
    total = ({});
    foreach(string limb in missings) {
        string s1;
        if(sscanf(limb,"%s foot",s1) > 0 || sscanf(limb,"%spaw",s1) > 0) {
            foot += 1;
            total += ({ limb });
        }
        if(sscanf(limb,"%sleg",s1)  > 0){
            leg += 1;
            total += ({ limb });
        }
    }

    if( foot == 0 && leg == 0 ) return "没有缺失的腿或脚。";

    ret = ([ "feet" : foot, "legs" : leg , "list" : total ]);
    return ret;
}
