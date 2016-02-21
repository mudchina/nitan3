// league.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int sort_hatred(string id1, string id2, mapping hatred);
int sort_member(string id1, string id2);
int show_league_info(object me, string arg);
int show_league_member(object me, string arg);
int show_league_hatred(object me, string arg);
int dismiss_league(object me, string arg);
int is_league_master(object me)
{
	return (me->query("master_league")==me->query("league/league_name"));
}

int main(object me, string arg)
{
        object *obs;
        string fname,str;
        string *args;
	object who;
	int i;
	
        if (! arg) arg = "info";
        args = explode(arg, " ");
        if (sizeof(args) > 1)
                arg = implode(args[1..<1], " ");
        else
                arg = 0;

        switch (args[0])
        {
        case "info":
                // 显示同盟的信息
                return show_league_info(me, arg);

        case "member":
                return show_league_member(me, arg);

        case "dismiss":
                return dismiss_league(me, arg);

        case "top":
                return "/cmds/usr/top"->main(me, "league");

        case "hatred":
                // 显示同盟的仇人
                return show_league_hatred(me, arg);
        case "accept":
        	if(sizeof(args)<2)
        		return notify_fail("参数不够！\n");
        	if(!is_league_master(me))
        		return notify_fail("你不是盟主，不能接收新的同盟成员！\n");
                 if (! objectp(who = present(args[1], environment(me))))
                	return notify_fail("你要吸收谁加入同盟？？？\n");
       		if( who->query_temp("pending/attemp_join_league") != me->query("id") )
       			return notify_fail("人家没跟你申请加入，你是光杆司令啊？\n");
       		i=LEAGUE_D->add_member_into_league(me->query("league/league_name"),who->query("id"));
       		if(i==-1)
       			return notify_fail("错误！请与巫师联系！\n");
       		if(i==-2)
       			return notify_fail("错误！"+who->name()+"已经在同盟里啦！\n");
       		if(i==-3)
       			return notify_fail("错误！同盟人数已经满100人了！\n");
       		if(i==1)
       		{
       			write("你成功地接引对方加入同盟了！\n");
       			tell_object(who,"你已经被"+me->name()+"吸收为同盟的一员了！");
       			who->set("league",([ "time" : time(), "league_name" : me->query ("league/league_name") ]));
       			LEAGUE_D->add_league_fame(me->query("league/league_name"), who->query("weiwang")/4 );
       			return 1;
       		}
       		else
       			return notify_fail("出现错误，请联系管理员。\n");
	case "join":
        	if(sizeof(args)<2)
        		return notify_fail("参数不够！\n");
                if ( fname = me->query("league/league_name"))
                        return notify_fail("一个人只能属于一个同盟！你必须先退出原来的同盟才行！\n");
                if (! objectp(who = present(args[1], environment(me))))
                	return notify_fail("你要加入谁的同盟？？？\n");
                str=me->query_temp("pending/attemp_join_league");
                if(str)
                	write("你取消了加入"+str+"的同盟的念头！\n");
                write("你向"+who->query("name")+"请求加入同盟！\n");
                if(!stringp(fname = who->query("league/league_name")))
                	return notify_fail("可是"+who->query("name")+"还没有加入同盟的。\n");
                if(!is_league_master(who))
                	return notify_fail("可是"+who->query("name")+"并不是盟主！\n");
                me->set_temp("pending/attemp_join_league",who->query("id"));
                tell_object(who,me->query("name")+"向你提出加入同盟的请求！\n");
                return 1;
        case "out":
                if (! stringp(fname = me->query("league/league_name")))
                        return notify_fail("你现在还没有和任何人结义成盟呢。\n");

                if (me->query_temp("pending/out_league"))
                {
                        // 同盟的声望下降
                        LEAGUE_D->add_league_fame(fname, -LEAGUE_D->query_league_fame(fname) / 10);
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                "听说" + me->name(1) + "(" + me->query("id") +
                                ")义无反顾，已经背离" + fname + "而去。");
                        me->delete_temp("pending/out_league");

                        // 清除该用户在同盟中的信息
                        UPDATE_D->clear_user_data(me->query("id"), "league");
                        return 1;
                }

                write("你真的想要背弃当初的结义好友吗？这样做会降低" + fname + "的声望。\n"
                      YEL "如果你确定了，就再输入一次 league out 命令。\n" NOR);
                me->set_temp("pending/out_league", 1);
                return 1;
        }

        write("无效的参数。\n"+args[0]);
        return 1;
}

// 根据玩家和参数选择同盟的名字
mixed select_league(object me, string arg)
{
        string fam;
        object ob;

        if (! wizardp(me))
                // only wizard can show every league's list
                fam = 0;
        else
        if (stringp(arg) && arg != "")
        {
                if (! arrayp(LEAGUE_D->query("member/" + fam)))
                        fam = 0;
                else
                        fam = arg;

                if (! stringp(fam) && objectp(ob = UPDATE_D->global_find_player(arg)))
                {
                        // 没有 arg 这个同盟，查看是否有该玩家
                        fam = ob->query("league/league_name");
                        UPDATE_D->global_destruct_player(ob);
                        if (! stringp(fam))
                                return notify_fail("这人现在没有和别人结成同盟。\n");
                }

                if (! stringp(fam))
                        return notify_fail("没有这个玩家，不能查阅相关的同盟。\n");
        }

        if (! fam)
        {
                // select my league
                if (! stringp(fam = me->query("league/league_name")))
                        return notify_fail("你现在还没有和别人结义成盟呢。\n");
        }

        return fam;
}

