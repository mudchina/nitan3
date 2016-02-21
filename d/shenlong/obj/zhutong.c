// Rama@hx

#include <ansi.h>
inherit ITEM;
inherit F_SSERVER;
void setup()
{}
void init()
{
        add_action("do_entice","entice");
        add_action("do_throw","fang");
        add_action("do_put", "put");
}

void create()
{
        set_name("竹筒", ({"zhu tong" ,"zt"}));
        set_max_encumbrance(10000);
        set("unit", "个");
        set("long", "这是一节青竹制成的竹筒，如果在里面放上诱饵，可以用来捕捉毒虫(entice)。\n");
        set("value", 100);
//      set("no_drop", "这样东西不能离开你。\n");
        set_weight(105);
        set("no_sell",1);
        setup();
}
int is_container() { return 1; }

int do_entice(string arg)
{
    object me,ob1,ob;
    string who,what;
    me = this_player();
    if( !arg
        ||      sscanf(arg, "%s in %s", who, what)!=2)
         return notify_fail("命令格式: entice <毒虫> in <物品>。\n");
    ob1= present(what,me);
    ob = present(who,environment(me));
    if (!ob )
         return notify_fail("你要引诱什么？\n");
    if (!ob1 ||ob1->query("id")!="zhu tong")
         return notify_fail("你要把虫子诱往那里？\n");
    if(!present("long xianxiang",ob1))
         return notify_fail("竹筒似乎对"+ob->query("name")+"并没有吸引力！\n");
    if(ob->query("race")!="蛇类" && ob->query("race")!="昆虫" && ob->query("name")==HIW"怪蛇"NOR)
         return notify_fail("竹筒太小，似乎放不下"+ob->query("name")+"！\n");
    if( ((int)ob1->query_max_encumbrance()-(int)ob1->query_encumbrance())< ob->query_weight()  )
        return notify_fail("竹筒太小，似乎放不下"+ob->query("name")+"！\n");
    if (sizeof(all_inventory(ob1)) >= 2) 
        return notify_fail("竹筒里面已经有东西了。\n");              
    message_vision("$N将竹筒的塞子拔掉，对着"+ob->query("name")+"轻轻的吹着口哨。\n",me);
    if(me->query_skill("poison",1) < 80)
    {
        message_vision("但是"+ob->query("name")+"不为所动，反而开始对$N发动攻击！！\n",me);
        ob->kill_ob(me);
        return 1;
    }
    else {      
        message_vision("只见"+ob->query("name")+"在竹筒边探头探脑的闻了闻，忽然一闪，钻进了$N的竹筒里。\n",me);
        message_vision("$N急忙将竹筒塞住，抹了抹满头的冷汗，心想“好险啊！”。\n",me);
        ob->move(ob1);
        return 1;
        }
     return 1;
}
int do_throw(string arg)
{
    object me,ob1,ob,target;
    string who,what;
    me = this_player();
//  ob1= this_object();
    if( !arg
        ||      sscanf(arg, "%s from %s", who, what)!=2)
         return notify_fail("命令格式: fang <毒虫> from <物品>。\n");
    ob1 = present(what,me);
    if (!ob1)
         return notify_fail("你要从那里放毒虫？\n");
    ob = present(who,ob1);
    if (!ob )
         return notify_fail("你要放什么？\n");
    if( !target ) target = offensive_target(me);
    if( !target
        ||      !me->is_fighting(target) )
                return notify_fail(ob->query("name")+"只能用于战斗中暗算对手。\n");
    if ((string)me->query("family/family_name") != "神龙教"
         ||me->query_skill("poison",1) < 50)
    {
         tell_object(ob, HIG "你从颤抖着从怀里掏出竹筒，但怎么也没有胆量打开它！\n" NOR );
         message_vision(HIG"只见$N从怀里掏出一个竹筒，脸色发白，手脚颤抖不知道要干什么？\n",me);
    }
    tell_object(me,  "你悄悄从怀里掏出一个竹筒，打开了塞子。\n" );
    message_vision("只见$N虚晃一招把手一扬，一道闪光射向"+target->query("name")+"的咽喉。\n",me);
    ob->move(environment(me));
    ob->set("combat_exp",ob->query("combat_exp")*2 + target->query("combat_exp"));
    ob->kill_ob(target);
    target->start_busy(1);
        COMBAT_D->do_attack(ob, target, ob->query_temp("weapon"),0);
    message_vision("只见"+ob->query("name")+"身子在空中一折，咬向"+target->query("name")+"的头顶。\n",me);
        COMBAT_D->do_attack(ob, target, ob->query_temp("weapon"), 0);
    message_vision("只见"+ob->query("name")+"尾巴一弹，在空中一个回转竟绕到了"+target->query("name")+"的背后。\n",me);
        COMBAT_D->do_attack(ob, target, ob->query_temp("weapon"), 0);
    message_vision( target->query("name")+"只见眼前一闪，"+ob->query("name")+"竟咬向"+target->query("name")+"的肩头。\n",target);
        COMBAT_D->do_attack(ob, target, ob->query_temp("weapon"), 0);
    message_vision(ob->query("name")+"力气用尽落向地面，顺势咬向"+target->query("name")+"的脚背。\n",me);
        COMBAT_D->do_attack(ob, target, ob->query_temp("weapon"), 0);
    message_vision(ob->query("name")+"落到地面，蜿蜒地游走了。\n",me);
    destruct(ob);
    return 1;
}
int do_put(string arg)
{
    object me=this_player();
    object ob,item;
    if(!arg) return notify_fail("你要将什么东西放进哪里？\n");

    if( sscanf(arg,"%s in %s",ob,item)!=2 || !objectp(ob = present(ob, me)) || !objectp(item = present(item, me)))
    {
        write("你要放什么东西？\n");
        return 1;
    }
    else if (item->query("id") != "zhu tong")
        return 0;
        else if( ob->query("id")!="long xianxiang")
    {
        write("你不能把这件东西放到竹筒里面。\n");
        return 1;
    }
    else if( present("long xianxiang", item) )
    {
        write("竹筒里面已经有一块龙涎香了。\n");
        return 1;
    }
    else return 0;
}

