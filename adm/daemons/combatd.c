// combatd.c
// Update by Doing for HELL
// Update by Lonely for nt2
// 解体增强技能威力的尚没有填加

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

// 关于玩家数据(/combat/)的说明
// PKS：杀害的玩家数目
// MKS；杀死的NPC数目(动物不计算)
// WPK：主动杀死玩家的次数
// WPK_NOTGOOD：主动杀死非正派(shen < 500)玩家的次数
// WPK_BAD：    主动杀死的邪派(shen <-500)玩家的次数
// WPK_NOTBAD： 主动杀死非邪派(shen >-500)玩家的次数
// WPK_GOOD：   主动杀死的正派(shen > 500)玩家的次数
// DPS：主动打晕玩家的次数
// DPS_NOTGOOD：主动打晕非正派(shen < 500)玩家的次数
// DPS_BAD：    主动打晕的邪派(shen <-500)玩家的次数
// DPS_NOTBAD： 主动打晕非邪派(shen >-500)玩家的次数
// DPS_GOOD：   主动打晕的正派(shen > 500)玩家的次数
// dietimes：   死亡的次数

// combat/today纪录(mapping)
// which_day: 日期(实际时间中日期)
// id       : n, 主动打晕某个ID的次数

#define DEFAULT_MAX_PK_PERDAY           8
#define DEFAULT_MAX_PK_PERMAN           2

// 经验底线(random(my_exp) > EXP_LIMIT，则不加经验)
#define EXP_LIMIT       200000000

#define ATTACK          0
#define DODGE           1
#define PARRY           2
#define DAMAGE          3
#define FORCE1           4

varargs void report_status(object ob, int effective);
private void special_bonus(object me, mixed arg);
private void money_bonus(object me, mixed arg);
void check_quest(object killer, object victim);
string base_dir(object obj);
int auto_perform(object me, object target, string perform_skill);

void team_gain(object me,string name, int gain);
void array_gain(object me,string name,int gain,int exp);

string *danger_limbs = ({
        "头部", "颈部", "胸口", "后心","小腹",
});

string *head_damage_me_msg = ({
        HIR "你觉得头有一点发晕。\n" NOR,
        HIB "你觉得一阵晕眩，身体晃了一下。\n" NOR,
        BLU "你只得眼冒金星，浑身发飘。\n" NOR,
});

string *body_damage_me_msg = ({
        HIR "你只觉$l隐隐作痛，体内真气受到一点振荡。\n" NOR,
        HIB "你只觉$l生疼，体内真气一阵乱窜。\n" NOR,
        BLU "你只觉得$l处剧痛，连带着体内真气一阵外泄。\n" NOR,
});

string *guard_msg = ({
        append_color(CYN "$N注视著$n的行动，企图寻找机会出手。\n" NOR, CYN),
        append_color(CYN "$N正盯著$n的一举一动，随时准备发动攻势。\n" NOR, CYN),
        append_color(CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR, CYN),
        append_color(CYN "$N目不转睛地盯著$n的动作，寻找进攻的最佳时机。\n" NOR, CYN),
        append_color(CYN "$N慢慢地移动著脚步，伺机出手。\n" NOR, CYN),
});

string *catch_hunt_human_msg = ({
        append_color(HIW "$N和$n仇人相见份外眼红，立刻打了起来！\n" NOR, HIW),
        append_color(HIW "$N对著$n大喝：「可恶，又是你！」\n" NOR, HIW),
        append_color(HIW "$N和$n一碰面，二话不说就打了起来！\n" NOR, HIW),
        append_color(HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR, HIW),
        append_color(HIW "$N一见到$n，愣了一愣，大叫：「我宰了你！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，我们的帐还没算完，看招！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，看招！」\n" NOR, HIW),
});

string *catch_hunt_beast_msg = ({
        append_color(HIW "$N怒吼一声，扑了过来攻击$n！\n" NOR, HIW),
        append_color(HIW "$N对著$n大吼，想杀死$n！\n" NOR, HIW),
        append_color(HIW "$N发出连串低吼，突然暴起攻击$n！\n" NOR, HIW),
});

string *catch_hunt_bird_msg = ({
        append_color(HIW "$N对著$n一声怒鸣，飞冲了过来！\n" NOR, HIW),
        append_color(HIW "$N怒鸣几声，突然暴起攻击$n！\n" NOR, HIW),
        append_color(HIW "$N一声锐鸣，猛然向$n发动攻击！\n" NOR, HIW),
});

string *catch_hunt_msg = ({
        append_color(HIW "$N和$n仇人相见分外眼红，立刻打了起来！\n" NOR, HIW),
        append_color(HIW "$N对著$n大喝：「可恶，又是你！」\n" NOR, HIW),
        append_color(HIW "$N和$n一碰面，二话不说就打了起来！\n" NOR, HIW),
        append_color(HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR, HIW),
        append_color(HIW "$N一见到$n，愣了一愣，大叫：「我宰了你！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，我们的帐还没算完，看招！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，看招！」\n" NOR, HIW),
});

