#include <lib.h>
#include <position.h>
#include ROOMS_H
#include <vendor_types.h>
inherit LIB_ITEM;

varargs mixed eventRead(object reader, mixed str){
    object ob, playerob;
    int corpse;
    string lang = this_object()->GetLanguage();
    if(!str || !objectp(str)){
        return ::eventRead(reader);
    } 
    if(reader->GetLanguageLevel(lang) < 100){
        return ::eventRead(reader);
    }
    ob = str;
    if(ob->isCorpse()) corpse = 1;

    if(interactive(ob)) playerob = ob;

    if( ob->isPlayer() ) playerob = ob->GetPlayerob();

    if( ob->isPlayer() && !playerob ){
        write("你不能复活一个不在线的玩家。");
        return 1;

    }
    if((playerob && !playerob->GetGhost()) || living(ob)) {
        write("你不能复活活着的人。");
        return 1;
    }

    if(base_name(ob) != LIB_CORPSE){
        write("你只能复活肉体制成的生物。");
        return 1;
    }

    if(environment(ob) != environment(this_player())) {
        write(capitalize(ob->GetKeyName())+" isn't here.");
        return 1;
    }

    tell_player(this_player(),"你念诵卷轴，随着一道闪光，"+ob->GetCapName()+"复活了！");
    tell_player(ob,capitalize(this_player()->GetKeyName())+"对着你念诵了"
            +possessive(this_player())+"卷轴，你从死亡中回来了！");
    tell_room(environment(this_player()),this_player()->GetCapName()+"对着"+ob->GetCapName()+"念诵了"
            +possessive(this_player())+"卷轴，"
            +nominative(ob)+"复活了！",
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
    tell_room(environment(this_player()),"卷轴化为灰烬。");
    this_object()->eventMove(ROOM_FURNACE);
    return 1;
}

void create(){
    string message="要让某人复活，恢复到死亡前的状态，且不会损失经验或能力，"+
        "那么去找到他们的尸体，然后：read scroll at person";
    ::create();
    SetKeyName("scroll");
    SetId(({"scroll of resurrection"}));
    SetAdjectives(({"resurrection","magic"}));
    SetShort("一卷卷轴");
    SetLong("这是一卷写有文字的卷轴。");
    SetMass(1);
    SetDollarCost(1000);
    SetVendorType(VT_TREASURE);
    SetReads( ([ "default" : message,
                ({ "words", "words written" }) : message,
                ]) );
    SetLanguage("Edhellen");
}

void init(){
    ::init();
}
