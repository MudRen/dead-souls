/*    /verbs/players/marry.c
 *    from the Dead Souls  Object Library
 *    marry
 *    marry LIV to LIV
 *    created by Descartes of Borg 951210
 */

#include <lib.h>
#include <objects.h>
#include "include/marry.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("marry");
    SetRules("LIV to LIV");
    SetErrorMessage("让谁和谁结婚？");
    SetHelp("Syntax: marry <PLAYER> to <PLAYER>\n\n"
            "Allows people of proper divine or legal authority to join two "
            "souls in marriage. In order to marry people, you must be in an "
            "appropriate location for it.\n"
            "See also: divorce");
}

mixed can_marry_liv_to_liv() {
    if( this_player()->GetSkillLevel("faith") < 5 ){
        return "你没有足够的信仰来结合两个人。";
    }
    return 1;
}

mixed do_marry_liv_to_liv(object spouse1, object spouse2) {
    mixed tmp;
    if( this_player() == spouse1 || this_player() == spouse2 )
        return "你不能为自己主持婚礼。";
    tmp = environment(this_player())->CanMarry(this_player(),
            spouse1, spouse2);
    if( !tmp ) {
        this_player()->eventPrint("这个地方对你来说不够神圣。");
        return 1;
    }
    else if( stringp(tmp) ) {
        this_player()->eventPrint(tmp);
        return 1;
    }
    tmp = environment(this_player())->eventMarry(this_player(),
            spouse1, spouse2);
    if( tmp == 1 ) {
        object ring;
        ring = new(OBJ_WED_RING);
        ring->SetSpouse(spouse2->GetCapName());
        ring->eventMove(spouse1);
        ring = new(OBJ_WED_RING);
        ring->SetSpouse(spouse1->GetCapName());
        ring->eventMove(spouse2);
    }
}
