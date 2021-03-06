// attack.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
// Modified by Lonely for nt2 (03/28/2005)

#include <ansi.h>
#include <dbase.h>
#include <origin.h>
#include <skill.h>
#include <action.h>

#define MAX_OPPONENT            4

string *killer = ({ });
string *want_kills = ({ });
nosave string current_skill = "unarmed";

void   meet(string str, object ob);
nosave object *enemy = ({});
nosave mixed  next_action = 0;
nosave mixed  default_object = 0;
nosave string default_function =0;
nosave object competitor = 0;
nomask string query_current_skill() { return current_skill; }

// query_ATTACK() and set_ATTACK()
mapping query_ATTACK()
{
	mapping m = ([]);
	m["killer"] = killer;
	m["want_kills"] = want_kills;
	return m;
}

int set_ATTACK(mapping m)
{
        if (! mapp(m))
                return 0;
                
	killer = m["killer"];
	want_kills = m["want_kills"];
	return 1;
}	

// prototypes
object *query_enemy()  { return enemy; }
string *query_killer() { return killer; }
string *query_want()   { return want_kills; }
mapping query_default_action() { return ([ default_object : default_function ]); }
void    apply_killer(string *ik) { if (arrayp(ik)) killer = filter_array(ik, (: stringp :)); }
void    apply_want(string *ik)   { if (arrayp(ik)) want_kills = filter_array(ik, (: stringp :)); }

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_fighting(object ob)
{
        if (! ob) return sizeof(enemy) > 0;

        return arrayp(enemy) && member_array(ob, enemy) != -1;
}

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_killing(string id)
{
        if (! id) return sizeof(killer) > 0;

        return arrayp(killer) && member_array(id, killer) != -1;
}

// This function returns 1 if I want to kill ob
varargs int is_want_kill(string id)
{
        return arrayp(want_kills) && member_array(id, want_kills) != -1;
}

// This function will update all killer inforamtion
void update_killer()
{
        if (! arrayp(killer) || ! arrayp(want_kills))
        {
                killer = ({ });
                want_kills = ({ });
                return;
        }

        // remove all offline char's information
        want_kills = filter_array(want_kills, (: objectp(find_player($1)) :));

        // remove all passive killing action
        killer = filter_array(killer, (: member_array($1, want_kills) == -1 :));
}

//This function starts fight between this_object() and ob
void fight_ob(object ob)
{
        object env;
        object *memb;

        if (! ob || ob == this_object()) return;
        if (member_array(ob, enemy) != -1)
                return;

        env = environment();
        if (environment(ob) != env ||
            env->query("no_fight"))
                return;

        if (! living(this_object()))
                return;

        set_heart_beat(1);

        enemy += ({ ob });

        // 阵法调用
        if (this_object()->in_array() > 1)
        {
                if (this_object()->is_array_member(ob))
                        this_object()->query_array_master()->release_array(5); // 起内杠解散阵
                else
                {
                        memb = this_object()->query_array_member() - ({ this_object() });
                        foreach(object body in memb)
                        {
                                body->fight_ob(ob);
                                ob->fight_ob(body);
                        }
                }
        }
                        
        if (this_object()->is_guarder() &&
            is_killing(ob->query("id")))
        {
                // guarder will look for help
                this_object()->kill_enemy(ob);
        }

        /*
        if (this_object()->is_master() &&
            is_killing(ob->query("id")))
        {
                // family will look for help
                this_object()->master_accept_kill(ob);
        }
        */

        ob->fight_ob(this_object());
}

