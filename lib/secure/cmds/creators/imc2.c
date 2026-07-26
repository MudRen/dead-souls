#include <daemons.h>

int cmd(string str){
    if(!(IMC2_D->command(str))){
        write("IMC2守护进程当前不可用。");
    }
    return 1;
}
string GetHelp(){ return "/secure/daemon/imc2.c"->main_help(); }
