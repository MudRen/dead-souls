#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void analyze(string butt);
object scanner,tricorder,person;
object *gstuff,*ngstuff;
mixed *statlist,*skilllist;
mapping this_stat,this_skill;
int allowed,statpoints,statlevel,statclass,tempint,i;
int skilllevel,skillclass,skillpoints;
string name;
string *stumps;
string warning = "我们提醒你，三录仪不会说话。如果它真的说话了，"+
"请忽略它的建议。";

void create(){
    item::create();
    SetKeyName("creator tricorder");
    SetId(({"tricorder","scanner","device","tool","medtric","tric"}));
    SetAdjectives(({"electronic","admin","diagnostic"}));
    SetShort("医疗三录仪");
    SetLong("这是一款掌上电子设备，设计用于进行各种医疗测试并提供疾病和伤害的治疗。"+
            "其表面用粗体红字写着：\"%^BOLD%^RED%^仅供授权测试角色使用%^RESET%^\"。\n%^YELLOW%^注意：某些功能对无人机无效。"+
            "这是由于主对象安全模型中的保护措施，不会被\"修复\"。%^RESET%^\n"+
            "三录仪上有一条警告，你可以阅读。\n"+
            "\n 设备上的标记按钮显示：\n"+
            "* fscan: 读取所有继承的文件\t\t%^GREEN%^在线%^RESET%^\n"+
            "* deshadow: 移除对象上的所有阴影\t%^GREEN%^在线%^RESET%^\n"+
            "* extract: 移除异物或物质\t\t%^GREEN%^在线%^RESET%^（仅限弹丸）\n"+
            "* modhealth: 提高或降低生命值\t\t%^GREEN%^在线%^RESET%^\n"+
            "* modcaff: 提高或降低咖啡因水平\t%^GREEN%^在线%^RESET%^\n"+
            "* modalc: 提高或降低酒精水平\t\t%^GREEN%^在线%^RESET%^\n"+
            "* modfood: 提高或降低食物水平\t\t%^GREEN%^在线%^RESET%^\n"+
            "* moddrink: 提高或降低饮水水平\t\t%^GREEN%^在线%^RESET%^\n"+
            "* modmag: 提高或降低魔法水平\t\t%^GREEN%^在线%^RESET%^\n"+
            "* modstam: 提高或降低体力\t\t%^GREEN%^在线%^RESET%^\n"+
            "* modtox: 提高或降低毒素\t\t\t%^GREEN%^在线%^RESET%^\n"+
            "* setskill: 设置技能等级\t\t\t%^GREEN%^在线%^RESET%^\n"+
            "* setstat: 设置属性等级\t\t\t%^GREEN%^在线%^RESET%^\n"+
            "* amputate: 移除肢体\t\t\t%^GREEN%^在线%^RESET%^\n"+
            "* regenerate: 恢复所有截断的肢体\t%^GREEN%^在线%^RESET%^\n"+
            "* cure: 消除已知疾病\t\t\t%^GREEN%^在线%^RESET%^\n"+
            "* infect: 向患者引入疾病\t\t%^GREEN%^在线%^RESET%^\n"+
            "");
    SetRead( "default" , warning);
    SetRead( "warning", warning );
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(12);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
    add_action("fscan","fscan");
    add_action("assess","assess");
    add_action("assess","diagnose");
    add_action("extract","extract");
    add_action("addhp","addhp");
    add_action("addhp","modhealth");
    add_action("modcaff","modcaff");
    add_action("modalc","modalc");
    add_action("modfood","modfood");
    add_action("moddrink","moddrink");
    add_action("modmag","modmag");
    add_action("modstam","modstam");
    add_action("modtox","modtox");
    add_action("setstat","setstat");
    add_action("setskill","setskill");
    add_action("regenerate","regenerate");
    add_action("amputate","amputate");
    add_action("infect","infect");
    add_action("germ_scan","germscan");
    add_action("germ_squash","cure");
    add_action("medscan","medscan");
    add_action("posture","posture");
    add_action("enshadow","enshadow");
    add_action("deshadow","deshadow");
    add_action("TestFun","HEINEKEN");
}

int TestFun(){
    write("WOOHOO");
    return 1;
}

