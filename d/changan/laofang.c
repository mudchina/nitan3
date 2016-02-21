//Room: laofang.c

inherit ROOM;

void create ()
{
	set ("short", "牢房");
        set("long", @LONG
这是一间牢房，室内昏暗无光，只有借着一碗口大的小洞射进来的余光，才
使人视力模糊的依稀见物。西边角落里堆放着一些已经腐烂的稻草，室内并不暗
潮，甚至还有一张简陋的旧床，牢门是用一根根手臂粗的铁棍做成的，中间有许
多的空隙，室外的光线可以射进来。
LONG );
        set("exits", ([
        ]));

	setup();
}
