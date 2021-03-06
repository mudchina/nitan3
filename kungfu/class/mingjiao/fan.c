// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

string ask_me();

void create()
{
        set_name("范遥",({"fan yao","fan","yao"}));
	set("title", HIG "明教" HIR "逍遥二仙" NOR);
        set("long", "他就是明教的光明右使，和杨逍合称逍遥二仙的范遥。\n"+
                    "他身着一身白衫，虽然已是中年，但看上去还十分英俊潇洒。\n");
        set("age", 56);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 26);
        set("per", 28);
        set("int", 29);
        set("con", 27);
        set("dex", 30);
        set("max_qi", 3500);
        set("max_jing", 2200);
        set("eff_jingli", 2500);
        set("jiali", 80);
        set("combat_exp", 1500000); 
        set("level", 40);
        set("heiyu", 1);

        set_skill("sword", 270); 
        set_skill("dodge", 270);
        set_skill("force", 270);
        set_skill("blade", 270);
        set_skill("literate", 250);
        set_skill("claw", 270);
        set_skill("strike", 270);
        set_skill("hanbing-mianzhang", 270);
        set_skill("yingzhua-shou", 270);
        set_skill("qingfu-shenfa", 270);
        set_skill("shenghuo-shengong", 270);
        set_skill("lieyan-dao", 270);
        set_skill("liehuo-jian", 270);
        set_skill("parry", 270);
        set_skill("martial-cognize", 200);   
        
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("blade", "lieyan-dao");
        map_skill("claw", "yingzhua-shou");
        map_skill("strike", "hanbing-mianzhang");
        
        prepare_skill("strike", "hanbing-mianzhang");
        prepare_skill("claw", "yingzhua-shou");

        create_family("明教", 35, "光明右使");

        set("inquiry", ([
                 "黑玉断续膏" : (: ask_me :),
        ]));
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: command("perform strike.jue") :),
                (: command("perform strike.xi") :),                
                (: command("perform claw.xue") :),                
	}));
        set("master_ob",4);
	setup();
        
        if (random(10) > 5)
                carry_object("/clone/weapon/blade")->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 10000)
        {
                command("say 你行侠仗义的事做得还不够，还是请回吧。");
                return;
        }
                        
        if (! fam || fam["family_name"] != "明教")
        {
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }

        if ((int)ob->query_skill("shenghuo-shengong", 1) < 120) 
        {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在圣火神功上多下点功夫？");
                return;
        }
        if ((int)ob->query_int() < 30) 
        {
                command("say 逍遥二仙的武功博而杂，要学会这些武功，非得有极高的悟性。");
                command("say 在悟性方面，"+RANK_D->query_respect(ob)+"是否还不够？");
                return;
        }
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", this_object()->query("title")+"座下弟子");
}

string ask_me()
{
        mapping fam; 
        object ob, *clone;
        int i, j;
        
        if (! (fam = this_player()->query("family")) || fam["family_name"] != "明教")
                return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
                
        if (this_player()->query_skill("shenghuo-shengong", 1) < 50)
                return "你在明教的时日尚短，这黑玉断续膏你还不够资格使用。\n";
                
        if (this_player()->query_temp("marks/膏1"))
                return "你不是刚拿了黑玉断续膏了吗，怎么还要？";
                
        if (present("heiyu duanxugao", this_player()))
                return "你身上不是带着黑玉断续膏吗，怎么还要？";
                
        if ((int)this_player()->query("eff_qi") == (int)this_player()->query("max_qi"))
                return "你现在不需要用黑玉断续膏。";
                
        if (this_object()->query("heiyu") < 1)       
                return "你来晚了，黑玉断续膏已给全部发出去了。"; 
        
        ob = new("/d/mingjiao/obj/heiyu"); 
        ob->move(this_player());
        this_player()->set_temp("marks/膏1", 1);
        this_object()->add("heiyu", -1);
        
        return "好吧，这盒黑玉断续膏你就拿去用吧。";
}

void reset()
{
        set("heiyu", 1);
}
