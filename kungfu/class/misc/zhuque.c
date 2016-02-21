// nanhai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIR "朱雀" NOR, ({ "fire phoenix", "phoenix", "fenghuang" }) );
        set("title", HIR "凤族" NOR);
        set("gender", "女性");
        set("age", 20);
        set("long", @LONG
这是一只巨大的火凤凰，浑身燃烧着熊熊的烈火，不时发出一两声撕心裂肺的怪叫。
LONG );
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 220000);
        set("neili", 220000);
        set("max_jing", 180000);
        set("jing", 180000);
        set("max_qi", 100000);
        set("qi", 100000);
        set("jingli", 120000);
        set("max_jingli", 120000);

        set("str", 60);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set_skill("unarmed", 1000);
        set_skill("sword", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);

        set("jiali", 400);

        set_temp("apply/attack", 800);
        set_temp("apply/unarmed_damage", 600);
        set_temp("apply/armor", 300);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIR "$N一声长嘶，浑身火焰四射，"
                       "令人心胆聚裂。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if (! is_killing(ob->query("id")))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N一声长嘶，扑了上来。\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 160 + random(170), me);
        me->set("neili", me->query("max_neili"));
        return HIR "$N" HIR "周围火焰爆涨，电光四射，登时令$n"
               HIR "痛苦不堪，难以忍受。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        object ob;
        string str;
        string* prize = ({
             "/clone/fam/etc/zhuquejiao",
             "/clone/fam/etc/zhuquejin",
             "/clone/fam/etc/yumao",
        });

        // 凤凰重生
        if (! this_object()->query("is_die"))
        {
            message_sort(HIR "\n$N" HIR "一声长嘶，地动山摇，猛然间，周身火焰冲天，$N"
                         HIR "腾空而起，在半空中盘旋着，随即又回到了原地。\n" NOR, this_object());

            this_object()->start_busy(2 + random(5));

            CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + name() + HIM "冲出地狱，获得了重生。\n" NOR);

            set("max_neili", 220000);
            set("neili", 220000);
            set("max_jing", 180000);
            set("jing", 180000);
            set("eff_jing", 180000);
            set("max_qi", 340000);
            set("qi", 340000);
            set("eff_qi", 340000);
            set("jingli", 120000);
            set("max_jingli", 120000);

            set("str", 100);
            set("int", 100);
            set("con", 100);
            set("dex", 200);

            set_skill("unarmed", 1800);
            set_skill("sword", 1800);
            set_skill("parry", 1800);
            set_skill("dodge", 1800);
            set_skill("force", 1800);
            
            add("is_die", 1);
            return ;
        }

        str = prize[random(sizeof(prize))];
        ob = new(str);
        command("chat 啊呀！人间居然有人能打败我，待我回到火焰山再修炼千年再说！");
        message_sort(HIR "$N" HIR "身子一扭，钻入地心，"
                     "只听叮玲玲的一声，从$N" HIR "身上掉下了一" +
                     ob->query("unit") + ob->name() +
                     HIR "。\n" NOR, this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 2400)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + name() + HIM "觉得人间气候恶劣，水土不服，终于又回到了火焰山。" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}