// This function starts killing between this_object() and ob
void kill_ob(object ob)
{       
        object *guarded;
        object me;
        object env;
        object gob;
        //int i;

        me = this_object();
        if (! living(me) || ! ob)
                return;

        env = environment();
        if (environment(ob) != env ||
            env->query("no_fight"))
                return;

        guarded = ob->query_temp("guarded");  
        if (! guarded) guarded = ({ });
        if (member_array(me, guarded) != -1)
        {
                tell_object(ob, HIR "不能杀你要保护的人！\n" NOR);
                return;
        }

        if (query_temp("owner") == ob)
        {
                tell_object(me, HIR "不能对你的主人下毒手。\n" NOR);
                return;
        }

        if (! arrayp(killer)) killer = ({ });
        if (member_array(ob->query("id"), killer) == -1)
        {
                killer += ({ ob->query("id") });
                tell_object(ob, HIR "看起来" + this_object()->name() +
                             HIR "想杀死你！\n" NOR);
        }

        foreach (gob in guarded)
        { 
                if (! gob || gob == me ||
                    environment(gob) != environment())
                        continue;

                if (! living(gob))
                        continue;

                if (gob->is_killing(me->query("id")))
                        continue;

                tell_object(gob, HIR + ob->name(1) +
                            "受到攻击，你挺身而出，加入战团！\n" NOR);
                switch (random(8))
                {
                case 0:
                        message_vision(HIW "$N" HIW "一言不发，对$n"
                                       HIW "发动了攻击。\n" NOR, gob, me);
                        break;
                case 1:
                        message_vision(HIW "$N" HIW "一声怒吼，冲上前"
                                       "去，看来是要和$n" HIW "拼命。\n" NOR,
                                       gob, me);
                        break;
                case 2:
                        message_vision(HIW "$N" HIW "冷笑了一声，道："
                                       "“接招吧！”说罢就对$n" HIW
                                       "发动了攻击。\n" NOR, gob, me);
                        break;
                case 3:
                        message_vision(HIW "$N" HIW "迈上一步，挡在前"
                                       "面，开始和$n" HIW "进行殊死搏"
                                       "斗！\n" NOR, gob, me);
                        break;
                case 4:
                        message_vision(HIW "$N" HIW "双臂一振，脸如寒水，"
                                       "已经向$n" HIW "接连发出数招！\n"
                                       NOR, gob, me);
                        break;
                case 5:
                        message_vision(HIW "$N" HIW "深吸一口气，一招"
                                       "直指$n" HIW "的要害，竟然是要"
                                       "取人的性命！\n" NOR, gob, me);
                        break;
                case 6:
                        message_vision(HIW "紧接着$N" HIW "已经攻上！"
                                       "招招进逼$n" HIW "，毫无容情余"
                                       "地！\n" NOR, gob, me);
                        break;
                default:
                        message_vision(HIW "$N" HIW "飞也似的扑上前来"
                                       "，开始进攻$n" HIW "。\n" NOR, gob, me);
                        break;
                }

                if (ob->is_want_kill(me->query("id")))
                        gob->want_kill(me);
                gob->kill_ob(me);
        }
        fight_ob(ob);
}

void want_kill(object ob)
{
        string ob_id;
        object me;

        if (! playerp(ob)) return;

        if (! arrayp(want_kills)) want_kills = ({ });

        ob_id = ob->query("id");
        if (is_killing(ob_id) ||
            is_want_kill(ob_id)) return;

        if (ob->is_want_kill(query("id"))) return;

        want_kills += ({ ob_id });
        
        me = this_object();
        
        if (playerp(ob) && ! ob->query("no_newbie") &&
            objectp(environment(ob)) && 
            domain_file(base_name(environment(ob))) != "pk" && 
            ! environment(ob)->query("fight_room")) 
        {
                me->set("no_newbie", 1);
                if (me->query("newbie"))
                {
                        me->delete("newbie");
                        tell_object(me, HIR "由于你主动攻击其他玩家，所以取消对你的新手保护！\n" NOR);
                }
        }
}

void clean_up_enemy()
{
        int i;

        if (i = sizeof(enemy))
        {
                while (i--)
                {
                        if (! objectp(enemy[i]) ||
                            environment(enemy[i]) != environment() ||
                            (! living(enemy[i]) && ! is_killing(enemy[i]->query("id"))))
                            enemy[i] = 0;
                }
                enemy -= ({ 0 });
        }
}

// This function checks if the current opponent is available or
// select a new one.
object select_opponent()
{
        int which;

        if (! (which = sizeof(enemy))) return 0;

        which = random(which);

        return enemy[which];
}

