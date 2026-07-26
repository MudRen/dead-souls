/*    /domains/Ylsrim/npc/priest.c
 *    From the Dead Souls Mud Library
 *    An example of a religious class leader
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>

inherit LIB_LEADER;

protected void create() {
    leader::create();
    SetKeyName("ixtala");
    SetId("ixtala", "priest");
    SetShort("伊克斯塔拉，牧师长");
    SetLong("伊克斯塔拉为牧师职业举行入会仪式，也引导迷途者皈依达林教的真理。"
            "要了解更多关于成为牧师的信息，请让她 \"describe priests\"。"
            "如果你选择成为牧师，请让她 \"join priests\"。"
            "当然，你也可以让她 \"convert me\" 来皈依。");
    SetLevel(45);
    SetRace("klingon");
    SetClass("cleric");
    SetGender("female");
    SetMorality(400);
    SetReligion("Dalin", "Dalite");
    SetProperty("no bump", 1);
    if( clonep() ) {
        AddChannel("priest");
    }
}