string *winner_msg = ({
        append_color(CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR, CYN),
        append_color(CYN "\n$N双手一拱，笑著说道：承让！\n\n" NOR, CYN),
        append_color(CYN "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR, CYN),
        append_color(CYN "\n$N双手一拱，笑著说道：知道我的利害了吧！\n\n" NOR, CYN),
        append_color(CYN "\n$N胜了这招，向后跃开三尺，叹道：真是拔剑四顾心茫然！\n\n" NOR, CYN),
        append_color(CYN "\n$n向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！\n\n" NOR, CYN),
        append_color(CYN "\n$n向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n" NOR, CYN),
        append_color(CYN "\n$n脸色一寒，说道：算了算了，就当是我让你吧！\n\n" NOR, CYN),
        append_color(CYN "\n$n纵声而笑，叫道：“你运气好！你运气好！”一面身子向后跳开。\n\n" NOR, CYN),
        append_color(CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR, CYN),
        append_color(CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR, CYN),
        append_color(CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR, CYN),
});

void create()
{
        int pd, pm;

        seteuid(getuid());
        set("channel_id", "战斗精灵");

        // if (undefinedp(pd = CONFIG_D->query_int("max pk perday")))
                pd = DEFAULT_MAX_PK_PERDAY;

        // if (undefinedp(pm = CONFIG_D->query_int("max pk perman")))
                pm = DEFAULT_MAX_PK_PERMAN;

        set("pk_perday", pd);
        set("pk_perman", pm);
}

// message after damage info
nosave string foo_before_hit = 0;
nosave string foo_after_hit = 0;

void set_bhinfo(string msg)
{
        if (! foo_before_hit)
        {
                foo_before_hit = msg;
                return;
        }

        foo_before_hit += msg;
}

void set_ahinfo(string msg)
{
        if (! foo_after_hit)
        {
                foo_after_hit = msg;
                return;
        }

        foo_after_hit += msg;
}

string query_bhinfo() { return foo_before_hit; }

string query_ahinfo() { return foo_after_hit; }

void clear_bhinfo() { foo_before_hit = 0; }

void clear_ahinfo() { foo_after_hit = 0; }

string damage_msg(int damage, string type)
{
        string str;

        if (damage == 0)
                return "结果没有造成任何伤害。\n";

        switch (type)
        {
        case "擦伤":
        case "割伤":
                if (damage < 15)  return "结果只是轻轻地划破$p的皮肉。\n"; else
                if (damage < 40)  return "结果在$p$l划出一道细长的血痕。\n"; else
                if (damage < 100) return "结果「嗤」地一声，$w已在$p$l划出一道伤口！\n"; else
                if (damage < 200) return "结果「嗤」地一声，$w已在$p$l划出一道血淋淋的伤口！\n"; else
                if (damage < 400) return "结果「嗤」地一声，$w已在$p$l划出一道又长又深的伤口，溅得$N满脸鲜血！\n"; else
                                  return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！\n";
                break;
        case "刺伤":
                if (damage < 15)  return "结果只是轻轻地刺破$p的皮肉。\n"; else
                if (damage < 40)  return "结果在$p$l刺出一个创口。\n"; else
                if (damage < 100) return "结果「噗」地一声，$w已刺入了$n$l寸许！\n"; else
                if (damage < 200) return "结果「噗」地一声，$w已刺进$n的$l，使$p不由自主地退了几步！\n"; else
                if (damage < 400) return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉□糊的血窟窿！\n"; else
                                  return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！\n";
                break;
        case "瘀伤":
        case "震伤":
                if (damage < 15)  return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n"; else
                if (damage < 40)  return "结果在$p的$l造成一处瘀青。\n"; else
                if (damage < 100) return "结果一击命中，$n的$l登时肿了一块老高！\n"; else
                if (damage < 150) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n"; else
                if (damage < 200) return "结果「砰」地一声，$n退了两步！\n"; else
                if (damage < 400) return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n"; else
                if (damage < 800) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n"; else
                                  return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！\n";
                break;
        case "内伤":
                if (damage < 15)  return "结果只是把$n打得退了半步，毫发无损。\n"; else
                if (damage < 40)  return "结果$n痛哼一声，在$p的$l造成一处瘀伤。\n"; else
                if (damage < 100) return "结果一击命中，把$n打得痛得弯下腰去！\n"; else
                if (damage < 150) return "结果$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n"; else
                if (damage < 200) return "结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n"; else
                if (damage < 400) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n"; else
                if (damage < 800) return "结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n"; else
                                  return "结果只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！\n";
                break;
        case "点穴":
                if (damage < 15)  return "结果只是轻轻的碰到$n的$l，根本没有点到穴道。\n"; else
                if (damage < 40)  return "结果$n痛哼一声，在$p的$l造成一处淤青。\n"; else
                if (damage < 100) return "结果一击命中，$N点中了$n$l上的穴道，$n只觉一阵麻木！\n"; else
                if (damage < 200) return "结果$n闷哼了一声，脸上一阵青一阵白，登时觉得$l麻木！\n"; else
                if (damage < 400) return "结果$n脸色一下变得惨白，被$N点中$l的穴道,一阵疼痛遍布整个$l！\n"; else
                if (damage < 800) return "结果$n一声大叫，$l的穴道被点中,疼痛直入心肺！\n"; else
                                  return "结果只听见$n一声惨叫，一阵剧痛夹杂着麻痒游遍全身，跟着直挺挺的倒了下去！\n";
                break;
        case "抽伤":
                if (damage < 15)  return "结果只是在$n的皮肉上碰了碰，好象只蹭破点皮。\n"; else
                if (damage < 40)  return "结果在$n$l抽出一道轻微的紫痕。\n"; else
                if (damage < 100) return "结果「啪」地一声在$n$l抽出一道长长的血痕！\n"; else
                if (damage < 200) return "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n"; else
                if (damage < 400) return "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n"; else
                if (damage < 800) return "结果「啪」地一声爆响！这一下好厉害，只抽得$n皮开肉绽，血花飞溅！\n"; else
                                  return "结果只听见$n一声惨嚎，$w重重地抽上了$p的$l，$n顿时血肉横飞，十命断了九条！\n";
                break;
        case "反震伤":
                if (damage < 15)  return "结果$N受到$n的内力反震，闷哼一声。\n"; else
                if (damage < 40)  return "结果$N被$n的反震得气血翻腾，大惊失色。\n"; else
                if (damage < 100) return "结果$N被$n的反震得站立不稳，摇摇晃晃。\n"; else
                if (damage < 200) return "结果$N被$n以内力反震，「嘿」地一声退了两步。\n"; else
                if (damage < 300) return "结果$N被$n的震得反弹回来的力量震得半身发麻。\n"; else
                if (damage < 400) return "结果$N被$n的内力反震，胸口有如受到一记重击，连退了五六步！\n"; else
                if (damage < 600) return "结果$N被$n内力反震，眼前一黑，身子向後飞出丈许！\n"; else
                                  return "结果$N被$n内力反震，眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！\n";
                break;
        case "砸伤":
                if (damage < 10)  return "结果只是轻轻地碰到，像是给$n搔了一下痒。\n"; else
                if (damage < 40)  return "结果在$n的$l砸出一个小臌包。\n"; else
                if (damage < 100) return "结果$N这一下砸个正着，$n的$l登时肿了一块老高！\n"; else
                if (damage < 150) return "结果$N这一下砸个正着，$n闷哼一声显然吃了不小的亏！\n"; else
                if (damage < 200) return "结果只听「砰」地一声，$n疼得连腰都弯了下来！\n"; else
                if (damage < 400) return "结果这一下「轰」地一声砸得$n眼冒金星，差一点摔倒！\n"; else
                if (damage < 800) return "结果重重地砸中，$n眼前一黑，「哇」地一声吐出一口鲜血！\n"; else
                                  return "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！\n";
                break;
        default:
                if (! type) type = "伤害";
                if (damage < 15)  str = "结果只是勉强造成一处轻微"; else
                if (damage < 40)  str = "结果造成轻微的"; else
                if (damage < 100) str = "结果造成一处"; else
                if (damage < 150) str = "造成一处严重"; else
                if (damage < 200) str = "结果造成颇为严重的"; else
                if (damage < 300) str = "结果造成相当严重的"; else
                if (damage < 400) str = "结果造成十分严重的"; else
                if (damage < 600) str = "结果造成极其严重的"; else
                                  str = "结果造成非常可怕的严重";
                return str + type + "！\n";
        }
}

string eff_status_msg(int ratio)
{
        if (ratio==100) return HIG "看起来气血充盈，并没有受伤。" NOR;
        if (ratio > 95) return HIG "似乎受了点轻伤，不过光从外表看不大出来。" NOR;
        if (ratio > 90) return HIY "看起来可能受了点轻伤。" NOR;
        if (ratio > 80) return HIY "受了几处伤，不过似乎并不碍事。" NOR;
        if (ratio > 60) return HIY "受伤不轻，看起来状况并不太好。" NOR;
        if (ratio > 40) return HIR "气息粗重，动作开始散乱，看来所受的伤著实不轻。" NOR;
        if (ratio > 30) return HIR "已经伤痕累累，正在勉力支撑著不倒下去。" NOR;
        if (ratio > 20) return HIR "受了相当重的伤，只怕会有生命危险。" NOR;
        if (ratio > 10) return RED "伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
        if (ratio > 5 ) return RED "受伤过重，已经奄奄一息，命在旦夕了。" NOR;
        return RED "受伤过重，已经有如风中残烛，随时都可能断气。" NOR;
}

string status_msg(int ratio)
{
        if (ratio==100) return HIG "看起来充满活力，一点也不累。" NOR;
        if (ratio > 95) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
        if (ratio > 90) return HIY "看起来可能有些累了。" NOR;
        if (ratio > 80) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
        if (ratio > 60) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
        if (ratio > 40) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
        if (ratio > 30) return HIR "已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
        if (ratio > 20) return HIR "看起来已经力不从心了。" NOR;
        if (ratio > 10) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
        return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

varargs void report_status(object ob, int effective)
{
        if (! ob || ! ob->query("max_qi"))
                return;

        if (effective)
                message_vision( "( $N" + eff_status_msg(
                        (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi") )
                        + " )\n", ob);
        else
                message_vision( "( $N" + status_msg(
                        (int)ob->query("qi") * 100 / (int)ob->query("max_qi") )
                        + " )\n", ob);
}

// Doing
// Reduce the power of the combat_exp
mixed valid_power(mixed combat_exp)
{
#ifdef LONELY_IMPROVED
        if (count_lt(combat_exp, 20000000))
                return combat_exp;

        combat_exp = count_sub(combat_exp, 20000000);
        if (count_lt(combat_exp, 10000000))
                return count_add(20000000, count_div(combat_exp, 10));

        combat_exp = count_sub(combat_exp, 10000000);
        return count_add(21000000, count_div(combat_exp, 20));
#else
        if (combat_exp < 20000000)
                return combat_exp;

        combat_exp -= 20000000;
        if (combat_exp < 10000000)
                return 20000000 + combat_exp / 10;

        combat_exp -= 10000000;
        return 20000000 + (10000000 / 10) + (combat_exp / 20);
#endif
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs mixed skill_power(object ob, string skill, int usage, int delta)
{
       // int status, level;
       int level;
        mixed power;
        mapping dbase;
        mapping temp;
        //mapping fight;
        mapping apply;

        if (! living(ob)) return 0;

        level = ob->query_skill(skill);

        dbase = ob->query_entire_dbase();
        temp = ob->query_entire_temp_dbase();
        if (temp)
        {
                apply = temp["apply"];
                // fight = temp["fight"];
        }

        switch (usage)
        {
                case SKILL_USAGE_ATTACK:
                        if (apply) level += apply["attack"];
                        break;
                case SKILL_USAGE_DEFENSE:
                        if (apply)
                        {
                        	level += apply[skill];
                        	level += apply["defense"];
                        }
                        break;
        }

        level += delta;
#ifdef LONELY_IMPROVED
        if (level < 1)
        {
                power = count_div(valid_power(ob->query("combat_exp")), 2);
                if (usage == SKILL_USAGE_ATTACK)
                        power = count_mul(count_div(power, 30), dbase["str"]);
                else
                        power = count_mul(count_div(power, 30), dbase["dex"]);

                return  power;
        }
        power = count_div(count_mul(count_mul(level, level), level), 100);
        power = count_add(power, valid_power(dbase["combat_exp"]));
        if (ob->query_xuruo()) power = count_div(power, 2);
        if (usage == SKILL_USAGE_ATTACK)
        {
                power = count_mul(count_div(power, 30), (dbase["str"] + (temp ? temp["str"] / 10 : 0)));
           	/*
           	if (fight && ob->is_fighting())
                         power = count_add(power, count_mul(count_div(power, 100), fight["attack"]));
                */
        }
        else
        {
                power = count_mul(count_div(power, 30), (dbase["dex"] + (temp ? temp["dex"] / 10 : 0)));
                /*
                if (fight && ob->is_fighting())
                         power = count_add(power, count_mul(count_div(power, 100), fight[skill]));
                */
                // 提高阵法的防御力
                if (ob->in_array())
                {
                        int n;

                        if ((n =  ob->query_array_level() / 100))
                                power = count_add(power, count_div(count_mul(power, n), 100));
                }
        }

        return power;
#else
        if (level < 1)
        {
                power = valid_power((int)ob->query("combat_exp")) / 2;
                if (usage == SKILL_USAGE_ATTACK)
                        power = power / 30 * dbase["str"];
                else
                        power = power / 30 * dbase["dex"];
                return  power;
        }

        if (level > 500)

                power = (level / 10) * (level / 10) * level;
        else
                power = level * (level / 10) * (level / 10);

        power += valid_power(dbase["combat_exp"]);
        // 虚弱状态，攻防减半
        if (ob->query_xuruo()) power /= 2;
        if (usage == SKILL_USAGE_ATTACK)
        {
                power = power / 30 * (dbase["str"] + (temp ? temp["str"] / 10 : 0));
                /*
                if (fight && ob->is_fighting())
                         power += power / 100 * fight["attack"];
                */
        } else
        {
                power = power / 30 * (dbase["dex"] + (temp ? temp["dex"] / 10 : 0));
		/*
                if (fight && ob->is_fighting())
                         power += power / 100 * fight[skill];
                */

                // 提高阵法的防御力
                if (ob->in_array())
                {
                        int n;

                        if ((n =  ob->query_array_level() / 100))
                        {
                                if (n < 10)
                                        power += power * n / 100;
                                else
                                        power += power / 100 * n;
                        }
                }
        }

        return power;
#endif
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
        mapping my, your;
        mapping my_temp, your_temp;
        mapping prepare, action;
        mapping fight;
        string limb, *limbs;
        string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
        string parry_msg;
        mixed foo;

        int delta;
        int ap, dp, pp;
        int damage, damage_bonus;
        int cost;
        int wounded;
        int array_flag;
        int attack;
        int avoid;

        object weapon2; // weapon of victim
        object cloth;   // armor of victim

        string result;
        string damage_info;
        string damage_desc;
        string *att, *def;

       // object env_me;
        //object env_v;

#ifdef LONELY_IMPROVED
        string apo, dpo, ppo;
#endif

        if (environment(me)->query("no_fight"))
        {
                message_vision("$N和$n各自退了一步，收住了招。\n",
                               me, victim);
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        if (environment(me) != environment(victim))
        {
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        my = me->query_entire_dbase();
        your = victim->query_entire_dbase();

        if (! (my_temp = me->query_entire_temp_dbase()))
                my_temp = allocate_mapping(5);

        if (! (your_temp = victim->query_entire_temp_dbase()))
                your_temp = allocate_mapping(5);

        //
        // (0) Choose skills.
        //
        prepare = me->query_skill_prepare();
        if (! prepare) prepare = ([]);

        if (objectp(weapon))
                attack_skill = weapon->query("skill_type");
        else
        {
                switch (sizeof(prepare))
                {
                case 0: attack_skill = "unarmed"; break;
                case 1: attack_skill = (keys(prepare))[0]; break;
                case 2: attack_skill = (keys(prepare))[me->query_temp("action_flag")]; break;
                }
        }

        if (attack_skill == "pin")
                // the pin skill will the same as the sword skill,
                // why don't I remove pin skill ? because I don't
                // combatd, they as same.
                attack_skill = "sword";

        //
        // (1) Find out what action the offenser will take.
        //
        me->reset_action();
        action = me->query_action();

        if (! action)
        {
                // reconfirm
                me->reset_action();
                action = me->query_action();
                if (! mapp(action))
                {
                        CHANNEL_D->do_channel( this_object(), "sys",
                                sprintf("%s(%s): bad action = %O",
                                        me->query("name"), me->query("id"),
                                        me->query_action(1)));
                        return 0;
                }
        }

        if (me->query_temp("action_flag") == 0)
                result = "\n" + action["action"] + "！\n";
        else
                result = "\n紧跟着" + action["action"] + "！\n";

        // 判断攻击部位
        //
        // (2) Prepare AP, DP for checking if hit.
        //
        /* 此设置可以使一些武功选择使用此武功的人的攻击部位。
         * 可以产生例如地趟刀法专攻下三路的效果。
         * 不过增加不少系统开销。
         */
        if (martial_skill = me->query_skill_mapped(attack_skill))
                limb = SKILL_D(martial_skill)->query_attack_limb(me,victim);

        if (! limb)
        {
                limbs = victim->query("limbs");
                if (! arrayp(limbs))
                {
                        limbs = ({ "身体" });
                        victim->set("limbs", limbs);
                }
                limb = limbs[random(sizeof(limbs))];

        }

        if (victim->in_array() &&
            victim->query_array_status() &&
            (random(100) < (victim->query_array_level() / 100 + 40)))
        {
                object ob;

                if (((your["qi"] < your["max_qi"] * 2 / 5) ||
                    (your["jing"] < your["max_jing"] * 2 / 5)) &&
                    objectp(ob = victim->query_array_obstructor()) &&
                    ! ob->is_busy() && ! ob->is_fighting())
                {
                        result = replace_string(result, "$l", limb);
                        if (objectp(weapon))
                                result = replace_string(result, "$w", weapon->name());
                        else if (stringp(action["weapon"]))
                                result = replace_string(result, "$w", action["weapon"]);
                        else if (attack_skill == "finger" || attack_skill == "hand")
                                result = replace_string(result, "$w", "手指" );
                        else if (attack_skill == "strike" || attack_skill == "claw")
                                result = replace_string(result, "$w", "手掌" );
                        else    result = replace_string(result, "$w", "拳头" );

                        message_combatd(result, me, victim);
                        message_combatd(HIC BWHT "$N飞身移步，挡在了$n的身前。\n" NOR, ob, victim);
                        result = "";

                        victim = ob;
                        array_flag = 1;
                        attack_type = TYPE_QUICK;
                }
        }

        if (! my["not_living"])
        {
                fight = allocate_mapping(5);
                if (att = SKILLS_D->skill_query_power(martial_skill))
                {

                        fight["attack"] = atoi(att[ATTACK]);
                        fight["dodge"]  = atoi(att[DODGE]);
                        fight["parry"]  = atoi(att[PARRY]);


                }
                else
                {
                        fight["attack"] = action["attack"];
                        fight["dodge"]  = action["dodge"];
                        fight["parry"]  = action["parry"];
                }
                my_temp["fight"] = fight;
        }

#ifdef LONELY_IMPROVED
        apo = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
        if (arrayp(att) && sizeof(att))
                apo = count_add(apo, count_mul(count_div(apo, 500), att[ATTACK]));

        apo = count_div(apo, 10000);
        ap = atoi(apo);
#else
        ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
        if (arrayp(att) && sizeof(att))
                ap += ap / 500 * (int)att[ATTACK];
#endif
        if (cost = sizeof(me->query_enemy()) > 1)
        {
                if (cost > 6) cost = 6;
                ap /= cost;
        }

        if (! me->visible(victim))
                ap /= 10;

        if (member_array(limb, danger_limbs) != -1) /* 向危险部位发动进攻 */
                ap -= ap / 10;  /* 击中的可能性减小10% */

        if (ap < 1) ap = 1;

        if (my["character"] == "阴险奸诈")
                ap += ap * 20 / 100;

        if (! array_flag)
        {
#ifdef LONELY_IMPROVED
                dpo = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
                if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                        dpo = count_add(dpo, count_mul(count_div(dpo, 100), SKILL_D(dodge_skill)->query_effect_dodge(me, victim)));

                dpo = count_div(dpo, 10000);
                dp = atoi(dpo);
#else
                dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
                if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                        dp += dp / 100 * SKILL_D(dodge_skill)->query_effect_dodge(me, victim);
#endif
                if (arrayp(att) && sizeof(att))
                        dp -= dp * (int)att[DODGE] / 500;
                if (cost = sizeof(victim->query_enemy()) > 1)
                {
                        if (cost > 6) cost = 6;
                        dp /= cost;
                }
                if (dp < 1) dp = 1;

                if (! victim->visible(me))
                        dp /= 10;

                if (victim->is_busy()) dp /= 3;

        } else dp = 0;
        //
        // (3) Fight!
        //     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
        //     AP and DP are greater than zero, so we always have chance to hit
        //     or be hit.
        //
        damage = 0;
        wounded = 0;
        damage_info = "";

        if (random(ap + dp) < dp)
        {  // Does the victim dodge this hit?
#if INSTALL_COMBAT_TEST
                if (wizardp(me) && me->query("env/combat_test"))
                        tell_object(me, HIY "【测试精灵】：己方 AP：" + ap +
                                    "，DP：" + dp + "。\n" NOR);
                if (wizardp(victim) && victim->query("env/combat_test"))
                        tell_object(victim, HIC "【测试精灵】：对方 AP：" + ap +
                                    "，DP：" + dp + "。\n" NOR);
#endif
                if (! dodge_skill) dodge_skill = "dodge";
                result += SKILL_D(dodge_skill)->query_dodge_msg(limb);

                if (dp < ap && (! userp(victim) || ! userp(me)))
                {
#ifdef LONELY_IMPROVED
                        if (count_lt(your["combat_exp"], EXP_LIMIT))
                        {
                                your["combat_exp"] = count_add(your["combat_exp"], victim->query_int() / 10);
#else
                        if (random(your["combat_exp"]) < EXP_LIMIT && random(5))
                        {
                                your["combat_exp"] += victim->query_int() / 10;
#endif
                                victim->improve_skill("dodge", 1);
                        }
                }
        } else
        {
                //
                //      (4) Check if the victim can parry this attack.
                //
                if (! userp(me) || ! userp(victim))
                {
                        if (ap < dp && random(my["int"]) > 8)
                        {
#ifdef LONELY_IMPROVED
                                if (count_lt(my["potential"], me->query_potential_limit()))
                                        my["potential"] = count_add(my["potential"], 2);
#else
                                if (my["potential"] < me->query_potential_limit())
                                        my["potential"]++;
#endif
                                me->improve_skill(attack_skill, 1);
                        }
                }
                delta = 0;
                if (weapon2 = your_temp["weapon"])
                {
                        if (! weapon) delta = 10;
                } else
                {
                        if (weapon) delta = -10;
                }
#ifdef LONELY_IMPROVED
                ppo = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
                if (stringp(parry_skill = victim->query_skill_mapped("parry")))
                        ppo = count_add(ppo, count_mul(count_div(ppo, 100), SKILL_D(parry_skill)->query_effect_parry(me, victim)));

                ppo = count_div(ppo, 10000);
                pp = atoi(ppo);
#else
                pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
                if (stringp(parry_skill = victim->query_skill_mapped("parry")))
                        pp += pp / 100 * SKILL_D(parry_skill)->query_effect_parry(me, victim);
#endif
                if (arrayp(att) && sizeof(att))
                        pp -= pp * (int)att[PARRY] / 500;

                if (cost > 1) pp /= cost;

                if (victim->is_busy()) pp /= 3;
                if (pp < 1) pp = 1;

                if (random(ap + pp) < pp)
                {
#if INSTALL_COMBAT_TEST
                        if (wizardp(me) && me->query("env/combat_test"))
                                tell_object(me, HIY "【测试精灵】：己方 AP：" + ap +
                                            "，PP：" + pp + "。\n" NOR);
                        if (wizardp(victim) && victim->query("env/combat_test"))
                                tell_object(victim, HIC "【测试精灵】：对方 AP：" + ap +
                                            "，PP：" + pp + "。\n" NOR);
#endif
                        if (! parry_skill) parry_skill = "parry";
                        // change to SKILL_D(parry_skill) after added parry msg to those
                        // martial arts that can parry.
                        parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);

                        if (! stringp(parry_msg))
                                parry_msg = SKILL_D("parry")->query_parry_msg(weapon2);

                        if (stringp(parry_msg))
                                result += parry_msg;

                        if (pp < ap && (! userp(victim) || ! userp(me)))
                        {
#ifdef LONELY_IMPROVED
                                if (count_lt(your["combat_exp"], EXP_LIMIT))
                                {
                                        your["combat_exp"] = count_add(your["combat_exp"], victim->query_int() / 10);
#else
                                if (random(your["combat_exp"]) < EXP_LIMIT && random(5))
                                {
                                        your["combat_exp"] += victim->query_int() / 10;
#endif
                                        victim->improve_skill("parry", 1);
                                }
                        }
                } else
                {
                        //
                        //      (5) We hit the victim and the victim failed to parry
                        //
                        attack = 1;

                        if (weapon)
                                damage = me->query_temp("apply/damage");
                        else
                                damage = me->query_temp("apply/unarmed_damage");
                        // Added by Lonely
                        damage += (int)me->query_skill(attack_skill, 1) / 10;
                        damage = (damage + random(damage)) / 2;
                        if (arrayp(att) && sizeof(att))
                                damage += (int)att[DAMAGE] * damage / 50;
                        else
                        if (action["damage"])
                                damage += action["damage"] * damage / 100;

                        // damage_bonus = me->query_str() / 10;
                        damage_bonus = me->query_str();
                        if (my["jianu"])
                        {
                                // does angry bnous
                                damage_bonus += me->cost_craze(my["jianu"]);
                                if (me->query_craze() > 1000 &&
                                    random(my["jianu"] + 200) > 200)
                                {
                                        damage_info += random(2) ? HIR "$N" HIR "大喝一声，双目圆睁，一股凌厉的杀气油然而起！\n" NOR
                                                                 : HIR "$N" HIR "奋不顾身的扑上前来，招招紧逼$n" HIR "，毫不容情。\n" NOR;
                                        me->cost_craze(200 + random(300));
                                        damage_bonus += my["jianu"] * 2;
                                }
                        }

                        // Clear the special message info after damage info
                        foo_before_hit = 0;
                        foo_after_hit = 0;

                        // Let force skill take effect.
                        if (my["jiali"] && (my["neili"] > my["jiali"]))
                        {
                                // avoid = victim->query_temp("apply/avoid_attack");
                                if (force_skill = me->query_skill_mapped("force"))
                                {
                                        foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage_bonus += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
#if INSTALL_COMBAT_TEST
                                if (wizardp(me) && me->query("env/combat_test"))
                                        tell_object(me, HIY "【测试精灵】：己方 AP：" + ap +
                                                    "，DP：" + dp + "，PP：" + pp +
                                                    "，伤害效果：" + damage +
                                                    "，额外伤害效果：" + damage_bonus + "。\n" NOR);
                                if (wizardp(victim) && victim->query("env/combat_test"))
                                        tell_object(victim, HIC "【测试精灵】：对方 AP：" + ap +
                                                    "，DP：" + dp + "，PP：" + pp +
                                                    "，伤害效果：" + damage +
                                                    "，额外伤害效果：" + damage_bonus + "。\n" NOR);
#endif
                        }

                        if (arrayp(att) && sizeof(att))
                                damage_bonus += (int)att[FORCE1] * damage_bonus / 50;
                        else
                        if (action["force"])
                                damage_bonus += action["force"] * damage_bonus / 100;

                        // calculate the damage
                        if (damage_bonus > 0)
                                damage += (damage_bonus + random(damage_bonus)) / 3;

                        // Let's attack & parry skill, weapon & armor do effect
                        while (damage > 0)
                        {
                                if (my["not_living"] || your["not_living"])
                                        // Only two living do this
                                        break;

                                if (damage < 1) break;

                                // Let parry skill take its special effort.
                                avoid = me->query_temp("apply/avoid_dodge");
                                if (random(100) >= avoid && random(5) &&
                                    stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                                {
                                        // 应该是先判断def后判断foo的
                                        if (def = SKILLS_D->skill_query_power(dodge_skill))
                                        {
                                                if (! sizeof(att) ||
                                                    (int)att[ATTACK] - (int)def[DODGE] < 50)
                                                {
                                                        foo = SKILL_D(dodge_skill)->valid_damage(me, victim, damage, weapon);
                                                        if (stringp(foo)) damage_info += foo; else
                                                        if (intp(foo)) damage += foo; else
                                                        if (mapp(foo))
                                                        {
                                                                damage_info += foo["msg"];
                                                                damage += foo["damage"];
                                                        }
                                                }
                                        }
                                        if (damage < 1) break;
                                }

                                avoid = me->query_temp("apply/avoid_parry");
                                if (random(100) >= avoid && random(5) &&
                                    stringp(parry_skill = victim->query_skill_mapped("parry")) &&
                                    ! me->query("special_skill/drift"))
                                {
                                        if (def = SKILLS_D->skill_query_power(parry_skill))
                                        {
                                                if (! sizeof(att) ||
                                                    (int)att[ATTACK] - (int)def[PARRY] < 50)
                                                {
                                                        foo = SKILL_D(parry_skill)->valid_damage(me, victim, damage, weapon);
                                                        if (stringp(foo)) damage_info += foo; else
                                                        if (intp(foo)) damage += foo; else
                                                        if (mapp(foo))
                                                        {
                                                                damage_info += foo["msg"];
                                                                damage += foo["damage"];
                                                        }
                                                }
                                        }
                                        if (damage < 1) break;
                                }

                                /*
                                // 魔幻兽
                                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["beast"]))
                                {
                                        foo = cloth->valid_damage(me, victim, damage, weapon);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else
                                */
                                // Let armor/cloth take its special effort
                                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["armor"]))
                                {
                                        foo = cloth->valid_damage(me, victim, damage, weapon);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else
                                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["cloth"]))
                                {
                                        foo = cloth->valid_damage(me, victim, damage, weapon);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                if (damage < 1) break;

                                // Let attack skill take its special effort.
                                avoid = victim->query_temp("apply/avoid_attack");
                                if (random(100) >= avoid && random(5) &&
                                    stringp(martial_skill = me->query_skill_mapped(attack_skill)) &&
                                    sizeof(att) && (int)att[ATTACK] > 150)
                                {
                                        foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                        if (damage < 1) break;
                                }

                                // Let weapon or living have their special damage.
                                if (weapon)
                                {
                                        foo = weapon->hit_ob(me, victim, damage);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else
                                {
                                        foo = me->hit_ob(me, victim, damage);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                // finish
                                break;
                        }

                        //
                        //      (6) Inflict the damage.
                        //

#if INSTALL_COMBAT_TEST
                        if (wizardp(me) && me->query("env/combat_test"))
                                tell_object(me, HIY "【测试精灵】：你对" +
                                            victim->query("name") + "造成" +
                                            damage + "点伤害。\n" NOR);
                        if (wizardp(victim) && victim->query("env/combat_test"))
                                tell_object(victim, HIG "【测试精灵】：你受到" +
                                            me->query("name") + damage + "点伤害。\n" NOR);
#endif

                        if (damage > 0)
                        {
                                if (my["character"] == "心狠手辣")
                                        damage += damage * 20 / 100;

                                // calculate wounded
                                wounded = damage;
                                if (mapp(your_temp["apply"]) && your_temp["apply"]["armor"] > 0)
                                        wounded -= random(your_temp["apply"]["armor"]);

                                if (wounded > 800)
                                        wounded = (wounded - 800) / 8 + 400;
                                else
                                if (wounded > 400)
                                        wounded = (wounded - 400) / 4 + 300;
                                else
                                if (wounded > 200)
                                        wounded = (wounded - 200) / 2 + 200;
                                else
                                if (wounded < 1)
                                        wounded = 0;

                                // recalculate damage
                                if (damage > 800)
                                        damage = (damage - 800) / 8 + 400;
                                else
                                if (damage > 400)
                                        damage = (damage - 400) / 4 + 300;
                                else
                                if (damage > 200)
                                        damage = (damage - 200) / 2 + 200;

                                if (your["character"] == "光明磊落")
                                        wounded -= wounded * 20 / 100;

                                damage = victim->receive_damage("qi", damage, me);
                                if (wounded > 0 &&
                                    ((me->is_killing(your["id"]) && random(3) == 1) ||
                                     random(3) == 1))
                                {
                                        // We are sure that damage is greater than victim's armor here.
                                        victim->receive_wound("qi", wounded, me);
                                }

                                // add message before hit in victim
                                if (foo_before_hit)
                                        result += foo_before_hit;

                                result += damage_msg(damage, action["damage_type"]);
                                damage_desc = WHT "( 你的攻击给" + victim->query("name") + "造成 " + NOR + WHT + damage + NOR + WHT " 点伤害值。)\n" NOR;

                                damage_info += "( $n" +
                                        status_msg(victim->query("qi") * 100 /
                                        (victim->query("max_qi") ? victim->query("max_qi") : 100)) + ")\n";
                        }

                        if (foo_after_hit)
                                damage_info += foo_after_hit;
                }
        }

        result = replace_string(result, "$l", limb);
        if (objectp(weapon))
                result = replace_string(result, "$w", weapon->name());
        else if (stringp(action["weapon"]))
                result = replace_string(result, "$w", action["weapon"]);
        else if (attack_skill == "finger" || attack_skill == "hand")
                result = replace_string(result, "$w", "手指" );
        else if (attack_skill == "strike" || attack_skill == "claw")
                result = replace_string(result, "$w", "手掌" );
        else    result = replace_string(result, "$w", "拳头" );

        message_combatd(result, me, victim, damage_info);
        if (damage_desc) tell_object(me, damage_desc);

        if (damage > 0)
        {
                if (victim->is_busy()) victim->interrupt_me(me, 16 + random(8));
                if ((! me->is_killing(your["id"])) &&
                    (! victim->is_killing(my["id"])) &&
                    ! victim->query("not_living") &&
                    your["qi"] * 3 <= your["max_qi"])
                {
                        me->remove_enemy(victim);
                        victim->remove_enemy(me);
                        message_vision(winner_msg[random(sizeof(winner_msg))],
                                       me, victim);
                        if (me == victim->query_competitor())
                        {
                                me->win();
                                victim->lost();
                        }
                }
        }

        if (functionp(action["post_action"]))
                evaluate(action["post_action"], me, victim, weapon, damage);

        if (attack == 1 && damage > 0)
        {
                int pers;
                switch(limb)
                {
                        // 头、颈受伤会伤一些神。
                        case "头部":
                        case "颈部":
                                damage /= 4;
                                if (damage < 1)
                                        damage = 1;
                                if (damage > 80)
                                        damage = 80;
                                victim->receive_damage("jing", damage, me );
                                pers = victim->query("jing")*100/victim->query("max_jing");
                                if (pers <= 30)
                                        tell_object(victim, head_damage_me_msg[2]);
                                else if (pers <= 70)
                                        tell_object(victim, head_damage_me_msg[1]);
                                else
                                        tell_object(victim, head_damage_me_msg[0]);
                                break;
                        // 击中这些部位真气会受到振荡。
                        case "胸口":
                        case "后心":
                        case "小腹":
                                if (victim->query("max_neili") && victim->query("neili"))
                                {
                                        string report_limb_msg;

                                        damage /= 4;
                                        if (damage < 1)
                                                damage = 1;
                                        if (damage > 100)
                                                damage = 100;
                                        if (victim->query("neili") <= damage)
                                                victim->set("neili", 0);
                                        else
                                                victim->add("neili", -damage);
                                        if (damage <= 20)
                                                report_limb_msg = body_damage_me_msg[0];
                                        else if (damage <= 100)
                                                report_limb_msg = body_damage_me_msg[1];
                                        else
                                                report_limb_msg = body_damage_me_msg[2];
                                        report_limb_msg = replace_string(report_limb_msg, "$l", limb);
                                        tell_object(victim, report_limb_msg);
                                }
                                break;
                }
        }

        // See if the victim can make a riposte.
        if (attack_type == TYPE_REGULAR &&
            damage < 1 &&
            your_temp["guarding"])
        {
               // your_temp["guarding"];
                if (random(my["dex"]) < 5)
                {
                        message_combatd("$N一击不中，露出了破绽！\n",
                                        me, 0, "");
                        do_attack(victim, me, your["weapon"],
                                  TYPE_QUICK);
                } else
                {
                        message_combatd("$N见$n攻击失误，趁机发动攻击！\n",
                                        victim, me, "");
                        do_attack(victim, me, your_temp["weapon"],
                                  TYPE_RIPOSTE);
                }
        }
}

// do damage when perform
// I will consider the damage of the weapon
// what is final: final may be a function with result type string,
// or a single string.
// The syntax of the final string is info:damage_type@limb or info only,
// If the limb if ?, the system will auto select limb of
// target, if the final is a single string, the system will
// treat as damage infomation.
varargs string do_damage(object me, object target, mixed type,
                         int damage, int percent, mixed final)
{
        mapping my;
        object weapon;
        object cloth;
        int apply;
        int armor;
        int wound;
        int jiali;
        //int bonus;
        mixed foo;
        string msg;
        string skill;
        string *limbs;
        string limb;
        string damage_type;
        string result;
        int str;
        int damage_bonus;
        mapping prepare;
        string attack_skill;
        string *att, *def;      
        int avoid;

        if (environment(me) != environment(target))
        {
                me->remove_enemy(target);
                target->remove_enemy(me);
                return "";
        }

        // Am I use weapon
        if (type == WEAPON_ATTACK)
        {
                apply  = me->query_temp("apply/damage");
                weapon = me->query_temp("weapon");
        } else
        if (type == UNARMED_ATTACK)
        {
                apply  = me->query_temp("apply/unarmed_damage");
                weapon = 0;
        } else
        {
                apply  = 0;
                weapon = 0;
        }

        prepare = me->query_skill_prepare();
        if (! prepare) prepare = ([]);

        if (weapon)
                skill = weapon->query("skill_type");
        else
        {
                switch (sizeof(prepare))
                {
                case 0: skill = "unarmed"; break;
                case 1:
                case 2: skill = (keys(prepare))[0]; break;
                }
        }

        if (skill == "pin") skill = "sword";

        attack_skill = me->query_skill_mapped(skill);
        if (SKILLS_D->skill_query_power(attack_skill))
                att = SKILLS_D->skill_query_power(attack_skill);

        // Check the target's armor
        armor = target->query_temp("apply/armor");

        damage += apply;
        msg = "";
        foo_after_hit = 0;

        while (type == UNARMED_ATTACK || type == WEAPON_ATTACK)
        {
                avoid = me->query_temp("apply/avoid_parry");
                // Let parry skill take its special effort
                if (random(100) >= avoid && random(5) &&
                    stringp(skill = target->query_skill_mapped("parry")) &&
                    ! me->query("special_skill/drift"))
                {
                        if (def = SKILLS_D->skill_query_power(skill))
                        {        
                                if (! sizeof(att) ||
                                    (int)att[ATTACK] - (int)def[PARRY] < 50)
                                {                        
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                        if (stringp(foo)) msg += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                msg += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }
                        }
                }

                avoid = me->query_temp("apply/avoid_dodge");
                // Let dodge skill take its special effort
                if (random(100) > avoid && random(5) &&
                    stringp(skill = target->query_skill_mapped("dodge")))
                {
                        if (def = SKILLS_D->skill_query_power(skill))
                        {
                                if (! sizeof(att) ||
                                    (int)att[ATTACK] - (int)def[DODGE] < 50)
                                {                        
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                        if (stringp(foo)) msg += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                msg += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }
                        }
                }

                if (damage < 1) break;

                /*
                // 魔幻兽
                if (cloth = target->query_temp("armor/beast"))
                {
                        foo = cloth->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } else
                */
                // Let cloth & armor take its special effort
                if (cloth = target->query_temp("armor/armor"))
                {
                        foo = cloth->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } else
                if (cloth = target->query_temp("armor/cloth"))
                {
                        foo = cloth->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                }

                // Finish
                break;
        }

        while (damage > 0)
        {
                if (target->is_busy()) target->interrupt_me(target, 6 + random(6));

                // Let weapon/unarmed attack take its special effort
                if (type == WEAPON_ATTACK && objectp(weapon))
                        // weapon attack
                        foo = weapon->hit_ob(me, target, damage);
                else
                if (type == UNARMED_ATTACK)
                        // unarmed attack
                        foo = me->hit_ob(me, target, damage);
                else
                if (objectp(type))
                        // special item attack
                        foo = type->hit_ob(me, target, damage);

                if (stringp(foo)) msg += foo; else
                if (intp(foo)) damage += foo; else
                if (mapp(foo))
                {
                        msg += foo["msg"];
                        damage += foo["damage"];
                }

                // do enforce effect
                my = me->query_entire_dbase();
                if ((jiali = my["jiali"]) > 0 && my["neili"] >= jiali)
                {
                        // eforced
                        my["neili"] -= jiali;
                        if (type == REMOTE_ATTACK)
                        {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);
                        } else
                        {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);

                                // check special force effort
                                skill = target->query_skill_mapped("force");
                                if (stringp(skill))
                                {
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage_bonus);
                                        if (stringp(foo)) msg += foo; else
                                        if (intp(foo)) damage_bonus += foo; else
                                        if (mapp(foo))
                                        {
                                                msg += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }
                        damage += damage_bonus;
                }

                // do strength effect
                str = me->query_str() + me->query_temp("str");
                if (str < 20)
                        damage += damage * str / 50;
                else
                if (str < 40)
                        damage += damage * ((str - 20) / 2 + 20) / 50;
                else
                if (str < 80)
                        damage += damage * ((str - 40) / 4 + 30) / 50;
                else
                        damage += damage * ((str - 80) / 8 + 40) / 50;

                if (damage < 1) break;

                // recalculate damage
                if (damage > 4500) 
                        damage = (damage - 4500) / 8 + 1500; 
                else
                if (damage > 1500)
                        damage = (damage - 1500) / 4 + 1000;
                else
                if (damage > 500)
                        damage = (damage - 500) / 2 + 500;

                // do damage
                target->receive_damage("qi", damage, me);
                wound = (damage - random(armor)) * percent / 100;
                if (target->query("character") == "光明磊落")
                        wound -= wound * 20 / 100;
                if (wound > 0) target->receive_wound("qi", wound, me);

                if (functionp(final)) final = evaluate(final);
                if (stringp(final))
                {
                        if (sscanf(final, "%s@%s", final, limb) == 2)
                        {
                                if (sscanf(final, "%s:%s", result, damage_type) != 2)
                                {
                                        result = HIR "这招打了个正中！";
                                        damage_type = final;
                                }
                                if (sscanf(limb, "?%*s"))
                                {
                                        // auto select limb
                                        limbs = target->query("limbs");
                                        if (! arrayp(limbs))
                                        {
                                                limbs = ({ "身体" });
                                                target->set("limbs", limbs);
                                        }
                                        limb = limbs[random(sizeof(limbs))];
                                }

                                // indicate damage type & limb
                                final = replace_string(damage_msg(damage, damage_type), "$l", limb);
                                final = replace_string(final, "$n", "$n" HIR);
                                final = replace_string(final, "$N", "$N" HIR);
                                final = replace_string(final, "$p", "$p" HIR);
                                final = replace_string(final, "$P", "$P" HIR);
                                if (weapon)
                                        final = replace_string(final, "$w", weapon->name() + HIR);
                                final = result + HIR + final + NOR;
                        }

                        msg += final;
                        msg += "( $n" + status_msg(target->query("qi") * 100 / (target->query("max_qi") ?
                                                   target->query("max_qi") : 100)) + ")\n";
                }
                msg += WHT "( $N的攻击给$n造成 " + NOR + WHT + damage + NOR + WHT " 点伤害值。)\n" NOR;
                break;
        }

        if (foo_after_hit) msg += foo_after_hit;
        if (foo_before_hit) msg = foo_before_hit + msg;
        // Clear the special message info after damage info
        foo_before_hit = 0;
        foo_after_hit = 0;

        return msg;
}

//      auto_perform()
//      自动出绝招
int auto_perform(object me, object target, string perform_skill)
{
        int l;
        string dir;
        string file;
        mixed *all_file;

        if (! stringp(dir = SKILL_D(perform_skill) + "/") ||
                file_size(dir) != -2)   // 这个武功没有绝招
                return 0;

        if (file_size(dir + "perform/") == -2)  // 这个武功有一个perform/子目录
        {
                all_file = get_dir(dir + "perform/");
                if (! sizeof(all_file))
                        all_file = get_dir(dir);
                else
                        dir += "perform/";
        }
        else
                all_file = get_dir(dir);

        if (! sizeof(all_file)) // 这个武功没有绝招
                return 0;

        all_file = filter_array(all_file,(:is_c_file($1):));     // 取出*.c文件
        if (! sizeof(all_file)) // 这个武功没有绝招
                return 0;

        file = all_file[random(sizeof(all_file))];      // 随机抽取武功的绝招
        l = strlen(file);
        file = dir + file[0..l-3];
        return (int)call_other(file, "perform", me, target);
}

//      fight()
//
//      This is called in the attack() defined in F_ATTACK, which handles fighting
//      in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
       // object ob;
        object weapon;
        string askill;
        int    double_attack;
        mapping prepare;
       // string result;
        mapping my_temp;
        int auto_pfm, can_auto_perform; // 自动PFM，add by smallfish
        string the_perform_skill, perform_skill_1, perform_skill_2;

        if (! living(me)) return;

        if (! me->visible(victim)) return;

        if (! mapp(my_temp = me->query_entire_temp_dbase()))
                my_temp = ([ ]);

        auto_pfm = 0;

        if (me->query("auto_perform"))
                auto_pfm = me->query("auto_perform");
        else
                auto_pfm = me->query_auto_perform();

        if (auto_pfm < 0) auto_pfm = 0;
        if (auto_pfm > 10) auto_pfm = 10;

        prepare = me->query_skill_prepare();
        if (weapon = my_temp["weapon"])
                askill = weapon->query("skill_type");
        else if (! prepare || sizeof(prepare) == 0) askill = "unarmed";
        else if (sizeof(prepare)) askill = (keys(prepare))[0];
        if (askill == "pin") askill = "sword";

        askill = me->query_skill_mapped(askill);
        // 下面是自动pfm的程序段
        // 如果auto_perform为1,表示任何时候都以发出绝招为主
        // 如果auto_perform大于1,表示以 1/auto_perform 的概率发出绝招
        if (auto_pfm == 1 || (random(auto_pfm) == 1))
        {
                can_auto_perform = 0;
                if (askill)
                {
                        perform_skill_1 = askill;       // 第一种pfm;
                        can_auto_perform = 1;
                }
                // 如果没有装备兵器，而且空手武功bei了不止一种，那么取第二种bei的空手武功的绝招为第二种pfm;
                if (! weapon && prepare && sizeof(prepare) > 1)
                        perform_skill_2 = me->query_skill_mapped((keys(prepare))[1]);

                if (perform_skill_2) can_auto_perform = 2;

                if (can_auto_perform == 1)
                        auto_perform(me, victim, perform_skill_1);
                else if (can_auto_perform == 2)
                {
                        // 随机选择两种PFM
                        if (random(2))
                                the_perform_skill = perform_skill_1;
                        else
                                the_perform_skill = perform_skill_2;

                        if (! auto_perform(me, victim, the_perform_skill))
                                auto_perform(me, victim, (the_perform_skill == perform_skill_1) ?
                                                        perform_skill_2 : perform_skill_1);
                }
        }       // 自动PFM程序段结束，下面进入正常的战斗判断

        if (! objectp(me) || ! objectp(victim)) return;

        if (me->is_busy() || me->is_p_busy()) return;  // 使用了PFM后可能会出现忙，那么终止这次的战斗

        if (askill && random(me->query_dex()) >= 8)
                double_attack = (sizeof(prepare) >= 2 && ! weapon) ||
                        SKILL_D(askill)->double_attack();

        // If victim is busy or unconcious, always take the chance to make an attack.
        if (victim->is_busy() || ! living(victim))
        {
                me->set_temp("guarding", 0);
                if (! victim->is_fighting(me)) victim->fight_ob(me);
                do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);

                if (me->is_fighting(victim) && victim->is_fighting(me) && double_attack)
                {
                        me->set_temp("action_flag",1);
                        do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);
                        me->set_temp("action_flag",0);
                }

        // Else, see if we are brave enough to make an aggressive action.
        } else
        if (me->query_str() > random(victim->query_str() * 3 / 4))
        {
                me->set_temp("guarding", 0);
                if (! victim->is_fighting(me))
                        victim->fight_ob(me);
                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);

                if (me->is_fighting(victim) && victim->is_fighting(me) && double_attack)
                {
                        me->set_temp("action_flag",1);
                        do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);
                        me->set_temp("action_flag",0);
                }

        // Else, we just start guarding.
        } else
        if (! me->query_temp("guarding"))
        {
                me->set_temp("guarding", 1);
                message_combatd( guard_msg[random(sizeof(guard_msg))], me, victim, "");
                return;
        } else return;
}

//      auto_fight()
//
//      This function is to start an automatically fight. Currently this is
//      used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
        // Don't let NPC autofight NPC.
        if (! userp(me) && ! userp(obj)) return;

        if (me->query_temp("owner") == obj ||
            obj->quety_temp("owner") == me)
                return;

        // Because most of the cases that we cannot start a fight cannot be checked
        // before we really call the kill_ob(), so we just make sure we have no
        // aggressive callout wating here.
        if (me->query_temp("looking_for_trouble")) return;
        me->set_temp("looking_for_trouble", 1);

        // This call_out gives victim a chance to slip trough the fierce guys.
        call_out("start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
        int shen;

        // Are we still exist( not becoming a corpse )?
        if (! me || ! obj || ! living(me)) return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me)!=environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        shen = 0 - (int)me->query("shen");
        message_vision("$N用一种异样的眼神扫视著在场的每一个人。\n", me);

        if (! userp(me) || (int)me->query("neili") > (random(shen) + shen)/10 )
                return;

        /*
        if (shen > (int)me->query("score") && ! wizardp(obj))
        {
                message_vision("$N对著$n喝道：" + RANK_D->query_self_rude(me)
                        + "看你实在很不顺眼，去死吧。\n", me, obj);
                me->kill_ob(obj);
        } else
        */
        {
                message_vision("$N对著$n喝道：喂！" + RANK_D->query_rude(obj) +
                               "，" + RANK_D->query_self_rude(me) +
                               "正想找人打架，陪我玩两手吧！\n",
                               me, obj);
                me->fight_ob(obj);
        }
}

void start_hatred(object me, object obj)
{
        if (! me || ! obj || ! living(me))
                return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me) != environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        if (me->query_temp("owner") == obj->query("id") ||
            obj->query_temp("owner") == me->query("id"))
                return;

        // We found our hatred! Charge!
        if ( me->query("race") == "人类" )
                message_vision( catch_hunt_human_msg[random(sizeof(catch_hunt_human_msg))], me, obj);
        if ( me->query("race") == "野兽" )
                message_vision( catch_hunt_beast_msg[random(sizeof(catch_hunt_beast_msg))], me, obj);
        if ( me->query("race") == "飞禽" )
                message_vision( catch_hunt_bird_msg[random(sizeof(catch_hunt_bird_msg))], me, obj);
        me->want_kill(obj);
        me->kill_ob(obj);

        if (! playerp(me) && me->is_busy() && ! intp(me->query_busy()))
                me->interrupt_me(me);
}

void start_vendetta(object me, object obj)
{
        if (! me || ! obj || ! living(me))
                return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me) != environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        message_vision(HIC"$N怒道：帮主有令，见到$n格杀勿论！\n"NOR, me, obj);
        tell_object(obj, HIR "看起来" + me->name() + "想杀死你！\n" NOR);
        // We found our vendetta opponent! Charge!
        me->want_kill(obj);
        me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
        if (! me || ! obj || ! living(me)) return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me) != environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        // We got a nice victim! Kill him/her/it!!!
        me->want_kill(obj);
        me->kill_ob(obj);
}