// Stop fighting ob.
int remove_enemy(object ob)
{
        enemy -= ({ ob });
        return 1;
}

// Stop killing ob.
int remove_killer(object ob)
{
        if (playerp(ob))
                want_kills -= ({ ob->query("id") });

        if (is_killing(ob->query("id")))
        {
                killer -= ({ ob->query("id") });
                remove_enemy(ob);
                return 1;
        }

        return remove_enemy(ob);
}

// Stop all fighting, but killer remains.
// If force set to 1, it will clear all enemy, or it will only
// clear the enemy who doesn't kill you.
void remove_all_enemy(int force)
{
        int i;

        if (! (i = sizeof(enemy)))
                return;

        while (i--)
        {
                // We ask our enemy to stop fight, but not nessessary to confirm
                // if the fight is succeffully stopped, bcz the fight will start
                // again if our enemy keeping call COMBAT_D->fight() on us.
                if (objectp(enemy[i]))
                {
                        if (force || ! enemy[i]->is_killing(query("id")))
                        {
                                enemy[i]->remove_enemy(this_object());
                                enemy[i] = 0;;
                        }
                }
        }

        enemy -= ({ 0 });
}

// Not want to kill anyone
void remove_all_want()
{
        want_kills = ({});
}

// Stop all fighting and killing.
void remove_all_killer()
{
        int i;
       // object ob;

        enemy -= ({ 0 });
        remove_all_want();

        for (i = 0; i < sizeof(enemy); i++)
                if (enemy[i]->remove_killer(this_object()))
                        enemy[i] = 0;

        killer = ({ });

        enemy -= ({ 0 });
}

object query_competitor()
{
        return competitor;
}

object set_competitor(object ob)
{
        competitor = ob;
}

// set competition with ob
void competition_with(object ob)
{
        competitor = ob;
        fight_ob(ob);
        ob->set_competitor(this_object());
        ob->fight_ob(this_object());
}

// win a competition
void win()
{
        run_override("win");
        competitor = 0;
}

// lost a competition
void lost()
{
        run_override("lost");
        competitor = 0;
}

// return the next action of this object
mixed query_action(int flag)
{
        if (flag || !functionp(next_action))
                return next_action;

        return (*next_action)(this_object());
}

// set next action
int set_action(mixed action, string fun)
{
        if (mapp(action) || functionp(action))
        {
                next_action = action;
        } else
        if (stringp(action) || objectp(action))
        {
                next_action = (: call_other, action, fun :);
        } else
                return 0;

        return 1;
}

// set default action
// this action may be a simple mapping or a file & function to called
int set_default_action(mixed ob, string fun)
{
        default_object = ob;
        default_function = fun;
        return 1;
}

// reset_action()
//
// This function serves as a interface of F_ATTACK and wielded, worn objects.
// When the living's fighting action need update, call this function.
//
void reset_action()
{
        object me,ob;
        mapping prepare;
        string type, skill;

        me = this_object();
        prepare = query_skill_prepare();
        
        if (ob = query_temp("weapon"))
        {
                type = ob->query("skill_type");
                if (type == "pin")
                        // the pin skill will the same as the sword skill,
                        // why don't I remove pin skill ? because I don't
                        // want the pin will be treat as sword, only at the
                        // combatd, they as same.
                        type = "sword";
        }
        else if (! prepare || sizeof(prepare) == 0) type = "unarmed";
        else if (sizeof(prepare) == 1) type = (keys(prepare))[0];
        else if (sizeof(prepare) == 2) 
                type = (keys(prepare))[query_temp("action_flag")];

        if (stringp(skill = query_skill_mapped(type)) &&
            (int)query_skill(skill, 1) > 0)
        {
                // If using a mapped skill, call the skill daemon.
                if (ob)
                        set_action((: call_other, SKILL_D(skill), "query_action", me, ob :), 0);
                else
                        set_action((: call_other, SKILL_D(skill), "query_action" :), 0);

                if (current_skill != skill)
		{
			current_skill = skill;
			this_object()->change_skill_status(skill);
		}
        } else
        {
                // Else, let weapon handle it.
                if (ob)
                        set_action(ob->query("actions", 1), 0);
                else
                        set_action(default_object, default_function);

                if (current_skill != skill)
		{
			current_skill = skill;
			this_object()->change_skill_status(skill);
		}
        }
}

