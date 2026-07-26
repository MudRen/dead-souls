#include <lib.h>

inherit LIB_VERB;

mixed can_shoot_obj_with_obj(mixed target,mixed shooter);
mixed can_shoot_obj_at_obj(mixed shooter,mixed target);
varargs mixed do_shoot_obj_at_obj(mixed args...);
varargs mixed do_shoot_obj_with_obj(mixed args...);

protected void create() {
    verb::create();
    SetVerb("shoot");
    SetRules("OBJ at OBJ", "OBJ with OBJ",
            "OBJ WRD", "OBJ WRD at WRD");
    SetSynonyms("fire", "gat", "gank");
    SetErrorMessage("射击什么？");
    SetHelp("语法：shoot <武器> at <敌人>\n\n"
            "射击一个目标。\n\n");
}

varargs mixed eventShoot(mixed device, mixed target, string dir, string whom){
    mixed attackable;
    object tmpob, who = this_player();

    if(!device || !objectp(device) || target == device ){
        write("你无法用那个射击这个。");
        return 0;
    }
    if(device->MustCarry() && environment(device) != who) {
        write("你没有持有武器。");
        return 1;
    }
    if(device->MustWield() && device->GetWorn() == 0 && !creatorp(who)) {
        write("你没有装备武器。");
        return 1;
    }
    if((!target || !objectp(target)) && !dir){
        write("那似乎不是有效目标。");
        return 0;
    }
    if(target && !present(target,environment(who)) && 
            !present(target,environment(device))){
        write("那个目标不在这里。");
        return 1;
    }

#if 1
    if(living(target) || target->isDummy()){
        attackable = target->GetAttackable();
        if(!attackable || !intp(attackable) || attackable != 1){
            write("你无法射击"+target->GetShort()+"。");
            return 1;
        }
    }
#endif
    return device->eventShoot(who, target, dir, whom);
}

mixed can_shoot_liv_with_obj(mixed target,mixed shooter){
    return can_shoot_obj_with_obj(target, shooter);
}

mixed can_shoot_obj_at_liv(mixed shooter,mixed target){
    return can_shoot_obj_at_obj(shooter, target);
}

mixed can_shoot_obj_with_obj(mixed target,mixed shooter) {
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed can_shoot_obj_at_obj(mixed shooter,mixed target) {
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed can_shoot_obj_wrd(mixed shooter,mixed dir) {
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed can_shoot_obj_wrd_at_wrd(mixed shooter, mixed dir, mixed whom) {
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

varargs mixed do_shoot_obj_at_liv(object what, object whom) {
    return do_shoot_obj_at_obj(what, whom);
}

varargs mixed do_shoot_liv_with_obj(object whom, object what) {
    return do_shoot_obj_at_obj(what, whom);
}

varargs mixed do_shoot_obj_at_obj(object what, object whom) {
    return eventShoot(what, whom);
}

varargs mixed do_shoot_obj_with_obj(object whom, object what) {
    return eventShoot(what, whom);
}

varargs mixed do_shoot_obj_wrd(object what, string dir) {
    return eventShoot(what, 0, dir);
}

varargs mixed do_shoot_obj_wrd_at_wrd(object what, string dir, string whom) {
    return eventShoot(what, 0, dir, whom);
}

