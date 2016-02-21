// 恢复一级技能、一半潜能及百分之二经验的仙药，由巫师掌握，需name，留有记录

#include <ansi.h>
inherit ITEM;
int do_eat(string);
int do_name(string);
void setup()
{}

void init()
{
    add_action("do_eat", "eat");
    add_action("do_name","name");
}

void create()
{
    set_name(HIB"ＢＵＧ死亡弥补丹"NOR, ({"mibu dan", "dan"}));
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit", "粒");
        set("long", "这是一粒非常奇异的药丸，据说一吃就死，但也或许有某些奇效。\n");
    }
    setup();
}

int do_eat(string arg)
{
    int i,level;
    mixed exp, pot;
    object me;
    mapping skill_status;
    string *sname;
    me = this_player();
    skill_status = me->query_skills();
    
    if (!id(arg))
        return notify_fail("你要吃什么？\n");
    if( !living(me) )
    return notify_fail("什么？\n");
    if(!query("me_id")||query("me_id")!=me->query("id"))
        return notify_fail("你用力朝一吃就死丹一口咬下去，“哎呀！”烫得赶紧吐出来，嘴里起了一圈泡！\n");
    sname = keys(skill_status);
    for(i = 0; i < sizeof(skill_status); i++)
    {
        level = skill_status[sname[i]] + 1;
        me->set_skill(sname[i], level);
    }
    exp  = me->query("combat_exp");
    me->set("combat_exp", count_div(count_mul(exp, 20), 19));
    pot = count_div(count_sub(me->query("potential"), me->query("learned_points")), 2);
    me->add("potential",pot);
    me->add("max_neili",20);
    write_file("/log/static/1794_eat",sprintf("(%s)%s(%s)服用一吃就死丹一次\n", ctime(time()),me->name(),me->query("id")));
    write("你失去的技能、潜能和经验被神力恢复回来了。\n");
    destruct(this_object());
    return 1;
}

int do_name(string arg)
{
    object me;
    me = this_player();
    if( !wizardp(me)) return 0;
    if(!arg) return notify_fail("name id!\n");
    set("me_id",arg);
    write("这粒一吃就死丹被设为"+arg+"专用的，别人无法吃！\n");
    return 1;
}

