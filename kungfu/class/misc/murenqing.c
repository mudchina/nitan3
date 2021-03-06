// murenqing.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("穆人清", ({ "mu renqing", "mu", "renqing" }));
	set("title", HIY "拳剑无双" NOR);

	set("gender", "男性");
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("age", 56);

	set("str", 33);
	set("int", 36);
	set("con", 31);
	set("dex", 34);

	set("qi", 60000);
	set("max_qi", 60000);
	set("jing", 30000);
	set("max_jing", 30000);
	set("neili", 72000);
	set("max_neili", 72000);
	set("jiali", 150);

	set("combat_exp", 64000000);
	set("score", 10000000);

	set_skill("cuff", 2700);
	set_skill("force", 2700);
	set_skill("sword", 2800);
	set_skill("dodge", 2800);
	set_skill("parry", 2700);
	set_skill("strike", 2700);
	set_skill("zixia-shengong", 2700);
	set_skill("poyu-quan", 2700);
	set_skill("huashan-jianfa", 2800);
	set_skill("hunyuan-zhang", 2700);
        set_skill("feiyan-huixiang",2800);
	set_skill("literate", 1200);

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("strike", "hunyuan-zhang");

	create_family("华山派", 18, "弟子");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "strike.wuji" :),
		(: perform_action, "cuff.poshi" :),
		(: perform_action, "sword.jianzhang" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}