// 显示同盟的仇人
int show_league_hatred(object me, string arg)
{
        mapping hatred;
        string fam;
        string *ids;
        mixed *data;
        string msg;
        string st;
        int count;
        int i;

        if (! stringp(fam = select_league(me, arg)))
                return 0;

        hatred = LEAGUE_D->query_league_hatred(fam);
        if (! mapp(hatred) || ! sizeof(hatred))
        {
                write(fam + "现在没有什么仇人。\n");
                return 1;
        }

        ids = keys(hatred) - ({ 0 });
        ids = sort_array(ids, (: sort_hatred :), hatred);

        count = 0;
        msg = WHT "目前" + fam + "在江湖上的仇敌都有\n" NOR
              HIY "────────────────\n" NOR;
        for (i = 0; i < sizeof(ids) && count < 30; i++)
        {
                data = hatred[ids[i]];
                if (! arrayp(data) || sizeof(data) < 2 ||
                    ! stringp(data[0]) || ! intp(data[1]))
                        continue;

                st = sprintf("%s(%s%s%s)", data[0], YEL, ids[i], NOR);
                msg += sprintf("%2d. %-34s  %s%-9d%s\n",
                               ++count, st, HIR, data[1], NOR);
        }

        msg += HIY "────────────────\n" NOR;
        if (i < sizeof(ids))
                msg += WHT "江湖上的敌人太多，难以尽数。\n" NOR;
        else
                msg += WHT "目前一共是" + chinese_number(i) +
                       "人。\n" NOR;
        write(msg);
        return 1;
}

// 显示某一个同盟中的人员
int show_league_member(object me, string arg)
{
        string *member;
        string id;
        object user;
        string msg;
        int n;

        if (! arg)
        {
                if (! stringp(arg = me->query("league/league_name")))
                        return notify_fail("你现在还没有加入任何一个同盟呢。\n");
        }

	if (! arrayp(member = LEAGUE_D->query_members(arg)))
        {
                write("现在江湖上没有(" + arg + ")这个字号。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(arg + "现在人丁稀落。\n");

        if (! wizardp(me))
        {
                if (me->query("jing") < 50)
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        msg = "";
        n = 0;
        foreach (id in member)
        {
                user = UPDATE_D->global_find_player(id);
                if (! objectp(user))
                        continue;

                n++;
                msg += user->short(1) + "\n";
                UPDATE_D->global_destruct_player(user);
        }

        if (msg == "")
                return notify_fail(arg + "现在人丁稀落。\n");

        write(arg + "目前有以下" + chinese_number(n) + "人：\n" + msg);
        return 1;
}

// 显示同盟中的信息
int show_league_info(object me, string arg)
{
        string fam;
        object  ob;
        string  msg;
        string pro;
        string *member;
        string  id;

        if (! stringp(fam = select_league(me, arg)))
                return 0;

        if (fam == me->query("league/league_name"))
                pro = "你";
        else
                pro = fam;

	if (! arrayp(member = LEAGUE_D->query_members(fam)))
        {
                write("现在江湖上没有(" + fam + ")这个字号。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(pro + "现在没有一个兄弟。\n");

        msg = pro + "现在" + LOCAL_MUD_NAME() + "的结义兄弟都有：\n\n";
        member = sort_array(member, (: sort_member :));
        foreach (id in member)
        {
                msg += sprintf(WHT "%-10s  ", id);
                if (objectp(ob = find_player(id)))
                        msg += sprintf(HIY "在线   "
                                       NOR WHT "经验：" HIC "%-9d "
                                       NOR WHT "阅历：" HIW "%-8d "
                                       NOR WHT "威望：" HIY "%-8d\n" NOR,
                                       ob->query("combat_exp"),
                                       ob->query("score"),
                                       ob->query("weiwang"));
                else
                        msg += HIR "不在线\n" NOR;
        }

        msg += sprintf("\n现在%s中一共有%s位好友，在江湖上具有 %s%d%s 点声望。\n",
                       fam, chinese_number(sizeof(member)),
                       HIY, LEAGUE_D->query_league_fame(fam), NOR);
        write(msg);

	return 1;
}

// 显示某一个同盟中的人员
int dismiss_league(object me, string arg)
{
        string *member;
        string id;
        object user;
        string msg;
        int n;

        if (wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("你的权限不够，不能强行解散同盟。\n");

        if (! arg)
                return notify_fail("你要解散哪个同盟？\n");

	if (! arrayp(member = LEAGUE_D->query_members(arg)))
        {
                write("现在江湖上没有(" + arg + ")这个字号。\n");
                return 1;
        }

        write("你强行解散了" + arg + "。\n");
        LEAGUE_D->dismiss_league(arg);
        return 1;
}


// 给所有的仇恨对象排序
int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return 1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return -1;

        return d2[1] - d1[1];
}

// 给同盟中的所有结义成员排序
int sort_member(string id1, string id2)
{
        object ob1, ob2;

        ob1 = find_player(id1);
        ob2 = find_player(id2);
        if (! objectp(ob1) && ! objectp(ob2))
                return strcmp(id2, id1);

        if (objectp(ob1) && objectp(ob2))
                return ob2->query("combat_exp") - ob1->query("combat_exp");

        if (objectp(ob1))
                return -1;

        return 1;
}

int help(object me)
{
   	write(@HELP
指令格式: league info [玩家] | hatred [玩家] | member [同盟名字] | top

查看目前你结义的同盟的各种信息，其中：

info   ：查看同盟中的人物，成员状态，声望。
hatred ：查看同盟的仇恨对象。
member ：查看某个同盟的成员。
top    ：查看结义同盟的声望排名。

巫师可以查看各个同盟的信息，只需要在命令后面加上同盟的名字或
是同盟中的玩家。另外巫师可以使用 league dismiss 命令强行解散
一个同盟。

see also: team (团体同盟)
HELP );
   	return 1;
}
