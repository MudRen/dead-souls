varargs mixed CanStop(object who, string what, mixed args){
    if(who != this_object()) return 0;
    if(what == "fishing"){
        int stop_err;
        object ob = environment(who);
        stop_err = ob->CanStop(this_player(), "fishing");
        return (stop_err || "你没有在钓鱼！");
    }
    if(what == "fighting"){
        mixed *enemies = this_object()->GetEnemies();
        //mixed *hostiles = this_object()->GetHostiles();
        mixed *hostiles = ({});
        if(!sizeof(enemies) && !sizeof(hostiles)){
            return "你没有在生任何人的气！";
        }
        return 1;
    }
    return 1;
}

varargs mixed eventStop(object who, string what, mixed args){
    if(who != this_object()) return 0;
    if(what == "fishing"){
        object ob = environment(who);
        return ob->eventStop(this_player(), "fishing");
    }
    if(what == "fighting"){
        mixed *enemies = this_object()->GetEnemies();
        mixed *hostiles = this_object()->GetHostiles();
        foreach(object enemy in enemies){
            if(!enemy) continue;
            write("你不再与"+enemy->GetShort()+"战斗了。");
            this_object()->RemoveEnemy(enemy);
        }
        //foreach(object hostile in hostiles){
        //if(!hostile) continue;
        // if(member_array(hostile, enemies) == -1)
        //  write("You are no longer hostile toward "+hostile->GetShort()+".");
        //   this_object()->RemoveEnemy(hostile);
        //}
        this_object()->AddNonTargets(enemies);
        //this_object()->AddNonTargets(hostiles);
        return "你已经停止了好斗行为。";
    }
    return 0;
}

