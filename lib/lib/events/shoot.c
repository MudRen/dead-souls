nosave int mustcarry = 1,mustwield = 1;

int MustCarry(int i){
    if(i) mustcarry = i;
    if(mustcarry) return mustcarry;
    else return 0;
}

int MustWield(int i){
    if(i) mustwield = i;
    if(mustwield) return mustwield;
    else return 0;
}

varargs mixed eventShoot(object who, mixed target, string dir, string whom){
    string tmp;
    if(target && objectp(target)){
        tmp=target->GetName();
        target = tmp;
    }
    if(target) write("你用武器向"+target+"射击。");
    return 1;
}

mixed CanShoot(object shooter, mixed target){
    object env = environment(this_player());
    if(this_object() == shooter && mustcarry > 0 && environment(this_object()) != this_player()){
        return "#你没有拿着"+remove_article(shooter->GetShort())+"。";
    } 
    if(this_object() == shooter && mustwield > 0 && this_object()->GetWorn() == 0 && !creatorp(this_player())){
        return "#你没有装备"+remove_article(shooter->GetShort())+"。";
    }
    if(env && env->GetProperty("no attack")){
        return "一股神秘的力量阻止了你的恶意。";
    }
    return 1;
}

varargs mixed direct_shoot_obj_at_obj(mixed args...){
    mixed ret;
    ret = CanShoot(args[0],args[1]);
    return CanShoot(args[0],args[1]);
}

varargs mixed direct_shoot_obj_with_obj(mixed args...){
    return 1;
}

varargs mixed indirect_shoot_obj_with_obj(mixed args...){
    mixed ret;
    ret = CanShoot(args[1],args[0]);
    return CanShoot(args[1],args[0]);
}

varargs mixed indirect_shoot_obj_at_obj(mixed args...){
    return 1;
}

varargs mixed direct_shoot_obj_at_liv(mixed args...){
    return direct_shoot_obj_at_obj(args...);
}

varargs mixed direct_shoot_liv_with_obj(mixed args...){
    return direct_shoot_obj_with_obj(args...);
}

varargs mixed indirect_shoot_liv_with_obj(mixed args...){
    return indirect_shoot_obj_with_obj(args...);
}

varargs mixed indirect_shoot_obj_at_liv(mixed args...){
    return indirect_shoot_obj_at_obj(args...);
}

varargs mixed direct_shoot_obj_wrd(mixed args...){
    return direct_shoot_obj_at_obj(args...);
}

varargs mixed direct_shoot_obj_wrd_at_wrd(mixed args...){
    return direct_shoot_obj_at_obj(args...);
}

