//查询游戏交费时间的命令，直接从数据库取数据，应该禁止频繁读取
//Write By JackyBoy@TOMUD 2001/5/15
#include <ansi.h>

inherit F_CLEAN_UP;

string bar_string = "■■■■■■■■■■■■■■■■■■■■■■■■■";
string blank_string = "□□□□□□□□□□□□□□□□□□□□□□□□□";
string status_color(int current, int max);
string tribar_graph(int val, int eff, int max, string color);
int buy_monfee();
void verify_pass(string arg,object me,int c);

int main(object me,string arg)
{
	string *res;
	int onl,fee,monfee;
	string line;
	
	if (! arg|| !wizardp(me))
	{
		if(!wizardp(me)&&me->query_temp("last_query_fee") > time() - 60 )
			return notify_fail("请不要频繁查询交费信息!\n");
		me->set_temp("last_query_fee",time());
		arg=me->query("id");
	}
	arg = lower_case(arg);
	if(arg=="转月费" ||arg == "buy_monfee" ||arg == "交月费"  || 
		arg=="缴月费" || arg=="buymonfee" ||arg=="buy monfee")
	{
		buy_monfee();
		return 1;
	}
	if(me->id(arg))
		me->save();
	seteuid(getuid(me));
	res=DATABASE_D->do_sql("select on_time,fee_time,subgy(f_dbase,'monfee') from users where id="+DB_STR(arg));
	line=" 请注意，本命令不是即时命令，可能会与你实际情况稍有偏差。\n";
	line+= HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR+
			" 用户 "+HIR+arg+NOR+" 的交费及使用情况如下：\n";
	if(!res) line+="未发现指定对象("+arg+")的用户资料！\n";
	else
	{
		int i,j;
		sscanf(res[0]+"0","%d",onl);
		sscanf(res[1]+"0","%d",fee);
		onl/=10;fee/=10;
		i=onl%3600;
		onl/=3600;
		j=i%60;
		line += " 累计购买时间： "+HIY+fee+NOR+" 小时\n";
		line += " 累计使用时间： "+HIY+(onl)+NOR+" 小时 ";
		if(i) line+=HIY+(i/60)+NOR+" 分 ";
		if(j) line+=(HIY+j)+NOR+" 秒";
		if(onl>=fee)
			line += "\n 你购买的游戏时间已经使用完了，请联系Tomud小组http://www.tomud.com 继续购买游戏时间！\n";
		else
			line += "\n 使用情况： " + tribar_graph(onl, fee, fee, HIY) + "\n";
		sscanf(res[2],"%*s%d%*s",monfee);
		if(monfee!=0)
			line += " 你的月费到期时间为："+CHINESE_D->cctime(monfee)+"\n 你可以使用括号内的命令{"+HIY+"fee 交月费"+NOR+"}来增加包月时间。\n";
		else
			line += " 你从未转过月费！你可以使用{"+HIY+"fee 交月费"+NOR+"}命令转换为包月计费方式。\n";
		if(fee==18)
			line+=ALERT("你好，你还未对此人物角色进行注册！请及时交费注册购买时间！$$未注册而且连续 "+
				UNREG_IDLE+" 天未上线者我们将清除其档案!");
	}
	line += HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR;
	tell_object(me,line);
	return 1;
}

string status_color(int current, int max)
{
	int percent;

	if (max) percent = current * 100 / max;
	else percent = 100;

	if (percent > 100) return HIC;
	if (percent >= 90) return HIG;
	if (percent >= 60) return HIY;
	if (percent >= 30) return YEL;
	if (percent >= 10) return HIR;
	return RED;
}

string tribar_graph(int val, int eff, int max, string color)
{
	return color + bar_string[0..(val * 25 / max) * 2 - 1]
		+ ((eff > val) ? blank_string[(val * 25 / max) * 2..(eff * 25 / max) * 2 - 1] : "") + NOR;
}