int player_escape(object killer, object ob)
{
        //object iob;
        string msg;

        if (! objectp(ob))
                return 0;

        // 是玩家么？
        if (! playerp(ob))
                return 0;

        if ((int)ob->query("combat/which_day") == time() / 86400 &&
            (int)ob->query("total_count") > 0)
                return 0;

        // 真的晕倒了，察看是否是被别人有意打晕的
        if (! killer) killer = ob->query_defeated_by();
        if (! killer || ! playerp(killer) ||
            ! killer->is_want_kill(ob->query("id")))
                return 0;

#ifdef LONELY_IMPROVED
        if (ob->query("no_newbie") ||
            ob->query("combat/WPK") ||
            (ob->query("age") >= 20 &&
            count_ge(ob->query("combat_exp"), 20000000)))
#else
        if (ob->query("no_newbie") ||
            ob->query("combat/WPK") ||
            (ob->query("age") >= 20 &&
            ob->query("combat_exp") >= 20000000))
#endif
                return 0;

        switch (random(7))
        {
        case 0:
                msg = "突然只听幽幽一声长叹，一掌轻轻按来。$N大吃一惊，不及"
                      "多加思索，只是抬手一格。匆忙之间只怕对手过于厉害，难"
                      "以招架，急忙向后跃开。却见来人并不追击，只是一伸手拎"
                      "起$n，转身飘然而去，仙踪渺然。\n";
                break;

        case 1:
                msg = "$N将$n打翻在地，“哈哈”一声笑声尚未落下，只听有人冷"
                      "哼一声，忽然间掌风袭体，$N顿感呼吸不畅，几欲窒息，慌"
                      "忙中急忙退后，待得立稳脚跟，却见$n早已无影无踪。\n";
                break;

        case 2:
                msg = "一人忽然掠至，喝道：“岂有此理？我龙岛主最恨此欺善怕"
                      "恶之辈，休走！”说罢一掌击来，$N奋力招架，一招之下几"
                      "欲吐血！只见来人轻轻提起$n，冷笑两声，转身离去，$N惊"
                      "骇之下，竟然说不出一句话来。\n";
                break;

        case 3:
                msg = "突然一人喝道：“且慢！”只见一道黑影掠到，飞起一脚将"
                      "$N踢了个跟头，左手拎起$n，冷冷对$N道：“今日所幸尚未"
                      "伤人命，你作恶不甚，饶你去吧！”$N捂胸运气，不住喘息"
                      "，眼睁睁的看着来人去了。\n";
                break;

        case 4:
                msg = "$N跨前一步，忽然看到面前已多了两人，一胖一瘦，一喜一"
                      "怒，不由暗生疑窦。一人手中亮出一面铜牌，笑道：“这位" +
                      RANK_D->quert_respect(killer)+ "，这面罚恶铜牌你收下可"
                      "好？”$N听了大吃一惊，手只是一软，哪里还敢搭半句话？"
                      "那瘦子冷冷看了过来，目光如电，$N讪讪笑了两声，目送两"
                      "人带了$n逍遥而去。\n";

        case 5:
                msg = "恰在此时，正逢一老者路过，只见他微一颦眉，喝道：“兀"
                      "那" + RANK_D->query_rude(killer)+ "，伤人做甚？”$N大"
                      "怒道：“你是何人，如此嚣张？”老者大怒，一掌拍落，$N"
                      "向上只是一格，“噗噜”一下双腿陷入土中，足有半尺。老"
                      "者森然道：“我乃侠客岛木岛主是也，如有不服，恭候大驾"
                      "！”此时$N内息如狂，连句场面话也说不出来，只能眼看$n"
                      "被那木岛主带了离去。\n";
                break;

        default:
                msg = "忽听“哈哈”一阵长笑，一人道：“龙兄，想不到我们三十"
                      "年不履中土，这些武林高手却是越来越不长进了！”另一人"
                      "道：“正是，看来赏善罚恶，漫漫无期，终无尽头。”$N听"
                      "得大汗涔涔而下，环顾四方却无一人，转回头来，更是大吃"
                      "一惊！连$n也不见了。\n";
                break;
        }

        if ((environment(killer) == environment(ob)) &&
            killer->is_fighting(ob))
        {
                msg = replace_string(msg, "$n", ob->name());
                message_sort(msg, killer);
        } else
        {
                msg = "正逢一老者路过，见了" + ob->name() + "晕倒在地，叹口"
                      "气，将他扶起带走了。\n";
                message("vision", msg, environment(ob));
        }

        // 将身上带的东西放下
        /*
        foreach (iob in all_inventory(ob))
                if (! iob->query("money_id") &&
                    ! iob->query("equipped"))
                        iob->move(environment(ob));
        */

        // 初始化玩家的状态
        ob->clear_condition();
        ob->remove_killer(killer);
        killer->remove_killer(ob);

        ob->move("/d/xiakedao/shiroom24");
        ob->set("startroom", "/d/xiakedao/shiroom24");
        ob->revive();
        ob->set("eff_qi", ob->query("max_qi"));
        ob->set("eff_jing", ob->query("max_jing"));
        ob->set("qi", 0);
        ob->set("jing", 0);

        if (intp(ob->query_busy()))
                ob->start_busy(30);

        tell_object(ob, "你睁开眼来，看到两位老者正在静坐修炼。\n"
                    HIG "龙岛主告诉你：" + RANK_D->query_respect(ob) +
                        "，你要想离岛不妨和我说一声(ask long about 离岛)。\n" NOR);

        return 1;
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
    if (ob->query("race") == "人类")
    {
        switch (event)
        {
        case "dead":
                message_vision(NOR "\n$N扑在地上挣扎了几下，腿一伸，口中喷出几口"
                               HIR "鲜血" NOR "，死了！\n\n" NOR, ob);
                if (environment(ob) && userp(environment(ob)) && living(environment(ob)))
                        tell_object(environment(ob),NOR "\n" + ob->name() + "扑腾了几下，腿一伸，口中喷出几口"
                               HIR "鲜血" NOR "，死了！\n\n" NOR);
                break;

        case "unconcious":
                message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
                player_escape(0, ob);
                break;

        case "revive":
                message_vision("\n$N慢慢睁开眼睛，清醒了过来。\n\n", ob);
                break;
        }
    } else
    {
        switch(event)
        {
        case "dead":
                message_vision(ob->query("dead_message"), ob);
                break;
        case "unconcious":
                message_vision(ob->query("unconcious_message"), ob);
                break;
        case "revive":
                message_vision(ob->query("revive_message"), ob);
                break;
        }
    }
}

