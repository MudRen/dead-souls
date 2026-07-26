#include <lib.h>

varargs mixed CanRoll(object target, object where){
    return 1;
}

mixed direct_roll_obj(object target){
    if( environment(this_object()) != this_player() ){
        return "#你没有那个东西！";
    }
    return CanRoll(this_object());
}

mixed direct_roll_obj_on_obj(object target, object where, mixed wtf, mixed wtf2){
    if( environment(this_object()) != this_player() ){
        return "#你没有那个东西！";
    }
    if(!where && wtf2) where = present(wtf2, environment(this_player()));
    if(!where && wtf2) where = get_object(wtf2, this_player());
    if(!where && (wtf2 == "floor" || wtf2 == "ground")){
        return CanRoll(this_object());
    }
    if(!where || !inherits(LIB_SURFACE,where) ) return "#你无法在那里掷那个！";
    return CanRoll(this_object(), where);
}

mixed direct_roll_obj_on_str(object target, string where){
    if( environment(this_object()) != this_player() ){
        return "#你没有那个东西！";
    }
    return CanRoll(this_object());
}

mixed direct_roll_obj_here(object target){
    if( environment(this_object()) != this_player() ){
        return "#你没有那个东西！";
    }
    return CanRoll(this_object());
}

mixed indirect_roll_obj_on_obj(object target, object where){
    if( environment(this_object()) != environment(this_player()) ){
        return "#这里没有可以掷骰子的地方。";
    }
    if(!inherits(LIB_SURFACE,where) ){
        return "#你无法在那里掷那个！";
    }
    return CanRoll(this_object(), where);
}

mixed indirect_roll_obs_on_obj(mixed target, object where){
    return indirect_roll_obj_on_obj(target, where);
}

varargs mixed eventRoll(object ob){
    return 1;
}

varargs mixed eventResults(mixed args){
    say(this_player()->GetName()+"掷骰的结果是："+identify(args));
    write("你掷骰的结果是："+identify(args));
    return args;
}
