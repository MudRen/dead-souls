/* fishing pole designed by Descartes for use in rooms that are fishing
   compatible.  The pole is really nothing special except in that
   you can bait it with anything that returns an id of bait and also
   in that it has the following functions called by fishing rooms:
   query_pole_class() returns an integer, the higher the number, the
   better the pole is for fishing.
   query_bait() returns an integer which is the strength of the bait,
   the higher the number, the better the bait is for fishing
   pole class should range from 2 (a horrible pole) to 7 (an absolutely
   awesome pole)
   bait strength, which is found out by the pole by calling a function
   in items which return an id of true for bait, should be a
   number between 0 (items fish wont eat) to 4 (yummy fish food)
 */

#include <lib.h>
inherit LIB_ITEM;

int query_bait();
int query_pole_class();
int query_broken();
int break_pole();
void unbait();
int broken;
int bait;

void init() {
    add_action("bait_it","bait");
}

void create() {
    ::create();
    SetKeyName("stick");
    SetId( ({ "stick", "fishing pole", "hook", "string" }) );    SetValue( 20);
    SetMass( 28);

    broken = 0;
    bait = 0;
}

string GetLong(string str) {
    if(str == "hook") {
        if(!bait) return ("也许你可以用什么东西做鱼饵？\n");
        else return ("上面有鱼饵。\n");
    }
    else if(str == "string") return ("一根末端有钩子的线。\n");
    else {
        return ("一根末端系着线的竹竿。\n"
                "线的末端是一个钩子。多么原始的钓鱼工具！\n");
    }
}

string GetShort() {
    if(!broken) {
        if(!bait) return "一根竹竿";
        else return "一根竹竿（已上饵）";
    }
    else return "一根竹竿（断了）";
}

int query_pole_class() {
    return 2;
}

int query_bait() {
    return bait;
}

int bait_it(string str) {
    string pole, the_bait;
    if(!str) return 0;
    if((sscanf(str, "%s with %s", pole, the_bait)) !=2) return 0;
    if(pole != "stick" && pole != "hook") return 0;
    if(!present(the_bait,this_player())) {
        write("你没有任何"+the_bait+"来给鱼钩上饵！\n");
        return 1;
    }
    if(!(present(the_bait,this_player())->id("bait"))) {
        write("你不能用那个做鱼饵！\n");
        return 1;
    }
    if(!bait) {
        bait = (100-present(the_bait, this_player())->query_strength())/7;
        write("你用"+the_bait+"给鱼钩上了饵。\n");

        say(this_player()->query_cap_name()+"给鱼钩上了饵。\n");
        find_object(the_bait)->remove();
        return 1;
    }
    else {
        write("你的鱼钩上已经有鱼饵了！");
    }
    return 1;
}

void unbait() {
    bait = 0;
}

int query_broken(){
    return broken;} int break_pole() {    SetValue( 10);

        true();
        broken = 1;
    }

