// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// peng.c 彭有敬

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include "fight.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("彭有敬", ({ "peng youjing", "peng", "youjing" }));
        set("long", @LONG
彭有敬是丐帮中净衣派的首领，衣着干净华丽
不象叫化子。他脸上挂着慈祥的笑容，一双眼
睛有摄人心魄的力量。
LONG);
        set("nickname", WHT "掌钵龙头" NOR);
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4300);
        set("max_neili", 4300);
        set("jiali", 180);
        set("combat_exp", 2200000);
        set("level", 20);
        set("score", 300000);
        set("shen_type", -1);
        
        set_skill("force", 220);
        set_skill("huntian-qigong", 220);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 220);
        set_skill("changquan", 220);        
        set_skill("hand", 220);             
        set_skill("shexing-diaoshou", 220);  
        set_skill("strike", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("parry", 220);
        set_skill("staff", 240);
        set_skill("fengmo-zhang", 220);
        set_skill("blade", 220);          
        set_skill("liuhe-dao", 220);      
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "fengmo-zhang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "changquan");

        prepare_skill("hand", "shexing-diaoshou");

        // set("no_teach/mihun-dafa",  "你弄错了吧？这种下三滥的东西我怎么会。");

        create_family("丐帮", 18, "长老");

        set("coagents", ({
                ([ "startroom" : "/d/city/gbxiaowu",
                   "id"        : "hong qigong" ]),
        }));

        set("inquiry", ([
                "群魔乱舞" : (: ask_skill1 :),
                "慑心术"   : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
	setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        string title = ob->query("title");
        int lvl = ob->query("family/beggarlvl");

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("level") < 5)
        {
                command("say 你的江湖经验不够，还是先向各位长老学习吧。");
                return;
        }

        if (ob->query("family/beggarlvl") < 4)
        {
                command("say 你在本帮的地位太低，还是先向其他师父学习吧。");
                return;
        }

        if (ob->query_skill("force") < 90)
        {
                command("say 你的内功火候还不够，还是先向其他师父学习吧。");
                return;
        }
        command("grin");
        command("say 那你以后就跟着我吧。");
        command("recruit " + ob->query("id"));

        if (ob->query("class") != "beggar")
                ob->set("class", "beggar");

        if (lvl > 0)
        {
                ob->set("family/beggarlvl", lvl);
                ob->set("title", title);
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if (me->query("can_perform/fengmo-zhang/luan"))
                return "这招我不是已经教会你了吗？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("fengmo-zhang", 1) < 1)
                return "你连疯魔杖法都没学，何谈绝招可言？";

        if (me->query("family/gongji") < 400)
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if (me->query_skill("fengmo-zhang", 1) < 120)
                return "你的疯魔杖法火候还不够，还是下去练高点再来吧。";

        if (me->query_skill("force") < 150)
                return "你现在的内功修为不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "点了点头，对$N" HIY "说道：“给"
                     "我看清楚了。”突然陡听$n" HIY "一声暴喝，手中铁"
                     "杖一阵乱舞，竟似毫无章理，挥舞出数道杖影，气势"
                     "澎湃，力不可挡。正是疯魔杖法的精要所在。\n\n" NOR,
                     me, this_object()); 

        command("say 明白了么。");
        tell_object(me, HIC "你学会了「群魔乱舞」。\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("fengmo-zhang"))
                me->improve_skill("fengmo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/fengmo-zhang/luan", 1);
        me->add("family/gongji", -400);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if (me->query("can_exert/huntian-qigong/shexin"))
                return "这招我不是已经教会你了吗？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query("family/gongji") < 400)
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if (me->query_skill("huntian-qigong", 1) < 120)
                return "你的混天气功火候还不够，还是下去练高点再来吧。";

        if (me->query_skill("force") < 150)
                return "你现在的内功修为不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "点了点头，对$N" HIY "鬼祟的说道：“给"
                     "我听清楚了”。然后开始小声地对$N讲解摄心术的精要所在。\n\n" NOR,
                     me, this_object()); 

        command("say 明白了么。");
        tell_object(me, HIC "你学会了「摄心术」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("huntian-qigong"))
                me->improve_skill("huntian-qigong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_exert/huntian-qigong/shexin", 1);
        me->add("family/gongji", -400);

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "连环诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuhe-dao/lian",
                           "name"    : "连环诀",
                           "sk1"     : "liuhe-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 4000, ]));
                break;

        case "混天神罡" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_exert/huntian-qigong/shengang",
                           "name"    : "混天神罡",
                           "sk1"     : "huntian-qigong",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 1000,
                           "shen"    : 60000, ]));
                break;
                                
        default:
                return 0;
        }
}                
