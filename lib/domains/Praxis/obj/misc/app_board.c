#include <lib.h>

inherit LIB_BOARD;

void create() {
    ::create();
    SetProperty("no steal",1);
    SetKeyName("board");
    SetId( ({"board","approval board"}) );
    set_board_id("approval");
    SetShort("审批布告板");
    SetLong("审批团队的帖子和笔记。\n");
}
