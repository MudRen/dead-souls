#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_INSTALL;

void create(){
    ::create();
    SetKeyName("orange vial");
    SetId( ({"vial"}) );
    SetAdjectives( ({"small","transparent","orange","glowing"}) );
    SetShort("一个发光的橙色小瓶");
    SetLong("一个小的透明小瓶，装满了发光的橙色液体。");
    SetMass(10);
    SetBaseCost("silver",1000);
    SetMaxClones(3);
    SetNoCondition(1);
    SetVendorType(VT_TREASURE);
}

varargs mixed eventInstall(object what, object where, int auto){
    int ret = this_object()->eventMove(where);
    string wat = remove_article(where->GetShort());
    if(ret){
        write("你将"+GetShort()+"安装到了"+wat+"中。");
        say(this_player()->GetName()+" installs "+GetShort()+" into "+
                where->GetShort()+".");
        return 1;
    }
    else {
        write("安装失败了。");
        return 0;
    }
}

varargs mixed eventUninstall(object what, mixed auto){
    int success;
    object contenv, env = environment(this_object());
    if(!env || base_name(env) != "/domains/default/obj/generator"){
        write("它没有被安装。");
        return 0;
    }

    if(!env || !environment(env) || env == this_player()){
        write("它似乎没有安装在任何地方。");
        return 0;
    }

    contenv = environment(env);

    if(contenv != this_player() && contenv != environment(this_player())){
        write("那不是你的，不能卸载。");
        return 0;
    }

    success = this_object()->eventMove(this_player());
    if(!success){
        write("卸载失败了。");
        return 0;
    }
    else {
        write("你从"+env->GetShort()+"中卸载了"+GetShort()+"。");
        say(this_player()->GetName()+" uninstalls "+GetShort()+" from "+
                possessive(this_player())+" "+env->GetShort()+".");
        return 1;
    }
}

void init(){
    ::init();
}
