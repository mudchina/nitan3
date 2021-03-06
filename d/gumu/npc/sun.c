#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

string ask_job();
string ask_ping();
string ask_jiedu();

void create()
{
        set_name("孙婆婆", ({ "sun popo", "sun", "popo" }));
        set("gender", "女性");
        set("age", 55);

        set("long", sort_msg("她是小龙儿的贴身奶妈。她长着一张生满鸡皮"
                "疙瘩的丑脸，正瞪眼瞧着你，她的笑容更是十分丑陋，但奇"
                "丑之中却含仁慈温柔之意，登时叫你心中感到一阵温暖。\n"));

        set("attitude", "friendly");

        set("qi", 1200);
        set("max_qi", 1200);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 80);
        set("combat_exp", 150000);
        set("score", 0);

        set_skill("force", 160);
        set_skill("yunv-xinfa", 160);
        set_skill("sword", 140);
        set_skill("yunv-jian", 160);
        set_skill("dodge", 160);
        set_skill("yunv-shenfa", 160);
        set_skill("parry", 140);
        set_skill("unarmed", 140);
        set_skill("meinv-quan", 140);
        set_skill("literate", 140);
        set_skill("qufeng", 90);
        set_skill("martial-cognize", 140);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "yunv-jian");
        map_skill("unarmed", "meinv-quan");

        prepare_skill("unarmed", "meinv-quan");

        create_family("古墓派", 2, "弟子");

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 60);
        set_temp("apply/unarmed_damage", 60);
        set_temp("apply/armor", 100);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform unarmed.you") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.mei" :),
        }) );

	set("inquiry", ([
		"job"  : (: ask_job :),
                "任务" : (: ask_job :),
		"青瓷瓶" : (: ask_ping :),
		"解毒" : (: ask_jiedu :),
        ]));
        
        set("env/wimpy", 50);

        set("coagents", ({
                ([ "startroom" : "/d/gumu/zhengting.c",
                   "id"        : "xiao longnv" ]),
        }));

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();

}

string ask_job()
{
	object ob2;
	object ob = this_player();
	object me = this_object();

        if (count_gt(ob->query("combat_exp"), 400000))
                 return "这位"+RANK_D->query_respect(ob)+"实战经验已经颇高，岂敢劳烦大架。\n";
                 
        if (ob->query("family/family_name") != "古墓派")
	        return "这位" + RANK_D->query_respect(ob) + "非我古墓派弟子，岂敢劳烦。\n";

        if (ob->query("scheming")) 
                return "现在禁止用 Scheme 做门派任务。\n"; 
                
        if (ob->query_temp("gm_xunfeng"))
        {
		command("hmm " + ob->query("id"));
		return "你还没完成任务，就又想要新的？\n";
	}

        if (present("feng xiang", environment(ob)))
                return "你还是先把你手里的蜂箱销毁了再来要任务！\n";
        /*
	if (time() < ob->query( "mp_job_time" ) +180)
	{
		tell_object( ob, "你先去歇息一下吧.\n" );
		return "\n";
	}
        */
	ob->set( "mp_job_time", time() );
	me->add_temp("job_pos", -1);

	command("nod");
	command("say 好，今天天气不错，"+RANK_D->query_respect(ob)+"把玉蜂带出去采些花蜜吧。");
	ob2 = new("/d/gumu/npc/obj/beehive");
	ob2->set("owner", ob);
	ob2->set("mi_lvl", 0);
	if (! ob->query_temp("bee_count"))
	{
		ob->set("bee_count", ob->query("bee_count") - 2);
		if (ob->query("bee_count") < 1) 
		        ob->set("bee_count", 1);
		ob->set_temp("bee_count", ob->query("bee_count"));
	}
	if (ob->query_temp("bee_count") > 5) 
	        ob->set_temp("bee_count", 5);
	ob2->set("bee_count",ob->query_temp("bee_count"));
	ob2->set_amount(ob->query_temp("bee_count"));
	ob2->move(ob);
	ob->set_temp("gm_xunfeng",1);
	ob->set("gm/job", 1);
	ob->set("gm/time", time());
	message_vision("$N给$n"+chinese_number(ob2->query_amount())
		+"个"+HIW"玉蜂箱。\n"NOR, me, ob);
	return "早去早回，小心麻雀！\n";
}

string ask_ping()
{
	object pl = this_player();
	object me = this_object();
	object *inv;	// 身上带的东西
	int i, j;
	object ping;

	if (pl->query("family/family_name") != "古墓派")
		return "青瓷瓶虽无奇，却深为我派弟子所爱。\n";

	inv = all_inventory(pl);
	j=0;
	for(i=0; i<sizeof(inv); i++)
		if( inv[i]->query("name") == CYN "青瓷瓶" NOR )
			j += 1;
	if (j > pl->query_temp("bee_count") + 4){
		command("hmm "+pl->query("id"));
		command("smile "+pl->query("id"));
        return ("要那么多青瓷瓶做什么？\n");
	}
	
	command("nod");
	ping = new("/d/gumu/npc/obj/qingci-ping");
	ping->set("liquid/remaining",0);
	ping->move(me);
	command("give ping to "+pl->query("id"));
	return ("这青瓷瓶又小又脆，别弄丢了！\n");
}

string ask_jiedu()
{
	object pl = this_player();
	object me = this_object();
	object ping, xiang;

	if ( pl->query("family/family_name") != "古墓派" ) {
		if ((int)pl->query_condition("yufeng_poison")) {
			command("laugh "+pl->query("id"));
			command("shrug");
			return ("恭喜你啦！玉蜂毒也没什么厉害的，只不过无药可解而已！\n");
		}
		else return 0;
	}

	if (present("qingci ping", pl))
		return ("你不是有解药吗？\n");

	if (!(int)pl->query_condition("yufeng_poison")) 
	        return ("你没中毒呀？");
	
	ping = new("/d/gumu/npc/obj/qingci-ping");
	ping->move(me);

	xiang = present("feng xiang", pl);
	if ( xiang && xiang->query("mi_lvl")>1) {
		message_vision("$N慢慢打开玉蜂箱的盖子。\n", me);
		message_vision("$N慢慢抽出一排装满玉蜂蜜的木板。\n", me);
		message_vision("$N慢慢刮下玉蜂蜜装入青瓷瓶。\n", me);
		message_vision("$N把玉蜂箱恢复原状。\n", me);

		ping->set("liquid/remaining",xiang->query("mi_lvl")/2 +1);
		xiang->set("mi_lvl",0);
	}
	else ping->set("liquid/remaining",1);

	command("give ping to "+pl->query("id"));
	return ("赶紧拿去用吧！");
}