// called when winner hit the victim to unconcious
void winner_reward(object winner, object victim)
{
        object owner;
        int temp;
        int td;
        mapping today;

        owner = winner->query_temp("owner");
        if (objectp(owner))
                winner = owner;

        winner->defeated_enemy(victim);

        if (! playerp(winner) || wizardp(victim) && 0)
                return;

        if (! winner->is_want_kill(victim->query("id")))
                // only if I want kill ob, I will record it.
                return;

        winner->add("combat/DPS", 1);
        if (victim->is_not_bad())  winner->add("combat/DPS_NOTBAD", 1);
        if (victim->is_not_good()) winner->add("combat/DPS_NOTGOOD", 1);
        if (victim->is_bad())      winner->add("combat/DPS_BAD", 1);
        if (victim->is_good())     winner->add("combat/DPS_GOOD", 1);

        if (victim->query_condition("killer"))
                return;

        log_file("static/killrecord",
                 sprintf("%s %s defeat %s\n",
                         log_time(), log_id(winner), log_id(victim)));

        td = time() / 86400;
        today = winner->query("combat/today");
        if (! mapp(today) || today["which_day"] != td)
        {
                today = ([ "which_day" : td,
                           "total_count" : 1,
                           victim->query("id") : 1, ]);
        } else
        {
                // count how many times that winner hit the victim to unconcious
                temp = ++today[victim->query("id")];
                if (temp == query("pk_perman"))
                {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n今天你已经打晕" +
                                    victim->name() + chinese_number(temp) +
                                    "次了，手下留"
                                    "情吧，否则麻烦可要找上门了。\n" NOR);
                } else
                if (temp > query("pk_perman"))
                        // too many times
                        winner->set("combat/need_punish", "这厮逼人太甚，真是岂有此理！");

                // count how many users that winner hit to unconcious
                temp = ++today["total_count"];
                if (temp == query("pk_perday"))
                {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n今天你已经打晕" +
                                    chinese_number(temp) + "次玩家了，手下留"
                                    "情吧，否则麻烦可要找上门了。\n" NOR);
                } else
                if (temp > query("pk_perday"))
                        // too many users
                        winner->set("combat/need_punish", "丧尽天良，大肆屠戮，罪无可恕！");
        }
        winner->set("combat/today", today);
}

