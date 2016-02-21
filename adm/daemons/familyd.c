// familyd.c 保存所有的门派信息

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 门派声望最大是10亿
#define MAX_FAMILY_FAME         1000000000

// 每个门派最多有100个仇人
#define MAX_HATRED_PERSON       100

// 当仇人超过的时候每次移除多少个
#define HATREDP_REMOVED         10

mapping family_fame = ([
        "少林寺"   : 10000000,
        "武当派"   : 8000000,
        "丐帮"     : 7000000,
        "全真教"   : 5000000,
        "华山派"   : 4500000,
        "段氏皇族" : 4000000,
        "慕容世家" : 4000000,
        "大轮寺"   : 3500000,
        "灵鹫宫"   : 3500000,
        "峨嵋派"   : 3000000,
        "桃花岛"   : 2500000,
        "神龙教"   : 2000000,
        "古墓派"   : 1500000,
        "星宿派"   : 1200000,
        "逍遥派"   : 1000000,
        "血刀门"   : 800000,
        "华山剑宗" : 600000,
        "欧阳世家" : 500000,
        "关外胡家" : 400000,
        "明教"     : 400000,
        "唐门世家" : 400000, 
        "日月神教" : 400000, 
]);

// 门派ID对应的门派名字
nosave mapping family_name = ([
        "shaolin"  : "少林寺",
        "wudang"   : "武当派",
        "gaibang"  : "丐帮",
        "quanzhen" : "全真教",
        "huashan"  : "华山派",
        "duan"     : "段氏皇族",
        "murong"   : "慕容世家",
        "xueshan"  : "大轮寺",
        "lingjiu"  : "灵鹫宫",
        "emei"     : "峨嵋派",
        "taohua"   : "桃花岛",
        "shenlong" : "神龙教",
        "gumu"     : "古墓派",
        "xingxiu"  : "星宿派",
        "xiaoyao"  : "逍遥派",
        "xuedao"   : "血刀门",
        "jianzong" : "华山剑宗",
        "ouyang"   : "欧阳世家",
        "hu"       : "关外胡家",
        "mingjiao" : "明教",
        "tang"     : "唐门世家",
        "riyue"    : "日月神教",
]);

mapping last_family_fame;

// 门派对仇人仇恨度的排序
private int sort_hatred(string id1, string id2, mapping hatred);

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(1800);
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

// 心跳：维护门派的通常信息
void heart_beat()
{
        int t;
        int last;
        string *all_fam;
        string fam;

        t = time();
        last = query("last_check");
        if ((t / 86400) != (last / 86400))
        {
                // 天数发生了变化：复制门派的名望信息
                all_fam = keys(family_fame) - ({ 0 });
                last_family_fame = family_fame;
                family_fame = ([ ]);

                foreach (fam in all_fam)
                        family_fame[fam] = last_family_fame[fam];
        }
        set("last_check", t);

        // 保存门派的最新信息
        save();
}

// 返回门派声望：如果参数为空，返回mapping类型，包含了所有门
// 派的声望；如果参数是人物， 则返回该人物所在的那个门派的声
// 望；如果参数是门派，则返回该门派的声望。
public mixed query_family_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return family_fame[ob];

        if (objectp(ob))
        {
                if (stringp(fname = ob->query("family/family_name")))
                        return family_fame[fname];
                else
                        return 0;
        }

        return family_fame;
}

// 查询昨天的门派名望信息
public mapping query_all_last_family_fame()
{
        if (! mapp(last_family_fame))
                // 没有昨天的信息，返回今天的
                return family_fame;

        // 返回昨天的门派声望信息
        return last_family_fame;
}

// 查询门派的仇恨信息：输入的ob可以是门派的名字，也可是门派
// 中的人物。
public mapping query_family_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname = ob->query("family/family_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query("hatred/" + fname)))
                return 0;

        return hatred;
}

