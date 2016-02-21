// xiezi.c

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("Ы��", ({ "scorpion" }));
        set("long", "һֻЫ������������ض����㡣\n");

        set("race", "����");
        set("subrace", "����");
        set("age", 3);
        set("attitude", "peaceful");

        set("max_ging", 80);
        set("max_qi", 80);
        set("str", 10);
        set("con", 50);

        set("limbs", ({ "��","����", "����", "β��"}));
        set("verbs", ({ "bite" }) );

        set_temp("apply/attack", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        set("combat_exp", 1000);
        setup();
}

void init()
{
        object me,ob;
        ::init();
        if (interactive(me = this_player()))
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, me);
        }
}

int hit_ob(object me, object ob, int damage)
{
        if (random(damage) > (int)ob->query_temp("apply/armor") &&
            ob->affect_by("poison", ([ "level" : random(10) + 10,
                                       "name"  : "Ы��",
                                       "id"    : "nature poison",
                                       "duration" : 5 + random(10), ])))
        {
                tell_object(ob, HIG "��е������ñ�����\n" NOR );
        }
}
