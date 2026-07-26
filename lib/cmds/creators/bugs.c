#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd() {
    int bugs = BUGS_D->BugCheck();
    write("未解决的错误报告: "+bugs);
    return 1;
}

string GetHelp() {
    return ("Syntax: bugs\n\n"
            "Returns the number of unresolved bug reports in the bug "
            "tracking system.\n"
            "See also: bug");
}
