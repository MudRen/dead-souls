/* remote control by Cratylus @ Frontiers
 * Sep 21 2005
 */

#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
int controlling;
string remote, control_code;
object owner;

void create(){
    ::create();
    SetKeyName("remote control");
    SetId(({"device","controller","remote","control"}));
    SetAdjectives(({"small","electronic"}));
    SetShort("遥控器");
    SetLong("这是一个小型电子设备，上面有各种标记的按钮。"+
            "看起来你可以用它\"控制某物\"，也可以\"释放\"它。"+
            "要命令你的远程仆人，你需要在命令前加上]字符（例如：] look at menu）。");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(20);
    SetVendorType(VT_TREASURE);
    control_code = alpha_crypt(16);
}

void init(){
    ::init();
    if(living(environment())) owner = environment();
    else owner = 0;
    add_action("control","control");
    add_action("release","release");
    add_action("do_control","]");
}

int control(string str){
    object ob;
    string *eyedees;
    if(!str){
        return 0;
    }
    ob=present(str, environment(this_player()));
    if(!ob){
        write("这里没有可以控制的东西。");
        return 1;
    }
    if(!builderp(this_player())){
        write("你渺小的凡人之心无法理解这个强大工具的用法。");
        log_file("adm/control",capitalize(this_player()->GetKeyName())+
                " attempted to use the remote control on "+str+": "+timestamp()+"\n");
        tell_creators("SECURITY: "+capitalize(this_player()->GetKeyName())+
                " attempted to use the remote control on "+str+".");
        return 1;
    }
    if(!living(ob)){
        write(capitalize(ob->GetKeyName())+"不是活物。");
        return 1;
    }

    if(!creatorp(this_player()) && strsrch(base_name(ob), homedir(this_player()))){
        write("只有创造者才能控制不属于他们的NPC。");
        say(this_player()->GetName()+"试图控制"+ob->GetName()+"，但失败了。\n");
        return 1;
    }
    if(!strsrch(base_name(ob),"/secure") ){
        write(ob->GetName()+"无法用这个设备控制。");
        say(this_player()->GetName()+"试图控制"+ob->GetName()+"，但失败了。\n");
        return 1;
    }
    if(controlling){
        write("你的遥控器正在控制其他生物。");
        return 1;
    }
    if(ob->GetOwner() && ob->GetOwner() != "NONE"){
        write("那个生物已经在别人的控制之下了。");
        return 1;
    }
    if(!(ob->GetOwner())) new("/shadows/drone")->eventShadow(ob);
    remote=file_name(ob);
    ob->SetOwner(this_player()->GetKeyName(), this_player());
    ob->SetListen(1);
    ob->SetControlCode(control_code);
    eyedees = ob->GetId();
    eyedees += ({"servant","drone","thrall"});
    ob->SetId(eyedees);
    write("你与"+capitalize(str)+"建立了远程控制连接。");
    say(this_player()->GetName()+"与"+capitalize(str)+"建立了控制链接。");
    controlling=1;
    return 1;
}

int do_control(string str){
    object obj;
    if(!controlling){
        write("你目前没有与任何活物连接。");
        return 1;
    }
    if(!str || str == ""){
        write("什么都没发生。");
        return 1;
    }
    if(environment() != owner){
        write("你似乎没有遥控器。");
        tell_object(environment(),"遥控器可能存在安全违规。");
        error("非法访问遥控器："+get_stack()+" "+identify(previous_object(-1)));
        return 1;
    }
    obj=find_object(remote);
    if(obj) obj->eventReceiveCommand(str);
    else {
        write("似乎出了点问题。");
        this_object()->release();
    }
    return 1;
}

int release(){
    object dingus;
    if(remote && dingus=find_object(remote) ){
        dingus->SetOwner("NONE");
        remove_shadow(dingus);
    }
    controlling=0;
    write("你释放了远程链接。");
    return 1;
}

string GetControlCode(){
    if(base_name(previous_object()) != "/shadows/drone") return alpha_crypt(16);
    else return control_code;
}
