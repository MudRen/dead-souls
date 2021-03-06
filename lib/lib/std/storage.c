#include <lib.h>

inherit LIB_BASE_STORAGE;
inherit LIB_ITEM;

nosave private mixed my_save = ({});

void create(){
    //parse_init();
    my_save = ({});
    item::create();
    base_storage::create();
}

int GetRadiantLight(int ambient){
    return item::GetRadiantLight(ambient) + base_storage::GetRadiantLight(ambient);
}

string* GetSave(){
    string *i_save;
    i_save = item::GetSave();
    my_save += i_save;
    my_save += ({ "Closed","CanClose", "CanLock", "RecurseDepth" , "MaxRecurseDepth" });
    my_save = distinct_array(my_save);
    return my_save;
}

protected mixed* AddSave(mixed* vars){
    my_save = distinct_array(my_save + vars);
    return item::AddSave(my_save);
}

int SetSaveRecurse(int x){
    return item::SetSaveRecurse(x);
}