void family_kill(object killer, object victim)
{
        // 以下为门派功绩处理
        if (! objectp(killer) || ! userp(killer) ||
            ! objectp(victim) ||
            ! stringp(killer->query("family/family_name")))
                return;

        if (killer->query("family/family_name") !=
            victim->query("family/family_name"))
                return;

        // quest 任务
        if (stringp(killer->query("quest/id")) &&
            killer->query("quest/id") == victim->query("id"))
                return;

        // free 任务
        if (! userp(victim) && victim->query_temp("quest_ob"))
                return;

        // ultra 任务
        if (! userp(victim) && stringp(victim->query_temp("quester")) &&
            victim->query_temp("quester") == killer->query("id"))
                return;

        // ultra 任务
        if (! userp(victim) && (killer->query("quest_dg") ||
            killer->query("quest_hs") || killer->query("quest_sn") ||
            killer->query("quest_kh")))
                return;

        if (userp(victim))
        {
                killer->add("family/gongji", -500);
                tell_object(killer, sprintf("由于你残害同门弟子，师门功绩下降 %d 点。\n", 500));
        }
        else
        {
                if (killer->is_apprentice_of(victim))
                {
                        killer->add("family/gongji", -1000);
                        tell_object(killer,sprintf("由于欺师灭组的行为，师门功绩下降 %d 点。\n", 1000));
                }
                else
                if (killer->query("family/generation") >
                    victim->query("family/generation"))
                {
                        killer->add("family/gongji", -600);
                        tell_object(killer,sprintf("由于你残害同门尊长，师门功绩下降 %d 点。\n", 600));
                }
                else
                {
                        killer->add("family/gongji", -300);
                        tell_object(killer,sprintf("由于你残害同门，师门功绩下降 %d 点。\n", 300));
                }
        }
        if (killer->query("family/gongji") < 0)
                killer->set("family/gongji", 0);
}

