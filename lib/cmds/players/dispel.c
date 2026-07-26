#include <lib.h>
#include <cfg.h>
#include <magic_protection.h>
#include <function.h>

inherit LIB_DAEMON;


mixed cmd(string args) {

    if(!args){
        write("驱散什么？");
        return 1;
    }
    if(args == "meditate"){
        object mojo = present("meditate mojo", this_player());
        if(!mojo){
            write("你没有冥想魔力可以驱散。");
            return 1;
        }
        write("你驱散了身上的冥想魔力。");
        mojo->eventDispel();
    }
    if(args == "whip"){
        object whip = present_file("/obj/whip", this_player());
        if(!whip){
            write("你没有鞭子可以驱散。");
            return 1;
        }
        write("你驱散了身上的鞭子。");
        whip->eventDispel();
    }
    if(args == "buffer"){
        class MagicProtection *Protections;
        Protections = this_player()->GetMagicProtection();
        foreach(class MagicProtection tmp in Protections){
            if(!tmp->obname) continue;
            if(tmp->obname == "/powers/spells/buffer"){
                if(!(functionp(tmp->hit) & FP_OWNER_DESTED)){
                    write("你驱散了防护罩。");
                    this_player()->RemoveMagicProtection("/powers/spells/buffer");
                    return 1;
                }
            }
        }
        write("你没有防护罩可以驱散。");
        return 1;
    }
    if(args == "greater buffer"){
        class MagicProtection *Protections;
        Protections = this_player()->GetMagicProtection();
        foreach(class MagicProtection tmp in Protections){
            if(!tmp->obname) continue;
            if(tmp->obname == "/powers/spells/greater_buffer"){
                if(!(functionp(tmp->hit) & FP_OWNER_DESTED)){
                    write("你驱散了高级防护罩。");
                    this_player()->RemoveMagicProtection("/powers/spells/greater_buffer");
                    return 1;
                }
            }
        }
        write("你没有高级防护罩可以驱散。");
        return 1;
    }
    return 1;
}


string GetHelp(){
    return ("用法: dispel <法术名>\n\n"
            "驱散指定的魔法效果（如果适用）。\n"
            "\n参考: cast");
}
