#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("ignore");
    SetRules("LVS","");
    SetErrorMessage("你想忽略谁？");
    SetHelp("用法：ignore <生物 | all>\n\n"
            "允许你停止攻击一个或多个生物。有助于不在错误的目标上浪费时间。\n"
            "另见：attack\n");
}

mixed can_ignore(){ return 1; }

mixed can_ignore_liv() { return 1; }

mixed do_ignore(){
    if(sizeof(this_player()->GetNonTargets())){
        string tmp;
        tmp = item_list(this_player()->GetNonTargets());
        this_player()->eventPrint("你正在忽略" + tmp + "。");
        return 1;
    }
    else {
        this_player()->eventPrint("忽略谁？");
        return 0;
    }
}

mixed do_ignore_liv(object ob) {
    this_player()->AddNonTargets(ob);
    if(member_array(ob,this_player()->GetNonTargets()) != -1){

        this_player()->eventPrint("你现在正在忽略" + ob->GetName() + "。");
        ob->eventPrint(this_player()->GetName() + "忽略了你！");
        environment(this_player())->eventPrint(this_player()->GetName() +
                "忽略了" + ob->GetName() + "！",
                ({ this_player(), ob }));
    }
    else this_player()->eventPrint("你无法忽略" + ob->GetName() + "。");
    return 1;
}

mixed do_ignore_lvs(mixed *targets) {
    object *obs;
    string tmp;

    obs = filter(targets, (: objectp :));
    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(targets, (: $1 :));
        foreach(string *lines in ua) this_player()->eventPrint(lines[0]);
        return 1;
    }
    if(member_array(this_player(),obs) != -1) obs -= ({ this_player() });
    this_player()->AddNonTargets(obs);
    tmp = item_list(obs);
    obs->eventPrint(this_player()->GetName() + "忽略了你！");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "忽略了" + tmp + "！",
            ({ this_player(), obs... }));
    this_player()->eventPrint("你忽略了" + tmp + "。");
    return 1;
}
