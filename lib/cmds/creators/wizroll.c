#include <daemons.h>
#include <lib.h>

inherit LIB_COMMAND;

int cmd(string str){
    mixed *tmp, *tmp2 = ({});

    if(!str || !(tmp = roll(str))){
        write(this_object()->GetHelp());
        return 1;
    }
    foreach(mixed foo in tmp){
        tmp2 += ({ itoa(foo) });
    }
    write("各次投掷结果: "+implode(tmp2[1..]," "));
    write("总和: "+tmp[0]);
    return 1;

}

string GetHelp(){
    return "Syntax: wizroll <NUMBERdNUMBER>\n\n"
        "Simulates a roll of dice. For example, 'wizroll 2d6' simulates a "
        "roll of two six-sided dice. Dice are not limited to realistic "
        "topologies. One may roll a 99d1025.";
}