varargs int preAction(int restricted){
    scanner=this_player();
    tricorder=this_object();

    if(!this_player()) return 0;

    if(!present(tricorder, scanner)){
        write("你没有拿着三录仪。");
        return 2;
    }

    if(restricted && !creatorp(this_player())){
        write("此功能不允许建筑者使用。");
        return 2;
    }
    if(!builderp(this_player())){
        write("你渺小的凡人之心无法理解这个强大工具的用法。");
        log_file("adm/tricorder",capitalize(this_player()->GetKeyName())+
                " attempted to use the medical tricorder: "+timestamp()+"\n");
        tell_creators("安全警告："+capitalize(this_player()->GetKeyName())+
                "试图使用医疗三录仪。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 2;
    }

    say(scanner->GetName()+"操作着医疗三录仪。",scanner);
    write("三录仪发出低沉的嗡嗡声。");
    return 1;
}

int posture(int i){
    allowed=preAction();
    if(allowed == 2) return 1;
    if(!i) {
        write("请指定想要的姿态编号。");
        return 0;
    }
    this_player()->SetPosition(i);
    return i;
}

int deshadow(string str){
    object target;
    allowed=preAction(1);
    if(allowed == 2) return 1;
    if(str == "me") str = this_player()->GetKeyName();
    if(!target = present(str,this_player())){
        target = present(str,environment(this_player()));
    }
    if(!target){
        write("那不在这里。");
        return 1;
    }
    else {
        if(shadow(target,0)){
            remove_shadow(target);
            write("你已移除 "+str+" 上的阴影");
        }
        else write("那里没有阴影。");
    }
    return 1;
}

int enshadow(string str){
    object target;
    string s1,s2,s3,file;
    allowed=preAction(1);
    if(allowed == 2) return 1;
    if(sscanf(str,"%sshadow/%s %s",s1,s2,s3) > 0) file = s2;
    else if(sscanf(str,"%sshadow/%s.c %s",s1,s2,s3) > 0) file = s2;
    else if(sscanf(str,"%s %s",s1,s2) > 0) file = s1;
    else {
        write("你必须指定 /shadows 目录中的一个文件和一个目标。");
        return 1;
    }
    if( s3 && s3 != "") target = present(s3,environment(this_player()));
    else if(s3 == "me") target = this_player();
    else target = present(s2,environment(this_player()));

    if(!target) {
        write("请指定 /shadows 目录中的一个文件和一个目标。");
        return 1;
    }

    if(file_size("/shadow/"+file) < 1){
        write("这不是一个有效的阴影。");
        return 1;
    }

    new("/shadow/"+file)->eventShadow(target);
    write("你用 /shadow/"+file+" 对 "+target->GetName()+" 施加了阴影");
    return 1;
}

int medscan(string str){
    allowed=preAction();
    if(allowed == 2) return 1;
    if(!str || str == "") {
        write("请重新描述，这次请包含你的目标。");
        return 1;
    }
    if(str == "me") str = this_player()->GetKeyName();
    person=present(str,environment(scanner));
    if(!person  || !living(person)){
        write("疾病检查：未找到该生物");
        return 1;
    }
    write("正在扫描病菌...");
    this_object()->germ_scan(str);
    write("病菌扫描完成。\n");
    write("伤口扫描当前离线。");
    return 1;
}

int germ_scan(mixed strob ){
    int i;
    string a,b,c,str;
    if(stringp(strob)) {
        str = strob;
        if(str == "me") str = this_player()->GetKeyName();
        person=present(str,environment(scanner));
        if(!person  || !living(person)){
            write("未找到该生物。");
            return 2;
        }
    }
    if(objectp(strob)){
        person = strob;
        str = person->GetName();
    }
    if(!str || str == "") {
        write("请重新描述，这次请包含你的目标。");
        return 1;
    }
    if(!living(person)){
        write("该生物不是活的。");
        return 2;
    }
    ngstuff=all_inventory(person);
    gstuff = ({});
    say(scanner->GetName()+"用三录仪扫描了 "+person->GetName()+"。",({scanner,person}) );
    tell_object(person,scanner->GetName()+"用三录仪扫描了你。");

    for(i=0;i<sizeof(ngstuff);i++){
        if(ngstuff[i]->isGerm()== 1 && !sizeof(gstuff)) gstuff = ({ngstuff[i]});
        if(ngstuff[i]->isGerm()== 1 && sizeof(gstuff) > 0 ) gstuff += ({ngstuff[i]});
    }
    if(!sizeof(gstuff)){
        write(person->GetName()+"没有检测到疾病。");
        return 2;
    }
    for(i=0;i<sizeof(gstuff);i++){
        if(!a=gstuff[i]->GetKeyName() || a == ""  ) a = "普通疾病";
        if(!b=gstuff[i]->GetType() || b == ""  ) b = "未知类型";
        if(intp(gstuff[i]->GetCure())) c=gstuff[i]->GetCure();
        if(!c) c = 0;
        write("疾病："+a+"，类型："+b+"，严重程度："+c);
        return 1;
    }
    write("请指定一个与你同处的活的生物。");
    return 2;
}

int germ_squash(string str){
    int i,bar,c;
    object* whom;
    allowed=preAction(1);
    if(allowed == 2) return 1;
    if(!str || str == "") {
        write("请指定一个活的生物，或输入 \"all\" 治疗环境中的所有生物。");
        return 1;
    }
    if(str == "me") str = this_player()->GetKeyName();
    person=present(str,environment(scanner));
    whom = ({});
    if(!person && str !="all"){
        write("疾病检查：未找到该生物");
        return 1;
    }

    if( str !="all" && !living(person)){
        write("疾病检查：未找到该活的生物");
        return 1;
    }
    if(str =="all") whom = get_livings(environment(this_player()));
    if(str !="all") whom = ({person});
    foreach(object ingrate in whom){
        i=germ_scan(ingrate);
        if(i!=2 && intp(gstuff[i]->GetCure()) ) bar=gstuff[i]->GetCure();
        if(i!=2 && !intp(gstuff[i]->GetCure()) ) write("GetCure类型："+typeof(gstuff[i]->GetCure()));
        if(!i) { write("出现了极其奇怪的错误。"); return 1; }
        for(i=0;i<sizeof(gstuff);i++){
            if(gstuff[i] && gstuff[i]->isGerm() ){
                c=10;
                gstuff[i]->SetCure(c);
                if(intp(gstuff[i]->GetCure()) ){
                    gstuff[i]->eventCure(ingrate,c,gstuff[i]->GetType());
                    write("你治愈了 "+ingrate->GetName()+" 的疾病。");
                    say(ingrate->GetName()+"看起来更健康了。",ingrate);
                    tell_object(ingrate,"你感觉不那么难受了。");
                }
                if(gstuff[i] && gstuff[i]->isGerm() && !intp(gstuff[i]->GetCure())){
                    write("该疾病使用函数作为其 SetCure 条件。");
                    write("此设备无法治愈它。你需要手动检查病菌代码来确定治愈方法。");
                    write("SetCure() 数据类型："+typeof(gstuff[i]->GetCure()));
                    write("文件名："+base_name(gstuff[i])+"\n");
                }
            }
        }
        gstuff=({});
    }
    return 1;
}

int infect(string str){
    string whom,what,disease;
    object ob;
    mixed foo;
    allowed=preAction(1);
    if(allowed == 2) return 1;
    if(!str){
        write("请指定感染对象和疾病。示例：");
        write("infect doofus cold");
        write("当前有效疾病：cold, flu, fleas, lice, h1n1");
        return 1;
    }
    if(sscanf(str,"%s %s",whom,what)) {
        if(!whom || !what || whom == "" || what == ""){
            write("请指定感染对象和疾病。示例：");
            write("infect doofus cold");
            write("当前有效疾病：cold, flu, fleas, lice");
            return 1;
        }
    }
    if(!whom || !what || whom == "" || what == ""){
        write("请指定感染对象和疾病。示例：");
        write("infect doofus cold");
        write("当前有效疾病：cold, flu, fleas, lice");
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();
    person=present(whom,environment(scanner));
    if(!person  || !living(person)){
        write("未找到该生物。");
        return 1;
    }
    if(what == "cold") disease  = "/domains/town/obj/cold";
    else if(what == "flu") disease  = "/domains/town/obj/flu";
    else if(what == "fleas") disease  = "/domains/town/obj/fleas";
    else if(what == "lice") disease  = "/domains/town/obj/lice";
    else if(what == "rage") disease  = "/domains/town/obj/rage";
    else if(what == "h1n1") disease  = "/domains/town/obj/h1n1";
    else if(what != "") {
        write("这不是一个有效的疾病。");
        return 1;
    }
    if(person){
        write("已定位 "+person->GetName()+"。正在感染...");
        say(scanner->GetName()+"用三录仪指向了 "+person->GetName()+"。",person);
        if(present(whom,environment(scanner))) {
            tell_object(person,scanner->GetName()+"用三录仪指向了你。");
        }
    }
    ob=new(disease);
    if(ob) foo = ob->eventInfect(person);
    else write("该寄生虫有问题。");
    return 1;
}

int amputate(string str){
    string whom,which,limb,both;
    allowed=preAction();
    if(allowed == 2) return 1;
    if(!str){
        write("请指定你要截肢的对象和部位。示例：");
        write("amputate joey left hand");
        return 1;
    }
    if(sscanf(str,"%s %s %s",whom,which,limb)) {
        if(!limb) sscanf(str,"%s %s",whom,limb);
    }
    if(whom && whom == "me") whom = this_player()->GetKeyName();
    if(!whom || !limb){
        write("请指定你要截肢的对象和部位。示例：");
        write("amputate joey left hand");
        return 1;
    }
    if(!person=present(whom,environment(scanner))){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    both = limb;
    if(which && which !="") both = which+" "+limb;
    //write("both: "+both);

    if(!person->RemoveLimb(both, scanner)){
        write("你威胁性地挥动三录仪，但什么也没发生。");
        tell_room(environment(person),scanner->GetName()+"以威胁的方式用三录仪指向了"+person->GetName()+"。", ({ scanner,person }) );
        tell_object(person,scanner->GetName()+"威胁性地用"+possessive(scanner)+"三录仪指向了你。");
        return 1;
    }

    if(both == "head"){
        tell_room(environment(person),scanner->GetName()+"用三录仪指向了"+person->GetName()+"，"+
                person->GetName()+"的头掉了下来！", ({ scanner,person }) );
        write("你斩首了"+person->GetName()+"。");
        tell_object(person,scanner->GetName()+"用三录仪一挥斩下了你的头！");
        //person->RemoveLimb(both, scanner);
        return 1;
    }
    stumps=person->GetLimbs();
    if(!stumps) {
        write(person->GetName()+"没有任何肢体。");
        say(scanner->GetName()+"用三录仪扫描了"+person->GetName()+"。",scanner,person);
        tell_object(person,scanner->GetName()+"用三录仪扫描了你。");
        return 1;
    }
    if(member_array(both,stumps) != -1){
        person->RemoveLimb(both, scanner);
        write("你截断了"+person->GetName()+"的"+both);
        say(scanner->GetName()+"用医疗三录仪的能量光束截断了"+person->GetName()+"的"+both+"。",scanner,person);
        tell_object(person,scanner->GetName()+"用三录仪指向了你，你的"+both+"被切断了。");
        return 1;
    }
    if(member_array(limb,stumps)!= -1){
        //person->RemoveLimb(limb, scanner);
        write("你截断了"+person->GetName()+"的"+limb+"。");
        say(scanner->GetName()+"用医疗三录仪的能量光束截断了"+person->GetName()+"的"+both+"。",scanner,person);
        tell_object(person,scanner->GetName()+"用三录仪指向了你，你的"+limb+"被切断了。");
        return 1;
    }
    //write("There is some sort of problem, it looks like. No "+
    //"limbs are severed.");
    return 1;
}

int regenerate(string str){
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("请指定你要再生肢体的对象。");
        return 1;
    }
    if(str == "me") str = this_player()->GetKeyName();
    if(!person=present(str,environment(scanner))){
        write(capitalize(str)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    stumps=person->GetMissingLimbs();
    if(!stumps) {
        write(person->GetName()+"没有缺失任何肢体。");
        say(scanner->GetName()+"用三录仪扫描了"+person->GetName()+"。",scanner,person);
        tell_object(person,scanner->GetName()+"用三录仪扫描了你。");
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    for(i=0;i<sizeof(stumps);i++){
        person->RestoreLimb(stumps[i]);
        write("你再生了"+person->GetName()+"的"+stumps[i]+"。");
        say(scanner->GetName()+"再生了"+person->GetName()+"的"+stumps[i]+"。",scanner,person);
        tell_object(person,scanner->GetName()+"再生了你的"+stumps[i]+"。");
    }
    return 1;
}

int DoSkillChange(string str, int i){
    int more_or_less;
    if(str == "me") str = this_player()->GetKeyName();
    this_skill = person->GetSkill(str);
    if(this_skill["level"] < i) more_or_less = 1;
    skillclass=this_skill["class"];
    person->SetSkill(str,i,skillclass);
    say(scanner->GetName()+"用医疗三录仪扫描了"+person->GetName()+"。",({person,scanner}));
    tell_object(person,scanner->GetName()+"用医疗三录仪扫描了你。");
    if(more_or_less == 1) tell_room(environment(person), person->GetName()+"看起来更有经验了。",({person}) );
    if(more_or_less != 1) tell_room(environment(person), person->GetName()+"看起来经验有所不足。",({person}) );
    write("你已将"+person->GetName()+"的"+str+"设置为等级"+i+"。");
    return 1;
}
int DoAllSkills(int foo){
    int i;
    for(i=0;i<sizeof(skilllist);i++){
        this_skill = person->GetSkill(skilllist[i]);
        skillclass=this_skill["class"];
        person->SetSkill(skilllist[i],foo,skillclass);
        write("你已将"+person->GetName()+"的"+skilllist[i]+"设置为等级"+foo+"。");
    }
    say(scanner->GetName()+"用医疗三录仪扫描了"+person->GetName()+"。",({person,scanner}));
    say(person->GetName()+"似乎经历了一种几乎无法察觉的微妙变化。",({person,scanner}));
    tell_object(person,scanner->GetName()+"用医疗三录仪扫描了你。");
    return 1;
}
int setskill(string str){
    string whom,skill;
    string skill1,skill2,rubbish;
    int amt;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str) {
        write("语法：setskill <人物> <技能> <数值>");
        write("如果技能名称中有空格，请用下划线替换。示例：\nsetskill schmucky blade_attack 5");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!sscanf(str,"%s %s %d",whom,skill,amt)) { sscanf(str,"%s %s",whom,skill);  }
    if(sscanf(str,"%s %s_%s ",rubbish,skill1,skill2) && skill1 && skill2){
        whom = rubbish;
        skill = skill1 + " " +skill2;
    }
    write("技能："+skill);
    if(!whom || whom == ""){
        write("语法：setskill <人物> <技能> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();
    if(!person=present(whom,environment(scanner))){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    this_skill = ([]);
    skilllist = ({});
    skilllist = person->GetSkills();
    if(amt < 0) amt = 0;
    if(allowed==2) return 1;
    if ( !whom || !skill || !amt || !intp(amt) ){
        write("语法：setskill <人物> <技能> <数值>");
        write("如果技能名称中有空格，请用下划线替换。示例：\nsetskill schmucky blade_attack 5");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(skill == "all") { DoAllSkills(amt); return 1; }
    if(member_array(skill,skilllist) == -1) {
        write(capitalize(whom)+"没有那个技能。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    DoSkillChange(skill, amt);
    return 1;
}
int DoStatChange(string str, int i){
    if(str == "me") str = this_player()->GetKeyName();
    this_stat = person->GetStat(str);
    statclass=this_stat["class"];
    person->SetStat(str,i,statclass);
    say(scanner->GetName()+"用医疗三录仪扫描了"+person->GetName()+"。",({person,scanner}));
    tell_object(person,scanner->GetName()+"用医疗三录仪扫描了你。");
    write("你已将"+person->GetName()+"的"+str+"设置为等级"+i+"。");
    return 1;
}
int DoAllStats(int foo){
    int i;
    for(i=0;i<sizeof(statlist);i++){
        this_stat = person->GetStat(statlist[i]);
        statclass=this_stat["class"];
        person->SetStat(statlist[i],foo,statclass);
        write("你已将"+person->GetName()+"的"+statlist[i]+"设置为等级"+foo+"。");
    }
    say(scanner->GetName()+"用医疗三录仪扫描了"+person->GetName()+"。",({person,scanner}));
    tell_object(person,scanner->GetName()+"用医疗三录仪扫描了你。");
    return 1;
}
int setstat(string str){
    string whom,stat;
    int amt;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str) {
        write("语法：setstat <人物> <属性> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!sscanf(str,"%s %s %d",whom,stat,amt)) { sscanf(str,"%s %s",whom,stat);  }
    if(!whom || whom == ""){
        write("语法：setstat <人物> <属性> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();
    if(!person=present(whom,environment(scanner))){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    this_stat = ([]);
    statlist = ({});
    statlist = person->GetStats();
    if(amt < 0) amt = 0;
    if(allowed==2) return 1;
    if ( !whom || !stat || !amt || !intp(amt) ){
        write("语法：setstat <人物> <属性> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(stat == "all") { DoAllStats(amt); return 1; }
    if(member_array(stat,statlist) == -1) {
        write(capitalize(whom)+"没有那个属性。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    DoStatChange(stat, amt);
    return 1;
}
int modstam(string str, int stamina){
    string whom;
    int tempint,staminalevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：modstam <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,stamina);
    if (!whom || !stamina){
        write("语法：modstam <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();
    if(!intp(stamina)){
        write("语法：modstam <人物> <数值>");
        write("其中<数值>为整数。示例：\nmodstam joe 3\nmodstam mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    staminalevel=person->GetStaminaPoints();
    tempint = staminalevel + stamina;
    if(tempint < 0) {
        stamina = stamina + absolute_value(tempint);
    }
    person->AddStaminaPoints(stamina);
    if(stamina > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更轻松了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更强壮了。");
        write("你已将"+capitalize(whom)+"的体力提升了"+stamina+"点。");
        return 1;
    }
    if(stamina < 0){
        stamina=absolute_value(stamina);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来不太舒服。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更虚弱了。");
        write("你已将"+capitalize(whom)+"的体力降低了"+stamina+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int modtox(string str, int poison){
    string whom;
    int tempint,poisonlevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：modtox <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,poison);
    if (!whom || !poison){
        write("语法：modtox <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();
    if(!intp(poison)){
        write("语法：modtox <人物> <数值>");
        write("其中<数值>为整数。示例：\nmodtox joe 3\nmodtox mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    poisonlevel=person->GetPoison();
    tempint = poisonlevel + poison;
    if(tempint < 0) {
        poison = poison + absolute_value(tempint);
    }
    person->AddPoison(poison);
    if(poison > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更苍白且在颤抖。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到不适。");
        write("你已将"+capitalize(whom)+"的毒素提升了"+poison+"点。");
        return 1;
    }
    if(poison < 0){
        poison=absolute_value(poison);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来不那么难受了。", ({person,scanner})
           );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感觉比之前好多了。");
        write("你已将"+capitalize(whom)+"的毒素降低了"+poison+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int modmag(string str, int magic){
    string whom;
    int tempint,magiclevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：modmagic <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,magic);
    if (!whom || !magic){
        write("语法：modmagic <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();

    if(!intp(magic)){
        write("语法：modmagic <人物> <数值>");
        write("其中<数值>为整数。示例：\nmodmagic joe 3\nmodmagic mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    magiclevel=person->GetMagicPoints();
    tempint = magiclevel + magic;
    if(tempint < 0) {
        magic = magic + absolute_value(tempint);
    }
    person->AddMagicPoints(magic);
    if(magic > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"短暂地发出了光芒。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到魔力充盈。");
        write("你已将"+capitalize(whom)+"的魔法提升了"+magic+"点。");
        return 1;
    }
    if(magic < 0){
        magic=absolute_value(magic);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来平淡了些。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到魔力减退了。");
        write("你已将"+capitalize(whom)+"的魔法降低了"+magic+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int moddrink(string str, int drink){
    string whom;
    int tempint,drinklevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：moddrink <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,drink);
    if (!whom || !drink){
        write("语法：moddrink <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();

    if(!intp(drink)){
        write("语法：moddrink <人物> <数值>");
        write("其中<数值>为整数。示例：\nmoddrink joe 3\nmoddrink mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    drinklevel=person->GetDrink();
    tempint = drinklevel + drink;
    if(tempint < 0) {
        drink = drink + absolute_value(tempint);
    }
    person->AddDrink(drink);
    if(drink > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更轻松了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到不那么渴了。");
        write("你已将"+capitalize(whom)+"的饮水提升了"+drink+"点。");
        return 1;
    }
    if(drink < 0){
        drink=absolute_value(drink);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来不太舒服。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更渴了。");
        write("你已将"+capitalize(whom)+"的饮水降低了"+drink+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int modfood(string str, int food){
    string whom;
    int tempint,foodlevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：modfood <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,food);
    if (!whom || !food){
        write("语法：modfood <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();

    if(!intp(food)){
        write("语法：modfood <人物> <数值>");
        write("其中<数值>为整数。示例：\nmodfood joe 3\nmodfood mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    foodlevel=person->GetFood();
    tempint = foodlevel + food;
    if(tempint < 0) {
        food = food + absolute_value(tempint);
    }
    person->AddFood(food);
    if(food > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更轻松了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更饱了。");
        write("你已将"+capitalize(whom)+"的食物提升了"+food+"点。");
        return 1;
    }
    if(food < 0){
        food=absolute_value(food);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来不太舒服。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更饿了。");
        write("你已将"+capitalize(whom)+"的食物降低了"+food+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int modcaff(string str, int caff){
    string whom;
    int tempint,cafflevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：modcaff <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,caff);
    if (!whom || !caff){
        write("语法：modcaff <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();

    if(!intp(caff)){
        write("语法：modcaff <人物> <数值>");
        write("其中<数值>为整数。示例：\nmodcaff joe 3\nmodcaff mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    cafflevel=person->GetCaffeine();
    tempint = cafflevel + caff;
    if(tempint < 0) {
        caff = caff + absolute_value(tempint);
    }
    person->AddCaffeine(caff);
    if(caff > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更敏锐了些。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到有些亢奋。");
        write("你已将"+capitalize(whom)+"的咖啡因提升了"+caff+"点。");
        return 1;
    }
    if(caff < 0){
        caff=absolute_value(caff);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更专注清醒了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更清醒了。");
        write("你已将"+capitalize(whom)+"的咖啡因降低了"+caff+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int modalc(string str, int alc){
    string whom;
    int tempint,alclevel;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：modalc <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,alc);
    if (!whom || !alc){
        write("语法：modalc <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();

    if(!intp(alc)){
        write("语法：modalc <人物> <数值>");
        write("其中<数值>为整数。示例：\nmodalc joe 3\nmodalc mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }

    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    alclevel=person->GetAlcohol();
    tempint = alclevel + alc;
    if(tempint < 0) {
        alc = alc + absolute_value(tempint);
    }

    person->AddAlcohol(alc);
    if(alc > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更眩晕和迷失方向。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到有些醉意。");
        write("你已将"+capitalize(whom)+"的酒精提升了"+alc+"点。");
        return 1;
    }
    if(alc < 0){
        alc=absolute_value(alc);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更专注清醒了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更清醒了。");
        write("你已将"+capitalize(whom)+"的酒精降低了"+alc+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int addhp(string str, int hp){
    string whom;
    object person;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("语法：addhp <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s %d",whom,hp);
    if (!whom || !hp){
        write("语法：addhp <人物> <数值>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();

    if(!intp(hp)){
        write("语法：addhp <人物> <数值>");
        write("其中<数值>为整数。示例：\naddhp joe 3\naddhp mike -10\n");
        say(scanner->GetName()+"愚蠢地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    person->AddHP(hp);
    if(hp > 0){
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更强壮更有精神了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更强壮更有精神了。");
        write("你已将"+capitalize(whom)+"的生命值提升了"+hp+"点。");
        return 1;
    }
    if(hp < 0){
        hp=absolute_value(hp);
        say(scanner->GetName()+"用医疗三录仪指向"+capitalize(whom)+"，"+
                ""+nominative(person)+"看起来更虚弱更萎靡了。", ({person,scanner}) );
        tell_object(person,scanner->GetName()+"用医疗三录仪指向了你，你突然感到更虚弱更脆弱了。");
        write("你已将"+capitalize(whom)+"的生命值降低了"+hp+"点。");
        return 1;
    }
    write("无效。");
    return 1;
}
int extract(string str){
    string what,whom;
    object person, slug;
    int rifleshot_wounds,firearms_wounds,wounds;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str){
        write("从谁身上提取什么？");
        write("示例：extract slug from <人物>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    sscanf(str,"%s from %s",what,whom);
    if (!what || ! whom){
        write("从谁身上提取什么？");
        write("示例：extract slug from <人物>");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(whom == "me") whom = this_player()->GetKeyName();
    person=present(whom,environment(scanner));
    if(!person){
        write(capitalize(whom)+"不在这里。");
        say(scanner->GetName()+"笨拙地摆弄着医疗三录仪。",scanner);
        return 1;
    }
    if(!creatorp(this_player()) && strsrch(base_name(person), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    slug=present("firearms_wound",person);
    wounds=0;
    wounds=person->GetLead("gunshot_wounds");
    wounds+=person->GetLead("rifleshot_wounds");
    if(!slug && what=="slug"){
        write(capitalize(whom)+"没有枪伤。");
        say(scanner->GetName()+"用医疗三录仪对着"+capitalize(whom)+"比划，看起来有点傻。",({ scanner, person }) );
        tell_object(person,scanner->GetName()+"用医疗三录仪对着你比划，看起来有点傻。");
        return 1;
    }
    if(slug && what=="slug" && wounds > 0 ){
        write("你从"+capitalize(whom)+"的身体中取出了一个铅弹头。");
        say(scanner->GetName()+"用医疗三录仪灵巧地从"+capitalize(whom)+"身上取出了一个铅弹头。",({ scanner, person }) );
        tell_object(person,scanner->GetName()+"用医疗三录仪灵巧地从你身上取出了一个铅弹头。");
        firearms_wounds=person->GetLead("firearms_wounds");
        rifleshot_wounds=person->GetLead("rifleshot_wounds");
        slug=new("/domains/town/obj/spent");
        if(person->GetLead("gunshot_wounds") > 0) {
            person->AddLead("gunshot_wounds", -1);
            slug->SetShort("一枚用过的手枪弹壳");
            --wounds;
            slug->eventMove(environment(scanner));
            if(person->GetLead() < 1){
                slug=present("firearms_wound",person);
                if(slug) slug->eventDestruct();
                return 1;
            }
            return 1;
        }
        if(person->GetLead("rifleshot_wounds") > 0) {
            person->AddLead("rifleshot_wounds", -1);
            slug->SetShort("一枚用过的步枪弹壳");
            --wounds;
            slug->eventMove(environment(scanner));
            if(person->GetLead() < 1){
                if(slug) slug->eventDestruct();
                slug=present("firearms_wound",person);
                if(slug) slug->eventDestruct();
                return 1;
            }
        }
        slug->eventMove(environment(scanner));
        slug=present("firearms_wound",person);
        if(wounds < 1 && slug){
            slug->eventDestruct();
            return 1;
        }
    }
    return 1;
}
int fscan(string str){
    object ob;
    object *stuffs;
    mixed *stuff;
    allowed=preAction();
    if(allowed==2) return 1;
    if(!str || str=="" || str=="here") {
        ob = environment(this_player());
        name = ob->GetShort();
        str = base_name(ob);
    }
    if(str == "me") str = this_player()->GetKeyName();
    if(present(str,this_player())) {
        ob = present(str,this_player());
        name = ob->GetName();
    }
    if(present(str,environment(this_player()))) {
        ob=present(str,environment(this_player()));
        name = ob->GetName();
    }
    if(!ob){
        write("三录仪无法定位该人物、对象或环境。\n");
        say(this_player()->GetName()+"漫无目的地用医疗三录仪扫描着。\n");
        return 1;
    }
    write("你对"+name+"执行了文件扫描。\n\n");
    write("\n"+name+"拥有以下物品：");
    write("-------------------------------------------");
    say(this_player()->GetName()+"用三录仪扫描了"+name+"。\n",ob);
    tell_object(ob,this_player()->GetName()+"用医疗三录仪扫描了你。\n");
    stuffs=deep_inventory(ob);
    filter(stuffs, (: this_object()->analyze(file_name($1)) :), this_object());
    filter(stuffs, (: this_object()->getname($1) :), this_object());
    stuff=deep_inherit_list(ob);
    write("\n"+name+"由以下文件组成：\n");
    write("-------------------------------------------");
    foreach(mixed gene in deep_inherit_list(ob)) {
        if(!stringp(gene)) break;
        if(!gene) gene="";
        write(gene);
    }
    write("\n扫描完成");
    return 1;
}
void analyze(string str){
    string temp, temp2;
    sscanf(str,"%s#%s",temp,temp2);
    if(temp=="/lib/corpse"){
        write("发现一具尸体。绝对名称：\n"+str);
        return;
    }
    return;
}
string getname(object ob){
    string temp, temp2;
    if(!ob) return "未找到对象。";
    else
        sscanf(file_name(ob),"%s#%s",temp,temp2);
    write(ob->GetName()+",\t\t文件名："+temp+".c");
    return ob->GetName();
}
mixed assess(string args) {
    string *lines, *arr, *limbs;
    object ob;
    string tmp1, tmp2;
    int i, x, y, cols;
    if( args == "" || !args ) return 0;
    if(args == "me") args = this_player()->GetKeyName();
    if( !(ob = present(args, environment(this_player()))) )
        if( !(ob = find_player(convert_name(args))) &&
                !(ob = find_living(lower_case(args))) )
            return capitalize(args) + "无处可寻。";
    if( creatorp(ob) ) return "你无法获取创造者的属性信息。";
    if(!creatorp(this_player()) && strsrch(base_name(ob), homedir(this_player()))){
        write("建造者只能对他们自己的NPC执行此操作。");
        return 1;
    }
    if(tmp1 = ob->GetGender()) {
        cols = ((int *)this_player()->GetScreen())[0];
        tmp1 = ob->GetCapName() + " aka " + ob->GetShort() +
            ", level " + ob->GetLevel() + " " + ob->GetGender();
        if( !(tmp2 = ob->GetRace()) ) tmp2 = "blob";
        tmp1 += " " + tmp2;
        if( !(tmp2 = ob->GetClass()) ) tmp2 = "drifter";
        tmp1 += " " + capitalize(tmp2);
        if( tmp2 = ob->GetSpouse() )
            tmp1 += " (spouse: " + tmp2 + ")";
        lines = ({ center(tmp1, cols) });
        if( ob->GetUndead() ) tmp1 = "Undead";
        else tmp1 = "Alive";
        if( ob->GetSleeping() ) tmp1 += " / Sleeping";
        else tmp1 += " / Awake";
        if( ob->GetParalyzed() ) tmp1 += " / Paralyzed";
        lines += ({ center(tmp1, cols), "" });
        lines += ({ center("Health: " +ob->GetHealthPoints() + "/"+
                    ob->GetMaxHealthPoints() + "   Magic: " +
                    ob->GetMagicPoints() + "/" +
                    ob->GetMaxMagicPoints() + "   Stamina: " +
                    ob->GetStaminaPoints() + "/" +
                    to_int((float)ob->GetMaxStaminaPoints()) + "   Carry: " +
                    ob->GetCarriedMass() + "/" +
                    ob->GetMaxCarry(), cols) });
        lines += ({ center("Food: " + ob->GetFood() + "    " +
                    "Drink: " + ob->GetDrink() + "    " +
                    "Alcohol: " + ob->GetAlcohol() + "    " +
                    "Caffeine: " + ob->GetCaffeine() + "    " +
                    "Poison: " + ob->GetPoison() + "    ", cols) });
        lines += ({ center("Training Points: " + ob->GetTrainingPoints()) });
        lines += ({ "", "Limbs:" });
        limbs = ob->GetWieldingLimbs();
        arr = map(ob->GetLimbs(),
                (: sprintf("%:-14s%s (%d) %d/%d", $1,
                           ((member_array($1, $(limbs)) == -1) ? " " : "*"),
                           ($(ob))->GetLimbClass($1),
                           ($(ob))->GetHealthPoints($1),
                           ($(ob))->GetMaxHealthPoints($1)) :));
        i = sizeof(arr);
        while(i--) if( (y = strlen(arr[i])) > x ) x = y;
        x = cols/(x+2);
        lines += explode(format_page(arr, x), "\n") + ({ "", "Skills:" });
        arr = map(ob->GetSkills(),
                function(string skill, object who) {
                mapping mp = who->GetSkill(skill);
                int x;
                x = to_int(percent(mp["points"],
                        who->GetMaxSkillPoints(skill, mp["level"])));
                return sprintf("%:-18s (%d) %:2d%% - %d/%d",
                    skill, mp["class"], x,
                    who->GetSkillLevel(skill), mp["level"] );
                }, ob);
        i = sizeof(arr);
        while(i--) if( (y = strlen(arr[i])) > x ) x = y;
        x = cols/(x+2);
        lines += explode(format_page(arr, x), "\n") + ({ "", "Stats:" });
        arr = map(ob->GetStats(),
                (: sprintf("%:-12s (%d) %d/%d", $1,
                           ($(ob))->GetStatClass($1),
                           ($(ob))->GetStatLevel($1),
                           ($(ob))->GetBaseStatLevel($1)) :));
        i = sizeof(arr);
        x = 0;
        while(i--) if( (y = strlen(arr[i])) > x ) x = y;
        x =cols/(x+2);
        lines += explode(format_page(arr, x), "\n");
        lines += ({ "", ob->GetName()+" has amassed a net worth of " +
                ( ob->GetNetWorth() * currency_rate("gold") ) + " gold."});
        arr = filter( map(ob->GetCurrencies(),
                    (: ($(ob))->GetCurrency($1) &&
                     sprintf("%d %s", ($(ob))->GetCurrency($1), $1) :)),
                (: $1 :));
        lines += ({ "Money on hand: "+implode(arr, ", ") });
        this_player()->eventPage(lines, "system");
        return 1;
    }
    else {
        write("你无法查看非活物的属性！");
        return 1;
    }
}