// This is called in heart_beat() to perform attack action.
int attack()
{
        object opponent;

        clean_up_enemy();

        opponent = select_opponent();
        if (objectp(opponent))
        {
                set_temp("last_opponent", opponent);
                COMBAT_D->fight(this_object(), opponent);
                return 1;
        } else
                return 0;
}

//
// init() - called by MudOS when another object is moved to us.
//
void init()
{
        object me;
        object ob;
        mapping my, its;
        string bunch_name;
        string vendetta_mark;

        // We check these conditions here prior to handle auto fights. Although
        // most of these conditions are checked again in COMBAT_D's auto_fight()
        // function, these check reduces lots of possible failure in the call_out
        // launched by auto_fight() and saves some overhead.
        me = this_object();

        if (! living(me) ||
            ! (ob = this_player()) ||
            ! living(ob) ||
            sizeof(enemy) ||
            (! interactive(ob) && ! interactive(me)))
                return;

        if (me->query_temp("owner") ||
            ob->query_temp("owner") == me)
                return;

        my = query_entire_dbase();
        its = ob->query_entire_dbase();

        if (stringp(bunch_name = query("bunch/bunch_name")) && 
            bunch_name == (string)ob->query("bunch/bunch_name") &&
            ! playerp(this_object()) && playerp(ob))  
        {
                if (! ob->is_killing(query("id")))
                        remove_killer(ob);
                        
                remove_call_out("canjian");       
                call_out("canjian", 0, this_object(), ob);
        }

        // Now start check the auto fight cases.
        if (interactive(ob) && is_killing(its["id"]))
        {
                if (interactive(me))
                {
                        // I don't wish two user kill ecah other
                        // when meeting. Because one player can
                        // kill another player & quit, then relogin,
                        // so nobody know that the player is willing
                        // to kill another player but another player
                        // may lost his life because auto fight.
                        // Here, I will check weather the player is
                        // really want to kill the other player,
                        // If want, then start auto fight.
                        if (! is_want_kill(its["id"]))
                        {
                                remove_killer(ob);
                                return;
                        }
                }

                COMBAT_D->auto_fight(me, ob, "hatred");
                return;
        } else
        /*
        if (stringp(vendetta_mark = my["vendetta_mark"]) &&
            ob->query("vendetta/" + vendetta_mark))
        {
                COMBAT_D->auto_fight(me, ob, "vendetta");
                return;
        } else
        */
        if (stringp(vendetta_mark = query("bunch/bunch_name")) &&
            ob->query("vendetta/" + vendetta_mark))
        {
                COMBAT_D->auto_fight(me, ob, "vendetta");
                return;
        } else    
        if (! playerp(ob) && my["attitude"] == "aggressive")
        {
                COMBAT_D->auto_fight(me, ob, "aggressive");
                return;
        }               

        return;
}   

void canjian(object ob, object me)
{
        if (! me || environment(me) != environment(ob)) 
                return;
        
        if (is_killing(me->query("id")))
                message_vision(HIC "$N" HIC "大喝一声：$n" HIC "，今天" +
                               RANK_D->query_self_rude(ob) + 
                               "要讨个公道！\n" NOR, ob, me);                                      
        else 
        if (me->query("vendetta/" + ob->query("bunch/bunch_name")))
                message_vision(HIC "$N" HIC "对着$n" HIC "道：" + 
                               RANK_D->query_self(ob) +
                               "奉命行事，还请" + 
                               RANK_D->query_respect(me) + 
                               "多多担待。\n" NOR, ob, me);
                                       
        else 
        if (stringp(me->query("bunch/title")) &&
            me->query("bunch/level") > 1)        
        {
                message_vision(HIC "$N" HIC "躬身对$n" HIC "道：属下参见" + 
                               me->query("bunch/title") + "。\n" NOR, ob, me);
        }
}
