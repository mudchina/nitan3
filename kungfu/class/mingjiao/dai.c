// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// NPC dai.c 黛绮丝

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("黛绮丝",({"dai qisi","dai","qisi"}));
	set("title", HIG "明教" MAG "紫衫龙王" NOR);
        set("gender","女性");
        set("long",  "她是明教的四大护法之一的紫衫龙王。\n"+
                     "她身材苗条，是当年明教的第一美女，\n"+
                     "虽年事已高，仍不资色仍不减当年。\n");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 24);
        set("int", 40);
        set("con", 26);
        set("dex", 30);        
        set("max_qi", 2800);
        set("max_jing", 2200);
        set("eff_jingli", 2000);
        set("jiali", 10);
        set("combat_exp", 1100000);
        set("level", 30);

        set_skill("throwing",280); 
        set_skill("dodge",240);
        set_skill("force", 240);
        set_skill("duoming-jinhua",280);
        set_skill("literate", 230);
        set_skill("qingfu-shenfa", 240);
        set_skill("shenghuo-shengong", 240);
        set_skill("parry", 240);
        set_skill("claw", 240);
        set_skill("yingzhua-shou", 220);
        set_skill("martial-cognize", 200);   
                
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("throwing", "duoming-jinhua");
        map_skill("parry", "duoming-jinhua");
        map_skill("claw", "yingzhua-shou");
        
        prepare_skill("claw", "yingzhua-shou");
        
        create_family("明教", 36, "护法法王");
        set("master_ob",4);
	setup();
        
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
        carry_object("/d/mingjiao/obj/luopan");
        carry_object("/d/mingjiao/obj/jinhua")->wield();
}

void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 5000)
        {
                command("say 你行侠仗义的事做得还不够，还是请回吧。");
                return;
        }
                
        if (! fam || fam["family_name"] != "明教")
        {
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }
        
        /*
        if(ob->query("gender")!="女性"){
                command("say "+RANK_D->query_respect(ob)+"还是回去吧，老身只收女弟子。");
                return;
        }
        */

        if ((int)ob->query_skill("shenghuo-shengong", 1) < 100) 
        {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob) + "是否还应该在圣火神功上多下点功夫？");
                return;
        }
        
        if ((int)ob->query_int() < 28) 
        {
                command("say 想学我的金花暗器，必须能够眼观四方，耳听八方。");
                command("say 在身体悟性方面，"+RANK_D->query_respect(ob)+"是否还嫌差了点？");
                return;
        }
        command("say 嗯，看你还是个学武的料，老身我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", this_object()->query("title") + "属下教众");
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {

        case "天外飞花" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/duoming-jinhua/fei",
                           "name"    : "天外飞花",
                           "sk1"     : "duoming-jinhua",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        default:
                return 0;
        }
}
