//fushe.c

inherit SNAKE;
#include <ansi.h>

void create()
{
	set_name("腹蛇", ({ "fu she", "she", "fu" }) );
	set("race", "蛇类");
        set("age", 1 + random(9));
	set("long", "只见它全身血红，头呈三角，长蛇吞吐，嗤嗤做响。\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 20,
                "maximum": 20,
                "supply" : 1,
        ]));

	set("combat_exp", 50000 + random(50000));

	set_temp("apply/attack", 20+random(10));
	set_temp("apply/damage", 10+random(10));
	set_temp("apply/armor",  15+random(10));
	set_temp("apply/defence",50+random(50));
	setup();
}

void die()
{
	object ob;
	message_vision("$N倒在地上，死了！\n", this_object());
	ob = new("/clone/misc/shedan");
	ob->move(environment(this_object()));
	::die();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="fu she" && arg!="fu") return 0;
	if (me->query("family/family_name") != "欧阳世家") 
		return notify_fail("你不能化蛇为杖。\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N左手按住蝮蛇的头，右手轻抚其七寸，口中念念有词，片刻间将蛇化为一根蛇杖。\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}