// 变化门派声望：输入的ob可以是门派的名字，也可是门派中的人
// 物。
public void add_family_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname = ob->query("family/family_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(family_fame[fname]))
                return;

        // 计算新的门派声望
        new_fame = family_fame[fname] + n;
        if (new_fame < 0) new_fame = 0;
        if (new_fame > MAX_FAMILY_FAME)
                new_fame = MAX_FAMILY_FAME;
        family_fame[fname] = new_fame;
}

// 门派间仇杀
public void family_kill(object killer, object victim)
{
        mixed kexp;
        mixed vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // 只有玩家之间的仇杀才计算在内
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // 巫师之间的比划可不能算数
        if (wizardp(killer) || wizardp(victim))
                return;

        kexp = killer->query("combat_exp");
        vexp = victim->query("combat_exp");
        kfam = killer->query("family/family_name");
        vfam = victim->query("family/family_name");

        if (stringp(kfam) && kfam == vfam)
        {
                // 同门残杀？
                return;
        }

        if (count_lt(kexp, count_mul(vexp, 3)) && count_ge(vexp, 100000))
        {
                // 杀手的经验不是远远的大于对方，并且被杀的
                // 人有一定的经验，这将导致门派声望的降低。
                sscanf(vexp, "%d", vexp);
                fame_delta = vexp + killer->query("score") * 2 +
                             killer->query("weiwang") * 10;
                fame_delta /= 1000;
        } else
                // 对手经验太少，或是差距太大，不影响声望
                fame_delta = 0;

        // 查看杀手所在的门派是否仇恨死者：如果仇恨，则能够
        // 带动声望的变化。
        if (stringp(kfam))
        {
                string path;

                path = "hatred/" + kfam + "/" + victim->query("id");
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // 仇恨死者，门派获得额外的声望
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "听说" + killer->name(1) + "击毙了" +
                                        victim->name(1) + "，为" +
                                        kfam + "讨回了公道。");
                        fame_delta += d[1] / 3;

                        // 对此人的仇恨降低(降低的要比增加的要多)，
                        // 具体可以看fame_delta 与仇恨度公司的差异
                        d[1] -= fame_delta;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // 调整两个门派的声望
        add_family_fame(killer,  fame_delta);
        add_family_fame(victim, -fame_delta);

        // 统计该杀手对本门的残害程度
        if (! stringp(vfam))
                return;

        // 仇恨程度和声望的变化都是在一个数量级上(K经验)，但
        // 是仇恨程度低于声望的变化。
        vexp = atoi(count_div(vexp, 1000)) + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid = killer->query("id");
        if (! mapp(hatred = query("hatred/" + vfam)))
        {
                set("hatred/" + vfam + "/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // 每个门派最多记录若干个仇人
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // 这个ID的数据出了故障
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // 过滤去掉一些人，为什么不去掉一个？这是为
                // 了防止过滤频繁的进行过滤操作。
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // 记录这个人的信息
        hatred[kid] = d;
}

// 去掉所有门派对某个人的仇恨信息
public void remove_hatred(string id)
{
        mapping all_hatred, hatred;
        string fam;

        if (! mapp(all_hatred = query("hatred")))
                // 现在还没有仇恨信息
                return;

        // 查阅所有的门派
        foreach (fam in keys(all_hatred))
        {
                if (mapp(hatred = all_hatred[fam]))
                        // 去掉该门派对某人的仇恨信息
                        map_delete(hatred, id);

                if (! mapp(hatred) || ! sizeof(hatred))
                        // 这个门派已经没有仇恨信息
                        map_delete(all_hatred, fam);
        }
}

// 排序：升序
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

public string query_family_name(string fid)
{
        string fam;

        if (undefinedp(fam = family_name[fid]))
                fam = fid;
        return fam;
}

public mapping query_all_family_name()
{
        return family_name;
}

public string query_save_file() { return DATA_DIR "familyd"; }