void killer_reward(object killer, object victim)
{
        object owner;
        string vmark;
        string msg = "莫名其妙地死了";
        string follow_msg = 0;
        object weapon;
        mapping actions;
        int shen_delta,exp_damage;
        mixed exp_lost;
        mapping ks, vs, kcombat;
        int lost_die = 0;

        if (! objectp(victim))
                return;

        if (objectp(killer))
        {
                owner = killer->query_temp("owner");
                if (objectp(owner))
                        killer = owner;
        }

        // This while is only to enable "break"
        vs = victim->query_entire_dbase();
        while (1)
        {
                if (! objectp(killer))
                        break;

                // call the killer's override function
                killer->killed_enemy(victim);

                if (! objectp(killer) || ! playerp(killer))
                        break;

                // assure the killer's dbase
                ks = killer->query_entire_dbase();
                if (! mapp(kcombat = ks["combat"]))
                {
                        kcombat = ([ ]);
                        ks["combat"] = kcombat;
                }

                // adjust the "shen" & "experience" of the killer
#ifdef LONELY_IMPROVED
                if (count_lt(count_div(ks["combat_exp"], 2), vs["combat_exp"]))
                {
                        if (count_ge(ks["combat_exp"], 100000) &&
                            count_ge(ks["combat_exp"], count_div(count_mul(vs["combat_exp"], 2), 3)))
#else
                if (ks["combat_exp"]/2 < vs["combat_exp"])
                {
                        if (ks["combat_exp"] >= 100000 &&
                            ks["combat_exp"] >= vs["combat_exp"] * 2 / 3)
#endif
                        {
                                // adjust experience
                                if (! intp(ks["experience"]))
                                        ks["experience"] = 0;
                                killer->improve_experience(1 + random(5));
                        }

                        // adjust shen
                        shen_delta = -vs["shen"] / 2;
                        if (shen_delta > 100)
                        {
                                // 非线性校正获得的正神
                                shen_delta = (shen_delta - 100) / 3 + 100;

                                if (shen_delta > 200)
                                        shen_delta = (shen_delta - 200) / 3 + 200;

                                if (shen_delta > 300)
                                        shen_delta = (shen_delta - 300) / 3 + 300;
                        } else
                        if (shen_delta < -100)
                        {
                                // 非线性校正获得的负神
                                shen_delta = (shen_delta + 100) / 3 - 100;

                                if (shen_delta < -200)
                                        shen_delta = (shen_delta + 200) / 3 - 200;

                                if (shen_delta < -300)
                                        shen_delta = (shen_delta + 300) / 3 - 300;
                        }

                        ks["shen"] += shen_delta;
                }

                // weapon get the bonus
                if (weapon = killer->query_temp("weapon") ||
                    weapon = killer->query_temp("armor/hands"))
                        weapon->killer_reward(killer, victim);
                
                if (weapon = killer->query_temp("handing"))
                        weapon->killer_reward(killer, victim);
                        
                // record the user's killing
                if (userp(victim))
                {
                        if (! intp(kcombat["PKS"]))
                                kcombat["PKS"] = 1;
                        else
                                kcombat["PKS"]++;

                        killer->set("pktime", (int)killer->query("mud_age"));

                        // do family action
                        FAMILY_D->family_kill(killer, victim);

                        // do pvp action
                        // PVP_D->pvp_kill(killer, victim);

                        // do league action
                        LEAGUE_D->league_kill(killer, victim);

                        // do bunch action
                        BUNCH_D->bunch_kill(killer, victim);

                        if (victim->query_condition("killer"))
                        {
                                follow_msg = "听说杀人凶手" + victim->name(1) +
                                             "被" + killer->name(1) + "在" +
                                             environment(victim)->short() + HIM
                                             "就地正法了。";
                                break;
                        }

                        if (userp(killer) && killer->in_array() && killer->query_array_status())
                        {
                                follow_msg = sprintf("%s(%s)被%s(%s)带领的『%s』做掉啦！！\n",
                                                victim->name(1),
                                                capitalize(victim->query("id")),
                                                killer->query_array_master()->name(1),
                                                capitalize(killer->query_array_master()->query("id")),
                                                killer->query_array_name());
                                break;
                        }

                        if (userp(killer) && killer->in_team())
                        {
                                follow_msg = sprintf("%s(%s)被%s(%s)带领的队伍做掉啦！！\n",
                                                victim->name(1),
                                                capitalize(victim->query("id")),
                                                killer->query_team_leader()->name(1),
                                                capitalize(killer->query_team_leader()->query("id")));
                                break;
                        }

                        if (! killer->is_want_kill(vs["id"]))
                                break;

                        if (! intp(kcombat["WPK"]))
                                kcombat["WPK"] = 1;
                        else
                                kcombat["WPK"]++;

                        if (! killer->query_condition("killer"))
                        {
                                follow_msg = "听说官府发下海捕文书，缉拿杀人凶手" +
                                             killer->name(1) + "。";
                                killer->apply_condition("killer", 500);
                        } else
                        {
                                follow_msg = "听说官府加紧捉拿累犯重案的暴徒" +
                                             killer->name(1) + "。";
                                killer->apply_condition("killer", 800 +
                                        (int)killer->query_condition("killer"));
                        }

                        // assure data of kcombat
                        if (! intp(kcombat["WPK_NOTBAD"])) kcombat["WPK_NOTBAD"] = 0;
                        if (! intp(kcombat["WPK_NOTGOOD"])) kcombat["WPK_NOTGOOD"] = 0;
                        if (! intp(kcombat["WPK_GOOD"])) kcombat["WPK_GOOD"] = 0;
                        if (! intp(kcombat["WPK_BAD"])) kcombat["WPK_BAD"] = 0;

                        // record the combat info.
                        if (victim->is_not_bad())  kcombat["WPK_NOTBAD"]++;
                        if (victim->is_not_good()) kcombat["WPK_NOTGOOD"]++;
                        if (victim->is_good())     kcombat["WPK_GOOD"]++;
                        if (victim->is_bad())      kcombat["WPK_BAD"]++;
                        break;
                }

                if (vs["can_speak"])
                        if (! intp(kcombat["MKS"]))
                                kcombat["MKS"] = 1;
                        else
                                kcombat["MKS"]++;

                family_kill(killer, victim);
                check_quest(killer, victim);

                break;
        }

        // die penalty & message of victim
        if (playerp(victim))
        {
                // clear punish info.
                victim->delete("combat/need_punish");

                // clear all condition
                victim->clear_condition();

                // remove vendetta
                map_delete(vs, "vendetta");

                if (! killer ||
                    victim->query("no_newbie") ||
                    victim->query("combat/WPK") ||
                    (killer && ! playerp(killer)) ||
                    (killer && playerp(killer) &&
                    killer->query("age") > 19 &&
                    victim->query("age") > 19 &&
#ifdef LONELY_IMPROVED
                    count_gt(victim->query("combat_exp"), 20000000) &&
                    count_gt(killer->query("combat_exp"), 20000000)))
#else
                    victim->query("combat_exp") > 20000000 &&
                    killer->query("combat_exp") > 20000000))
#endif
                {
                        lost_die = 1;
                        // adjust shen
                        vs["shen"] -= vs["shen"] / 10;
                        if (vs["max_neili"] >= 20)
                                vs["max_neili"] -= 20;
                        else
                                vs["max_neili"] = 0;

                        // adjust combat exp.
                        if (!mapp(vs["combat"])) exp_damage = 1;
                        else exp_damage = vs["combat"]["WPK"];
                        if (exp_damage < 1) exp_damage = 1;
                        if (exp_damage > 5) exp_damage = 5;
#ifdef LONELY_IMPROVED
                        exp_lost = count_div(count_mul(vs["combat_exp"], exp_damage), 100);
                        vs["combat_exp"] = count_sub(vs["combat_exp"], exp_lost);
#else
                        exp_lost = vs["combat_exp"] * exp_damage / 100;
                        vs["combat_exp"] -= exp_lost;
#endif

#ifdef LONELY_IMPROVED
			if (killer)
				killer->set("combat/WPKEXP", count_add(killer->query("combat/WPKEXP"), exp_lost));
                        victim->set("combat/dieexp", count_add(victim->query("combat/dieexp"), exp_lost));
#else
                        if (killer)
                                killer->add("combat/WPKEXP",exp_lost);
                        victim->add("combat/dieexp",exp_lost);
#endif
                        // adjust weiwang
                        vs["weiwang"] -= vs["weiwang"] / 10;

                        // adjust score
                        vs["score"] -= vs["score"] / 10;


                        // lost half of potential
#ifdef LONELY_IMPROVED
                        if (count_gt(vs["potential"], vs["learned_points"]))
                                vs["potential"] = count_add(vs["potential"], count_div(count_sub(vs["learned_points"], vs["potential"]), 2));
#else
                        if (vs["potential"] > vs["learned_points"])
                                vs["potential"] += (vs["learned_points"] - vs["potential"]) / 2;
#endif
                        // lost half of experience
                        if (vs["experience"] > vs["learned_experience"])
                                vs["experience"] += (vs["learned_experience"] - vs["experience"]) / 2;

                        victim->skill_death_penalty();
                }
                // generate message of die reason
                if (objectp(killer) && killer->is_character())
                {
                        msg = "被" + filter_color(killer->name(1));

                        if( killer->query("race") == "野兽"
                        ||  killer->query("race") == "蛇类"
                        ||  killer->query("race") == "游鱼"
                        ||  killer->query("race") == "昆虫" )      msg += "咬死了";
                        else if( killer->query("race") == "家畜" ) msg += "踩死了";
                        else if( killer->query("race") == "飞禽" ) msg += "啄死了";
                        else
                        {
                                actions = killer->query_action();
                                switch (mapp(actions) ? actions["damage_type"] : "杀伤") {
                                case "擦伤":
                                case "割伤":
                                        msg+="砍死了";
                                        break;
                                case "刺伤":
                                        msg+="刺死了";
                                        break;
                                case "震伤":
                                case "瘀伤":
                                        msg+="击死了";
                                        break;
                                case "内伤":
                                        msg+="震死了";
                                        break;
                                default:
                                        msg+="杀死了";
                                }
                        }
                }

                if (stringp(victim->query_temp("die_reason")))
                        msg = filter_color(victim->query_temp("die_reason"));

                victim->delete_temp("die_reason");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        sprintf("听说%s" HIM + msg + "。", victim->name(1)));

                // show the follow msg after victim die
                if (follow_msg)
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                              follow_msg);

                victim->set("combat/last_die", filter_color(msg));
                if (objectp(killer) && playerp(killer) && playerp(victim))
                {
                        string cname;
                        object couple;

                        log_file("static/killrecord",
                                 sprintf("%s %s killed %s\n",
                                         log_time(),
                                         log_id(killer), log_id(victim)));

                        killer->remove_killer(victim);

                        // check sadly
                        cname = victim->query("couple/couple_id");
                        if (cname &&
                            victim->query("gender") == "女性" &&
#ifdef LONELY_IMPROVED
                            count_ge(victim->query("combat_exp"), 970000) &&
#else
                            victim->query("combat_exp") >= 970000 &&
#endif
                            objectp(couple = find_player(cname)) &&
                            couple != killer &&
                            couple->query("couple/married") <= 1 &&
                            victim->query("couple/married") <= 1 &&
                            lost_die)
                        {
                                couple->add("static/sadly", 1);
                                tell_object(couple, "你的妻子死在了" +
                                            killer->name(1) + "的手下" +
                                            "，你感到了一阵深深的哀伤。\n");
                        }
                }
        }

        if (stringp(vmark = victim->query("vendetta_mark")) && objectp(killer))
                killer->add("vendetta/" + vmark, 1);
}

