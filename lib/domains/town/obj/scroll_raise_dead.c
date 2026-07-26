#include <lib.h>
#include <position.h>
#include ROOMS_H
#include <vendor_types.h>
inherit LIB_ITEM;

varargs mixed eventRead(object reader, mixed str){
    object ob, playerob;
    int corpse;
    object *inv;
    object npc;
    int err;
    string basefile;
    string lang = this_object()->GetLanguage();
    object zombie;
    catch(zombie = new("/shadows/zombie"));
    if(!str || !objectp(str) || !zombie){
        return ::eventRead(reader);
    } 
    if(reader->GetLanguageLevel(lang) < 100){
        return ::eventRead(reader);
    }
    ob = str;
    if(ob->isCorpse()) corpse = 1;

    if(living(ob)) {
        write("你不能复活活着的人。");
        return 1;
    }

    if(base_name(ob) != LIB_CORPSE){
        write("你只能复活肉体制成的尸体。");
        return 1;
    }

    if(environment(ob) != environment(this_player())) {
        write(capitalize(ob->GetKeyName())+" isn't here.");
        return 1;
    }

    tell_player(this_player(),"你念诵卷轴，随着雷鸣般的咆哮，"+ob->GetCapName()+"复活了！");
    tell_room(environment(this_player()),this_player()->GetCapName()+"对着"+ob->GetCapName()+"念诵了"
            +possessive(this_player())+"卷轴，伴随着雷鸣般的咆哮，"
            +nominative(ob)+"复活了！",
            ({ob, this_player()}) );

    basefile = ob->GetBaseFile();
    if(file_exists(basefile)){
        err = catch( npc = new(basefile) );
    }
    if(!npc){
        npc = new(LIB_SENTIENT);
        npc->SetShort(ob->GetRace()+"僵尸");
        npc->SetLong(ob->GetRace()+"僵尸");
    }

    npc->SetRace(ob->GetRace());
    npc->SetClass(ob->GetClass());
    npc->SetLevel(ob->GetLevel());
    npc->SetGender(ob->GetGender());
    npc->SetId( ({ ob->GetGender(), ob->GetRace(),
                ob->GetClass(), "zombie" }) );
    npc->SetAdjectives( ({ ob->GetGender(), ob->GetRace(),
                ob->GetClass(), "zombie", "undead" }) );
    npc->SetUndead(1);
    npc->SetKeyName(lower_case((ob->GetOwner()|| ob->GetRace())));

    foreach(mixed key, mixed val in ob->GetSkills()){
        npc->SetSkill(key, val["level"], val["class"]);
    }
    foreach(mixed key, mixed val in ob->GetStats()){
        npc->SetStat(key, val["level"], val["class"]);
    }
    npc->eventMove(ROOM_POD);
    npc->SetProperty("basefile", basefile);
    npc->init();
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
    npc->DisableActions(1);
    npc->SetUndead(1);
    npc->SetEncounter(0);
    npc->eventQuell();
    npc->SetUndeadType("zombie");
    ob->eventMove(ROOM_FURNACE);
    tell_room(environment(this_player()),"卷轴化为灰烬。");
    zombie->eventShadow(npc);
    this_object()->eventMove(ROOM_FURNACE);
    return 1;
}

void create(){
    string message = "这张可怕的卷轴可以复活一个生物的尸体。"+
        "复活的僵尸几乎没有原来生物的个性……只有身体属性，而且会"+
        "慢慢腐烂并最终崩解。僵尸会服从任何用它生前理解的语言说出的命令。"+
        "如果你确定要踏入死灵术的黑暗世界，那么你可以：read scroll at person";
    ::create();
    SetKeyName("scroll");
    SetId(({"scroll of raise dead","scroll of necromancy"}));
    SetAdjectives(({"terrible","raise dead","magic","necromancy","dark"}));
    SetShort("一卷暗色卷轴");
    SetLong("这是一卷写有文字的暗色卷轴。");
    SetMass(1);
    SetDollarCost(500);
    SetVendorType(VT_TREASURE);
    SetReads( ([ "default" : message,
                ({ "words", "words written" }) : message,
                ]) );
    SetLanguage("English");
}

void init(){
    ::init();
}
