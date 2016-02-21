// Room: /d/wizard/wizard_room.c

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "巫师休息室");
	set("long", @LONG
这里就是泥潭巫师的休息所在，刚粉刷过的四周墙壁上光
秃秃的什么都没有，屋子的正中央放着一张楠木桌，上面摆着
一本巫师留言簿(board)。地上则是零零碎碎的一些BUG，到处
乱爬。
LONG );

	set("exits", ([
               "down" : __DIR__"guest_room",
               "up" : __DIR__"meeting_room",
	]));
        set("valid_startroom", 1);
	set("no_fight", "1");
	setup();

	call_other("/clone/board/wiz_b", "???");
        replace_program(ROOM);
}