// me hit victim with poison in ob
void hit_with_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if (! mapp(p = ob->query_temp("daub/poison")))
                return;

        if (! stringp(poison_type = ob->query_temp("daub/poison_type")))
                return;

        if (! p["remain"])
                return;

        // affect parameter
        ap = allocate_mapping(4);
        if (ob == me)
                ap["level"] = p["level"] * 9 / 10 + 1;
        else
                ap["level"] = p["level"] * 8 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if (p["remain"] > p["level"])
        {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else
        {
                // the poison has run out
                ob->delete_temp("daub");
        }

        msg = HIG "突然$n觉得受伤的地方有一些麻痒";
        if (p["id"] == victim->query("id"))
        {
                if (! victim->query_temp("has_announce/defense1"))
                {
                        victim->set_temp("has_announce/defense1", 1);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "。\n" NOR HIC "$n默一运功，冷笑两声：“好你个" +
                               RANK_D->query_rude(me) + "，居然在我面前卖弄" +
                               RANK_D->query_self_rude(victim) +
                               "毒药！真是假李鬼碰上真李逵了！”\n" NOR;
                } else
                        msg += "，不过$n并没有在意。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < victim->query_skill("poison", 1))
        {
                if (! victim->query_temp("has_announce/defense2"))
                {
                        victim->set_temp("has_announce/defense2", 1);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "。\n" NOR HIC "$n呼吸数次，嘿然冷笑道："
                               "“米粒之珠，也放光华？”\n" NOR;
                } else
                        msg += "，不过$n显然并没有把它放在心上。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < victim->query_skill("force") / 2)
        {
                if (! victim->query_temp("has_announce/defense3"))
                {
                        victim->set_temp("has_announce/defense3", 1);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "。\n" NOR HIC "$n深吸一口气，哈哈长笑道：“好家伙，居然" +
                               (ob == me ? "在身上淬毒" : "使用淬毒兵器") +
                               "，你这些下三滥的手段也敢到我面前卖弄？”\n" NOR;
                } else
                        msg += "，不过$n看起来似乎并无大碍。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        victim->affect_by(poison_type, ap);

        msg += "，大概是中毒了。\n" NOR;
        if (p["level"] < victim->query_skill("force"))
        {
                msg += HIG "$n深深吸一了口气，面目凝重，手中的攻势陡然一紧。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$n闷哼一声，攻势顿缓，神情甚是痛苦。\n" NOR;
        if (! victim->is_busy())
                victim->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

// me hit victim, but poison by victim in ob
void hit_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if (! mapp(p = ob->query_temp("daub/poison")))
                return;

        if (! stringp(poison_type = ob->query_temp("daub/poison_type")))
                return;

        if (! p["remain"])
                return;

        if (me->query_temp("armor/hands"))
                return;

        // affect parameter
        ap = allocate_mapping(4);
        ap["level"]    = p["level"] * 7 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if (p["remain"] > p["level"])
        {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else
        {
                // the poison has run out
                ob->delete_temp("daub");
        }

        msg = HIG "突然$N觉得浑身有些麻痒";
        if (p["id"] == me->query("id"))
        {
                if (! me->query_temp("has_announce/defense1"))
                {
                        me->set_temp("has_announce/defense1", 1);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "。\n" NOR HIC "$N默一运功，冷笑两声：“好你个" +
                               RANK_D->query_rude(victim) + "，居然在我面前卖弄" +
                               RANK_D->query_self_rude(victim) +
                               "的毒药！把你衣服上的毒药都还给我！”\n" NOR;
                } else
                        msg += "，不过$N并没有在意。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < me->query_skill("poison", 1))
        {
                if (! me->query_temp("has_announce/defense2"))
                {
                        me->set_temp("has_announce/defense2", 1);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "。\n" NOR HIC "$N呼吸数次，嘿然冷笑道：“米粒之珠，也"
                               "放光华？你在衣衫上淬毒我就怕你了？”\n" NOR;
                } else
                        msg += "，不过$N显然并没有把它放在心上。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < me->query_skill("force") / 2)
        {
                if (! me->query_temp("has_announce/defense3"))
                {
                        me->set_temp("has_announce/defense3", 1);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "。\n" NOR HIC "$N深吸一口气，哈哈长笑道：“你居然在衣衫上"
                               "淬毒，这些下三滥的手段也敢到我面前卖弄？”\n" NOR;
                } else
                        msg += "，不过$N看起来似乎并无大碍。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        me->affect_by(poison_type, ap);

        msg += "，看来有些不妙。\n" NOR;
        if (p["level"] < me->query_skill("force"))
        {
                msg += HIG "$N深深吸一了口气，面目凝重，手中的攻势陡然一紧。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$N脚步一个跄踉，攻势顿缓，神色难看之极。\n" NOR;
        me->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

void clear_announce(object me)
{
        if (! objectp(me))
                return;

        me->delete_temp("has_announce");
}

void check_quest(object killer,object victim)
{
        mapping quest,b;
        int level,i,exp,pot,score,weiwang,mar,quest_count,all_quest;
        mixed special = 0;
        mixed money = 0;
        object ob,*all_killer,obj;

        //以下是NPC帮派任务的奖励
        //如果是追杀任务
        if (! userp(victim) && victim->query("bunch_quest"))
        {
                quest = victim->query("bunch_quest");
                if (quest["type"] == "追杀" &&
                   ((quest["bunch_type"] == "good" && good_bunch(killer) && killer->query("shen") >= 0) ||
                   (quest["bunch_type"] == "bad" && bad_bunch(killer)  && killer->query("shen") <= 0)) &&
#ifdef LONELY_IMPROVED
                   count_lt(killer->query("combat_exp"), 600000))
#else
                   killer->query("combat_exp") < 600000)
#endif
                {
                        exp = quest["bonus"];
                        exp += 100;
                        exp += random(exp/2);
                        pot = exp/(2 + random(2));
                        score = 25 + random(20);
                        weiwang = 25 + random(20);

                        b = ([ "exp" : exp,
                               "pot" : pot,
                               "score" : score,
                               "weiwang" : weiwang,
                               "prompt": "在追杀" + victim->name() + HIG "的过程中，经过锻炼"
                        ]);

                        QUEST_D->delay_bonus(killer, b);
                }
                return;
        }

        //如果是铲除外敌任务
        if (killer->query("bunch_quest") &&
          killer->query("bunch_quest")["type"] == "铲除外敌" &&
          killer->query("bunch_quest")["ob"] == victim)
        {
                quest = killer->query("bunch_quest");

                exp = quest["bonus"];
                exp += 120;
                exp += random(exp/2);
                pot = exp/(2 + random(2));
                score = 25 + random(20);
                weiwang = 25 + random(20);

                b = ([ "exp" : exp,
                       "pot" : pot,
                       "score" : score,
                       "weiwang" : weiwang,
                       "prompt": "在铲除外来敌人" + victim->name() + HIG "的过程中，经过锻炼"
                ]);

                QUEST_D->delay_bonus(killer, b);

                killer->delete("bunch_quest");
                killer->add_temp("finish_bunch_times",1);
                return;
        }

        //以下是组队任务的奖励
        if (! userp(victim) && victim->query("my_type"))
        {
                /*
                if (objectp(victim->query_defeated_by()) &&
                    userp(victim->query_defeated_by()))
                    killer = victim->query_defeated_by();
                */
                switch(victim->query("my_type"))
                {
                case "外敌入侵":
                        GROUP_QUEST_D->be_killed(1);
                        GROUP_QUEST_D->add_killer(killer);
                        exp = victim->query("bonus");
                        pot = exp;
                        score = random(exp);
                        weiwang = exp + random(exp);
                        mar = random(exp/2);
                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                        "weiwang" : weiwang, "score" : score ]), 1);
                        if (GROUP_QUEST_D->query_enemy() == 0)
                        {
                                all_killer = GROUP_QUEST_D->query_killer();
                                exp = 2000;
                                pot = 2000;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if (! objectp(ob) || ! userp(ob))
                                                continue;

                                        tell_object(ob, HIW "所有入侵的敌人都给打退了，由于你也参与了战斗，" +
                                                            "因此现在你也一起分享胜利果实！\n" NOR);
                                            QUEST_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                           "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                case "门派":
                        GROUP_QUEST_D->be_killed(1);
                        if (victim->query("门派") == killer->query("family/family_name"))
                        {
                                GROUP_QUEST_D->add_killer(killer);
                                exp = victim->query("bonus");
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                                QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                "weiwang" : weiwang, "score" : score, "gongxian" : score ]), 1);
                        }
                        if (GROUP_QUEST_D->query_enemy() == 0)
                        {
                                all_killer = GROUP_QUEST_D->query_killer();
                                exp = 2000;
                                pot = 2000;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if (! objectp(ob) || ! userp(ob))
                                                continue;

                                        tell_object(ob, HIW "所有入侵的敌人都给打退了，由于你也参与了战斗，" +
                                                            "因此现在你也一起分享胜利果实！\n" NOR);
                                        QUEST_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                        "weiwang" : weiwang, "score" : score, "gongxian" : score ]), 1);
                                }
                        }
                        break;
                case "帮派":
                        GROUP_QUEST_D->be_killed(1);
                        if (victim->query("帮派") == killer->query("bunch/bunch_name"))
                        {
                                GROUP_QUEST_D->add_killer(killer);
                                exp = victim->query("bonus");
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                                QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                   "weiwang" : weiwang, "score" : score ]), 1);
                        }
                        if (GROUP_QUEST_D->query_enemy() == 0)
                        {
                                all_killer = GROUP_QUEST_D->query_killer();
                                exp = 2000;
                                pot = 2000;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if (! objectp(ob) || ! userp(ob))
                                                continue;

                                        tell_object(ob, HIW "所有入侵的敌人都给打退了，由于你也参与了战斗，" +
                                                            "因此现在你也一起分享胜利果实！\n" NOR);
                                        QUEST_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                        "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                }
                return;
        }

        //以下是宗师任务的奖励
        if (mapp(quest = killer->query("quest_kh")) && quest["desc"] == "灭")    //东方不败
        {
                if ((quest["name"] == "男子" && victim->query("gender") == "男性") ||
                (quest["name"] == "女子" && victim->query("gender") == "女性") ||
                (quest["type"] == "地点" && (domain_file(base_name(victim)) == quest["dir"] ||
                   (stringp(victim->query("startroom")) && (domain_file(victim->query("startroom")) == quest["dir"])) ||
                base_dir(victim) == quest["dir1"])))
                {
                        if((quest["time"]-time()) < 0)
                        {
                                killer->delete("quest_kh");
                                return ;
                        }
                        else if(victim->query("race")=="野兽") return;
                        else
                        {
                                level = (quest["level"]+1)*(70+random(20));
                                exp = level;
                                pot = exp/(2+random(2));
                                score = random(exp/20);
                                weiwang = random(exp/15);
                                if (killer->query("questkh_times") + 1 > 200)
                                        mar = exp/5 + random(killer->query("questkh_times"));
                                else mar = random(20);
                                if (mar > 5000) mar = 5000;

                                QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                              "weiwang" : weiwang, "score" : score ]), 1);

                                return ;
                        }
                }
        }

        if (mapp(quest = killer->query("quest_dg")))    //独孤求败
        {
                if(quest["type"] == "杀" && victim->name(1) == quest["name"])
                {
                        if((i=killer->query("questdg_times")) < 8)
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*105 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if (level == 9)
                                pot = exp*(2+random(2));
                        else
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);

                        if (killer->query("questdg_times") + 1 > 200)
                                mar = exp/5 + random(killer->query("questdg_times"));
                        else mar = random(20);
                        if (mar > 5000) mar = 5000;

                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);

                        killer->add("questdg_times",1);
                        quest_count = killer->query("questdg_times")%500;
                        if (quest_count == 50)
                                special = 1;
                        else if (quest_count == 100)
                               special = "/d/shaolin/obj/puti-zi";
                        else if (quest_count == 150)
                               money = 1;
                        else if (quest_count == 200)
                               money = 1;
                        else if (quest_count == 250)
                               money = 1;
                        else if (quest_count == 300)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 350)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 400)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 450)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 0)
                                special = "/clone/gift/jiuzhuan";

                        if (special) special_bonus(killer, special);
                        if (money) money_bonus(killer,money);
                        killer->add("total_hatred",-5);
                        if (killer->query("total_hatred") < 0) killer->set("total_hatred",0);
                        killer->delete("quest_dg");

                        all_quest = (int)killer->query("all_quest_dg");
                        if (!all_quest) all_quest = 0;
                        all_quest += 1;
                        if (all_quest == 1000)
                        {
                                obj = new("/clone/gift/cagate");
                                tell_object(killer,"由于你已经累计完成了一千个任务，因此你得到了一个" +
                                                obj->query("name") + "作为奖励\n");
                                if (!obj->move(killer))
                                obj->move(environment(killer));
                                killer->set("all_quest_dg",0);
                        } else killer->set("all_quest_dg",all_quest);
                        return ;
                }
        }

        if (mapp(quest = killer->query("quest_hs")))    //黄裳
        {
                if (quest["type"]=="杀"&&quest["name"]==victim->name(1))
                {
                        tell_object(killer,"恭喜你！你又为绿林立了一功！\n");
                        if((i=killer->query("quesths_times")) < 15)
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if (level > 4 && i > 5)
                                exp /= 2;
                        if (level == 9)
                                pot = exp*(2+random(2));
                        else
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if (killer->query("quesths_times") + 1 > 200)
                                mar = exp/5 + random(killer->query("quesths_times"));
                        else mar = random(20);
                        if (mar > 5000) mar = 5000;

                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);

                        killer->add("quesths_times",1);
                        quest_count = killer->query("quesths_times")%500;
                        if (quest_count == 50)
                                special = 1;
                        else if (quest_count == 100)
                               special = "/d/shaolin/obj/puti-zi";
                        else if (quest_count == 150)
                               money = 1;
                        else if (quest_count == 200)
                               money = 1;
                        else if (quest_count == 250)
                               money = 1;
                        else if (quest_count == 300)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 350)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 400)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 450)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 0)
                                special = "/clone/gift/jiuzhuan";

                        if (special) special_bonus(killer, special);
                        if (money) money_bonus(killer,money);

                        killer->add("total_hatred",-5);
                        if (killer->query("total_hatred") < 0) killer->set("total_hatred",0);
                        killer->delete("quest_hs");
                        killer->set_temp("hs_giveup",0);

                        all_quest = (int)killer->query("all_quest_hs");
                        if (!all_quest) all_quest = 0;
                        all_quest += 1;
                        if (all_quest == 1000)
                        {
                                obj = new("/clone/gift/ccrystal");
                                tell_object(killer,"由于你已经累计完成了一千个任务，因此你得到了一个" +
                                                obj->query("name") + "作为奖励\n");
                                if (!obj->move(killer))
                                obj->move(environment(killer));
                                killer->set("all_quest_hs",0);
                        } else killer->set("all_quest_hs",all_quest);
                        return ;
                }
        }

        if (mapp(quest = killer->query("quest_sn")))    //南海神尼
        {
                if (quest["type"]=="杀"&&quest["name"]==victim->name(1))
                {
                        tell_object(killer,"恭喜你！你又为南海神尼立了一功！\n");
                        if ((i=killer->query("questsn_times")) < 15)
                                i = 15-i;
                        else i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if (level > 4 && i > 5)
                                exp /= 2;
                        if (level == 9)
                                pot = exp*(2+random(2));
                        else
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if (killer->query("questsn_times") + 1 > 200)
                                mar = exp/5 + random(killer->query("questsn_times"));
                        else mar = random(20);
                        if (mar > 5000) mar = 5000;

                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);

                        killer->add("questsn_times",1);
                        quest_count = killer->query("questsn_times")%500;
                        if (quest_count == 50)
                                special = 1;
                        else if (quest_count == 100)
                               special = "/d/shaolin/obj/puti-zi";
                        else if (quest_count == 150)
                               money = 1;
                        else if (quest_count == 200)
                               money = 1;
                        else if (quest_count == 250)
                               money = 1;
                        else if (quest_count == 300)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 350)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 400)
                               special = "/clone/misc/tianxiang";
                        else if (quest_count == 450)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 0)
                                special = "/clone/gift/jiuzhuan";

                        if (special) special_bonus(killer, special);
                        if (money) money_bonus(killer,money);

                        killer->add("total_hatred",-5);
                        if (killer->query("total_hatred") < 0) killer->set("total_hatred",0);
                        killer->delete("quest_sn");
                        killer->set_temp("sn_giveup",0);

                        all_quest = (int)killer->query("all_quest_sn");
                        if (!all_quest) all_quest = 0;
                        all_quest += 1;
                        if (all_quest == 1000)
                        {
                                obj = new("/clone/gift/cjade");
                                tell_object(killer,"由于你已经累计完成了一千个任务，因此你得到了一个" +
                                                obj->query("name") + "作为奖励\n");
                                if (!obj->move(killer))
                                obj->move(environment(killer));
                                killer->set("all_quest_sn",0);
                        } else killer->set("all_quest_sn",all_quest);
                        return ;
                }
       }
}