//这个函数只对this_player()进行操作！所以一定要注意不要试图操作其他人！
int buy_monfee()
{
        //做防止刷屏判断，因为该操作直接涉及到数据库操作
        object me=this_player();
        me->save();
	if(!wizardp(me)&&me->query_temp("last_query_fee") > time() - 300 )
	{
		write("请不要频繁进行转换操作，至少间隔五分钟!\n");
		return 1;
        }
	me->set_temp("last_query_fee",time());
	if(me->query("doing")=="scheme")
	{
		write("对不起，计划时不能进行这个操作！");
		return 1;
	}
	write("请输入你的管理密码，以确认此次操作：");
	input_to("verify_pass",me,0);
	return 1;
}

void verify_pass(string arg,object me,int c)
{
        string sql;
        int onl,fee;
        mixed res;
	mapping m=me->query_entire_dbase();
	string my_pass;
	object lkob=me->query_temp("link_ob");
	if(!objectp(lkob))
	{
		write(ALERT("对不起，你的人物角色状态不对，请先找管理员来处理一下吧！"));
		return ;
	}
	my_pass=lkob->query("ad_password");
	if(arg=="quit"||arg==""||arg=="exit")
	{
		write("你退出了转月费的操作！\n");
		return ;
	}
	if(crypt(arg, my_pass) != my_pass)
	{
		if(c>2)
		{
			write(ALERT("对不起，请确定你没记错管理密码再来试吧！"));
			return ;
		}
		write(ALERT("管理密码不对！(请回车或输入exit命令退出转月费操作)")+"\n请输入你的管理密码以验证操作：");
		input_to("verify_pass",me,++c);
		return ;
	}
	arg=m["id"];
	res=DATABASE_D->do_sql("select on_time,fee_time from users where id="+DB_STR(arg));
	if(!res) write("查询出错，请询问游戏管理员。\n");
	else
	{
		int i,j;
		sscanf(res[0]+"0","%d",onl);
		sscanf(res[1]+"0","%d",fee);
		onl/=10;fee/=10;
		i=m["monfee"]-time();
		if(i<0) i=0;
		i/=86400;//包月还有多少天！
		write("你交过的游戏点是"+fee+"可用数"+(fee-onl/3600)+"\n");
                if(fee - onl/3600 > 318 && i<120 )
                {
                        sql=sprintf("update users set fee_time=fee_time-300,endrgt=now() where id="+DB_STR(arg));
                        if ((DATABASE_D->do_sqlexec(sql))<1)
                        {
                                write("扣除点数失败，未能成功缴纳月费，请尽快联系游戏管理员查明原因。\n");
                                return ;
                        }
                        else
                        {
                                //扣除点数成功	                        
	                        if(m["monfee"]>time())
                                        m["monfee"]+=86400*30;//如果本来是月费，则在月费上加
                                else
                                        m["monfee"]=time()+86400*30;
                                me->save();
                                //重新从数据库取，以验证是否真的已经改变
	                       	res=DATABASE_D->do_sql("select fee_time from users where id="+DB_STR(arg));
	                       	sscanf(res[0]+"0","%d",j);
	                       	write("300个游戏点扣除成功！现在你交过的游戏点是"+j/10+"\n");
	                       	write("缴月费成功，月费期限延长到 "+CHINESE_D->cctime(m["monfee"])+"，还有"+(i+30)+"天 。\n");
                                sql=sprintf("insert into reg_log (id,add_hours,new_fee_time,time) values (%s,%d,%d,now())",DB_STR(arg),-300,j/10);
                                if(DATABASE_D->do_sqlexec(sql) < 1)
                                	log_file("database",ctime(time())+":"+sql);
                        }


                }
                else
                {
                	if(i>=120)
                		write("对不起，你目前已经包了五个月（剩余"+i+"天！）了，而包月最多只能五个月！");
                	else
                        	write("你的点数已经不够缴月费了。请确认还有318个游戏点。\n");
                }
	}
}
int help()
{
	write(@HELP
指令格式 : fee
           fee <对象名称>                   (巫师专用)

这个指令可以显示你或指定对象的交费情况。
交费等信息请访问主页 [http://www.tomud.com] 。

HELP );
    return 1;
}

