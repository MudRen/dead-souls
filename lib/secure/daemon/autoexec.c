#include <lib.h>
#include <save.h>
#include <daemons.h>
#include <commands.h>

inherit LIB_DAEMON;

int t, BootScore, PerformanceScore, hasrun = 0;

string RateScore(int i){
    string ret;
    if(!i) ret = "无评分。";
    else if(i < 51) ret = "极好。";
    else if(i < 101) ret = "优秀。";
    else if(i < 201) ret = "很好。";
    else if(i < 301) ret = "良好。";
    else if(i < 401) ret = "一般。";
    else if(i < 501) ret = "较差。";
    else if(i < 601) ret = "很差。";
    else if(i < 701) ret = "糟糕。";
    else ret = "极差。";
    return ret;
}

protected void eventRun() {
    string ret = "";
    mapping before, after;
    string *noobnames = ({ "Dead_Souls_"+DEBUGGER, "DeadSoulsNew",
            "DeadSoulsWin" });
    debug_message("\n正在运行自动执行，请稍候...");
    BootScore = MASTER_D->GetBootScore();
#ifdef __HAS_RUSAGE__
    before = rusage();
#endif
    t = time(); 
    load_object(CMD_UPDATE)->cmd("-r /lib/creator");
    if(RESET_INTERMUD){
        rm(save_file(SAVE_INTERMUD));
        update(INTERMUD_D);
    }
    if(member_array(mud_name(),noobnames) == -1){
        mixed foo;
        foo = IMC2_D->UnSetAutoDisabled(1);
    }

    //Put your start-on-boot stuff below

    catch( load_object("/secure/cmds/creators/dsversion")->cmd());
    catch( reload("/domains/default/room/stargate_lab.c",0,1));
    catch( reload("/domains/town/virtual/space/1,1,1",0,1));
    catch( reload("/domains/town/virtual/bottom/33,100000",0,1));
    catch( reload("/domains/Praxis/square.c",0,1));
    catch( reload("/domains/Ylsrim/room/tower",0,1));
    catch( reload("/domains/campus/room/slab",0,1));

    //Put your start-on-boot stuff above

#ifdef __HAS_RUSAGE__
    after = rusage();
#endif
    t = time() - t;
#ifdef __HAS_RUSAGE__
    if(sizeof(before) && sizeof(after)){
        t = after["utime"] - before["utime"];
        ret = "自动执行守护进程运行完成。("+t+"毫秒)\n";
    }
#else 
    ret =  "自动执行守护进程运行完成。\n";
#endif
    debug_message(ret);
    call_out("perfreport", 1);
}

void perfreport(){
    string ret = "";
    float secs;
    if(!PerformanceScore) PerformanceScore = MASTER_D->GetPerformanceScore();
    if(!BootScore) BootScore = MASTER_D->GetBootScore();
    if(BootScore){
        secs = ((BootScore + t ) * 0.001);
        ret += "启动CPU耗时: " + sprintf("%.2f",secs)+ " 秒。";
    }
    if(PerformanceScore){
        ret += " (性能评分: " + (RateScore(PerformanceScore))+")\n";
    }
    debug_message(ret);
}

protected void create() {
    daemon::create();
    PerformanceScore = MASTER_D->GetPerformanceScore();
    if(hasrun){
        return;
    }
    call_out((: eventRun :), 1);
    hasrun = 1;
}