private void special_bonus(object me, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/hantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(me, 1);
        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

void money_bonus(object me, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(me,1);

        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

string base_dir(object obj)
{
        string filename;
        int at;

        filename = base_name(obj);
        at = strsrch(filename,"/",-1);
        filename = filename[0..at];
        return filename;
}
/*
void team_gain(object me,string name, int gain)
{
        object *memb;
        int i,n, sum;

        if(!objectp(me)
        || !stringp(name)
        || (gain <= 0) )
                return;

        if(!n = sizeof(memb = me->query_team_member()))
                return;

        for(i=0;i<n;i++)
                sum += memb[i]->query("combat_exp");

        for(i=0;i<n;i++)
        {
                float temp = to_float(memb[i]->query("combat_exp"));
                int e = temp/sum*gain;

                if(e < 1)
                        e = 1;

                tell_object(memb[i],sprintf("你所在的队伍杀死%s，你分到%d点经验。\n\n",name,e));
                memb[i]->add("combat_exp",e);
        }
}

void array_gain(object me,string name,int gain,int exp)
{
        object *memb;
        int i,n, sum;
        string a_name;

        if(!objectp(me)
        ||!stringp(name)
        || (gain <= 0)
        || (exp <= 0)
        || (!a_name = me->query_array_name()) )
                return;

        if(!n = sizeof(memb = me->query_array_member()))
                return;

        for(i=0;i<n;i++)
                sum += memb[i]->query("combat_exp");

        gain *= 1.2;

        for(i=0;i<n;i++)
        {
                float temp = to_float(memb[i]->query("combat_exp"));
                int e = temp/sum*gain;

                if(e < 1)
                        e = 1;

                tell_object(memb[i],sprintf("『%s』杀死%s，你分到%d点经验。\n\n",
                        a_name,name,e));
                memb[i]->add("combat_exp",e);
        }
}


eg.
        if(userp(killer)
        && killer->in_array()
        && killer->query_array_status())
                array_gain(killer,victim->name(),gain,k_exp);

        else if(userp(killer)
        && killer->in_team() )
                team_gain(killer,victim->name(),gain);
*/
