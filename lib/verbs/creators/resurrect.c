#include <lib.h>
#include <daemons.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>
#include <position.h>

inherit LIB_VERB;
string *carried = ({});

protected void create() {
    verb::create();
    SetVerb("resurrect");
    SetRules("OBJ", "here");
    SetErrorMessage("复活什么？");
    SetHelp("用法：resurrect <物品>\n\n"
            "复活已死亡的生物。当用于玩家的尸体时，可以将他们从死亡中带回，且不会有技能或经验惩罚。\n"
            "另见：zap, dest");
}

mixed can_resurrect_obj(string str) {
    if(!creatorp(this_player()))
        return "此命令仅对创造者可用。";
    else return 1;
}

mixed do_resurrect_obj(object ob) {
    int corpse;
    object playerob;
    if(ob->isCorpse()) corpse = 1;
    if(interactive(ob)) playerob = ob;
    if( ob->isPlayer() ) playerob = ob->GetPlayerob();
    if( ob->isPlayer() && !playerob ){
        write("你无法复活不在线的玩家。");
        return 1;
    }
    if((playerob && !playerob->GetGhost()) || living(ob)) {
        write("你无法复活活着的生物。");
        return 1;
    }

    if(base_name(ob) != LIB_CORPSE){
        write("你只能复活血肉之躯的生物。");
        return 1;
    }

    if(environment(ob) != environment(this_player())) {
        write(capitalize(ob->GetKeyName())+"不在这里。");
        return 1;
    }

    tell_player(this_player(),"你挥了挥手，伴随着一道闪光，"+
            ob->GetCapName()+"复活了！");
    tell_player(ob,capitalize(this_player()->GetKeyName())+"挥了"+
            possessive(this_player())+
            "手，伴随着一道闪光，你从死亡中复活了！");
    tell_room(environment(this_player()),this_player()->GetCapName()+"挥了"+
            possessive(this_player())+
            "手，伴随着一道闪光，"+ob->GetCapName()+
            "复活了！",
            ({ob, this_player()}) );
    if(playerob){
        object *inv;
        playerob->eventRevive(1);
        playerob->eventMove(environment(this_player()));
        inv = all_inventory(ob);
        if(sizeof(inv)) inv->eventMove(playerob);
        inv = all_inventory(ob);
        if(sizeof(inv)) inv->eventMove(environment(this_player()));
        ob->eventMove(ROOM_FURNACE);
        playerob->eventDescribeEnvironment();
    }
    else {
        object *inv;
        object npc;
        int err;
        string basefile = ob->GetBaseFile();
        err = catch( npc = new(basefile) );
        if(!npc){
            npc = new(LIB_SENTIENT);
            npc->SetRace(ob->GetRace());
            npc->SetClass(ob->GetClass());
            npc->SetLevel(ob->GetLevel());
            npc->SetGender(ob->GetGender());
            npc->SetKeyName(lower_case((ob->GetOwner()|| ob->GetRace())));
            npc->SetShort((ob->GetLivingShort()|| "A "+ob->GetRace()));
            npc->SetLong((ob->GetLivingLong() || "A "+ob->GetRace()));
        }
        foreach(mixed key, mixed val in ob->GetSkills()){
            npc->SetSkill(key, val["level"], val["class"]);
        }
        foreach(mixed key, mixed val in ob->GetStats()){
            npc->SetStat(key, val["level"], val["class"]);
        }
        npc->eventMove(ROOM_POD);
        npc->ResetCurrency();
        if(sizeof(all_inventory(npc))){
            all_inventory(npc)->eventMove(ROOM_FURNACE);
        }
        inv = all_inventory(ob);
        if(sizeof(inv)) inv->eventMove(npc);
        inv = all_inventory(ob);
        if(sizeof(inv)) inv->eventMove(environment(this_player()));
        foreach(string element in ob->GetMissingLimbs()){
            npc->RemoveLimb(element);
        }
        if(ob){
            mapping oldequipped = ob->GetEquipped();
            string *oldkeys = keys(oldequipped);
            foreach(object thing in all_inventory(npc)){
                if(member_array(file_name(thing),oldkeys) != -1){
                    object oldob = oldequipped[file_name(thing)]["object"];
                    string *where = oldequipped[file_name(thing)]["where"];
                    if(objectp(oldob)){
                        if(oldob->CanEquip(npc, where)){
                            oldob->eventEquip(npc, where);
                        }
                    }
                }
            }
        }
        npc->SetPosition(POSITION_LYING);
        npc->eventMove(environment(this_player()));
        ob->eventMove(ROOM_FURNACE);
    }
    return 1;
}
