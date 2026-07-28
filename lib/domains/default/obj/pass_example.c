/* Please note this info from options.h
 * REF_RESERVED_WORD: If this is defined then the word 'ref' can be
 *   used to pass arguments to functions by reference.  Example:
 *
 * void inc(int ref x) {
 *     x++;
 * }
 *
 * ... y = 1; inc(ref y); ...
 *
 * A side effect is that 'ref' cannot be a variable or function name.
 *
 * Note: ref must be used in *both* places; this is intentional.  It protects
 * against passing references to routines which don't intend to return values
 * through their arguments, and against forgetting to pass a reference
 * to a function which wants one (or accidentally having a variable modified!)
 */

#include <lib.h>

inherit LIB_ITEM;
mixed globalvar;

protected void create() {
    item::create();
    SetKeyName("object");
    SetId( ({ "example", "sample" }) );
    SetAdjectives( ({ "example","sample","pass by reference" }) );
    SetShort("一个 pass by reference 示例对象");
    SetLong("这个对象允许你测试按引用传递。当你：\n\n call example->StartPass(1)\n\n\t你可以看到不仅局部变量被改变了，全局变量也被改变了，\n\t尽管没有赋值操作将 globalvar 改为 localvar 的新值。\n\t这种按引用传递是通过使用 \"ref\" 关键字实现的。\n\t如果你需要按引用传递整数或字符串，请研究这里的做法来理解过程。");
    SetNoCondition(1);
    SetMass(50);
    SetBaseCost(1);
}
void init(){
    ::init();
}

mixed PassByRef(mixed ref arg){
    if(intp(arg)) arg++;
    else if(stringp(arg)) arg += "localvar";
    else if(mapp(arg)) arg[identify(this_object())] = this_object();
    else if(arrayp(arg) && sizeof(arg)){
        if(stringp(arg[0])) arg += ({ "localvar" });
        else if(intp(arg[0])) arg += ({ 1 });
        else if(objectp(arg[0])) arg += ({ this_object() });
    }
    return arg;
}

mixed StartPass(mixed localvar){
    globalvar = localvar;
    write("localvar: "+identify(localvar));
    write("globalvar: "+identify(globalvar));
    flush_messages();
    localvar = PassByRef(ref globalvar);
    write("localvar: "+identify(localvar));
    write("globalvar: "+identify(globalvar));
    return 1;
}
