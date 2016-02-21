// channeld.c
// 97-10-18 add intermud channel and emote capability
//          By ken@XAJH & fuyo@XAJH
// Updated by Doing for HELL

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <mudlib.h>
#include <net/macros.h>
#include <net/dns.h>
#include <localtime.h>

inherit F_DBASE;

#define ALLOW_LIST ({ })
#define SPECIAL_NPC     ({ "/adm/npc/youxun" })

#define REMOTE_Q        "/adm/daemons/network/services/remote_q.c"

string remove_addresses(string, int);
int filter_listener(object ppl, string only, object me);
private int check_bad_words(object user,string msg);

nosave string msg_log;
nosave int log_from;

string query_msg_log() { return msg_log; }

//¶ÔÓÚ²ÎÊýµÄ½âÊÍ£¬update by alf
//msg_speak   ±ê×¼Ëµ»°µÄÌâÍ·
//msg_emote   ¶¯×÷Ëµ»°µÄÌáÍ·£¬²»¶¨ÒåÔò±íÊ¾²»ÄÜÓÃ¶¯×÷
//msg_color   ÆµµÀµÄÑÕÉ«
//name        ÆµµÀµÄÃû³Æ
//only        Ö¸¶¨½ÓÊÜÐÅÏ¢µÄÍæ¼ÒÀàÐÍ
//            wiz    :  appÒÔÉÏ¿ÉÒÔÊ¹ÓÃ¼°¿´µ½
//            arch   :  archÒÔÉÏ¿ÉÒÔÊ¹ÓÃ¼°¿´µ½
//            party  :  °ïÅÉÄÚ²¿Ê¹ÓÃ¼°¿´µ½£¨Î×Ê¦ºÍÖ¸¶¨¿ÉÒÔÊÕ¿´ËùÓÐÆµµÀµÄID¿ÉÒÔ¿´µ½£©
//            family :  ÃÅÅÉÄÚ²¿Ê¹ÓÃ¼°¿´µ½£¨Î×Ê¦ºÍÖ¸¶¨¿ÉÒÔÊÕ¿´ËùÓÐÆµµÀµÄID¿ÉÒÔ¿´µ½£©
//            league :  Í¬ÃËÅÉÄÚ²¿Ê¹ÓÃ¼°¿´µ½£¨Î×Ê¦ºÍÖ¸¶¨¿ÉÒÔÊÕ¿´ËùÓÐÆµµÀµÄID¿ÉÒÔ¿´µ½£©
//name_raw    ÉèÖÃÎª1µÄ»°£¬¸ÃÆµµÀÔÚÍæ¼Ò´÷Ãæ¾ßºóÈÔÈ»È¡ÆäÕæÊµÐÕÃû
//need_age    ÉèÖÃÎª1µÄ»°£¬¸ÃÆµµÀÔÚÍæ¼Ò18ËêÖ®Ç°ÎÞ·¨Ê¹ÓÃ
//omit_log    ¼ÇÂ¼ÁÄÌì¼ÇÂ¼

string *bad_words = 
({
       "ÈÕÄã", "²ÙÄã", "¸ÉÄã", "ÈÕËÀ", "²ÙËÀ", "¸ÉËÀ", "¹·ÈÕ", "ÈÕ³öÀ´",
       "riÄã", "caoÄã", "ganÄã", "riËÀ", "caoËÀ", "ganËÀ", "¹·ri", "ri³öÀ´",
       "ÎÒÈÕ", "ÎÒ²Ù", "ÎÒ¸É", "ÎÒ¿¿", "ÎÒri", "ÎÒcao", "ÎÒgan", "ÎÒkao",
       "fuck", "¼¦°Í", "¸ØÃÅ", "ÐÔ½»", "ÐóÉú", "Ç¿¼é", "¸Ø½»", "·¨ÂÖ¹¦",
       "²åËÀ", "¸É³öÀ´", "gan³öÀ´", "¹·Äï", "ÔÓÖÖ", "×ÔÎ¿", "´ò·É»ú",
       "Òùµ´", "Ä¸¹·", "×æ×ÚÊ®°Ë", "ÂèµÄ¸ö±Æ", "ÂèµÄ±Æ", "Âè¸ö±Æ", "shit",
       "Âè±Æ", "±ÆÑøµÄ", "Ð¡±Æ", "ÂèµÄ¸öb", "ÂèµÄb", "Âè¸öb", "Âèb", "É§»õ",
       "bÑøµÄ", "Ð¡b", "ÄãÂèÉú", "ÒõµÀ", "Òõ»§", "ÒõµÙ", "Òõ¾¥", "¹êÍ·",
       "ÂÑµ°", "¹·Äï", "ÎÚ¹êÍõ°Ë", "Éµ±Æ", "Éµb", "sb", "×ö°®", "ÒâÒù", "ÂÖ¼é", "ÔÓ½»",
       "ÂèÂèµÄ", "bitch", "ÐÔ°®", "falun", "Èý¼¶Æ¬", "sex", "ëë", "¼Ë", "æ½",
       "åê", "æ»", "ŒÂ", "ÚP", "åþ", "ÃH", "åê", "ŒÅ", "µõÄã", "µóÄã",
});

mapping channels = ([
        "sys":  ([      "msg_speak": HIR "¡¾ÏµÍ³±¨¸æ¡¿%s£º%s\n" NOR,
                        "msg_emote": HIR "¡¾ÏµÍ³±¨¸æ¡¿%s" NOR,
                        "msg_color": HIR,
                        "only"     : "imm",
                        "name"     : "ÏµÍ³",
                        "omit_log" : 1,
                        "name_raw" : 1,
                ]),

        "wiz":  ([      "msg_speak": HIG "¡¾Î×Ê¦ÆµµÀ¡¿%s£º%s\n" NOR,
                        "msg_emote": HIG "¡¾Î×Ê¦ÆµµÀ¡¿%s" NOR,
                        "msg_color": HIG,
                        "name"     : "Î×Ê¦",
                        "only"     : "imm",
                        "intermud" : GCHANNEL,
                        "intermud_emote"   : 1,
                        "intermud_channel" : "wiz",
                        "omit_address": 0,
                        "omit_log" : 1,
                        "name_raw" : 1,
                        "filter"   : (: $1["MUDLIB"] == MUDLIB_NAME :)
                ]),

        "gwiz": ([      "msg_speak": HIG "¡¾Íø¼ÊÎ×Ê¦¡¿%s£º%s\n" NOR,
                        "msg_emote": HIG "¡¾Íø¼ÊÎ×Ê¦¡¿%s" NOR,
                        "msg_color": HIG,
                        "name"     : "½»Á÷",
                        "only"     : "imm",
                        "intermud" : GCHANNEL,
                        "intermud_emote"   : 1,
                        "intermud_channel" : "gwiz",
                        "omit_address"     : 0, 
                        "omit_log" : 1,
                        "name_raw" : 1,
                        "filter"   : 1,
                ]),
              
        // 97-10-18 this channel add for display debug message by ken@XAJH
        "debug":([      "msg_speak": HIW "¡¾µ÷ÊÔÐÅÏ¢¡¿%s£º%s\n" NOR,
                        "msg_emote": HIW "¡¾µ÷ÊÔÐÅÏ¢¡¿%s" NOR,
                        "msg_color": HIW,
                        "name"     : "µ÷ÊÔ",
                        "only"     : "wiz",
                        "omit_log" : 1,
                        "name_raw" : 1,
                ]),

        "task": ([      "msg_speak": WHT "¡¾ÈÎÎñÆµµÀ¡¿%s£º%s\n" NOR,
                        "msg_emote": WHT "¡¾ÈÎÎñÆµµÀ¡¿%s" NOR,
                        "msg_color": WHT,
                        "name"     : "ÈÎÎñ",
                        "omit_log" : 1,
                        "name_raw" : 1,
                ]),

        "war": ([       "msg_speak": MAG "¡¾Õ½ÕùÆµµÀ¡¿%s£º%s\n" NOR,
                        "msg_emote": MAG "¡¾Õ½ÕùÆµµÀ¡¿%s" NOR,
                        "msg_color": MAG,
                        "name"     : "ÈÎÎñ",
                        "omit_log" : 1,
                        "name_raw" : 1,
                ]),
                                
        "inter":([      "msg_speak": HIR "¡¾Í¬ÃË½»Ì¸¡¿%s£º%s\n" NOR,
                        "msg_emote": HIR "¡¾Í¬ÃË½»Ì¸¡¿%s" NOR,
                        "msg_color": HIR,
                        "only"     : "league",
                        "name_raw" : 1,
                        "name"     : "Í¬ÃË",
                        "omit_log" : 1,
                ]),

        "chat": ([      "msg_speak": HIC "¡¾ÂÛµÀ½­ºþ¡¿%s£º%s\n" NOR,
                        "msg_emote": HIC "¡¾ÂÛµÀ½­ºþ¡¿%s" NOR,
                        "msg_color": HIC,
                        "name"     : "ÏÐÁÄ",
                ]),

        "nitan":([      "msg_speak": HIC "¡¾ÒìÓò´«ÎÅ¡¿%s£º%s\n" NOR,
                        "msg_emote": HIC "¡¾ÒìÓò´«ÎÅ¡¿%s" NOR,
                        "msg_color": HIC,
                        "intermud" : GCHANNEL,
                        "intermud_emote"   : 1,
                        "intermud_channel" : "nitan",
                        "name"     : "ÒìÓò",
                        "filter"   : (: $1["MUDLIB"] == MUDLIB_NAME :)
                ]),

        "es":   ([      "msg_speak": HIC "¡¾Íø¼Ê´«Çé¡¿%s£º%s\n" NOR,
                        "msg_emote": HIC "¡¾Íø¼Ê´«Çé¡¿%s" NOR,
                        "msg_color": HIC,
                        "intermud" : GCHANNEL,
                        "intermud_emote"   : 1,
                        "intermud_channel" : "es",
                        "name"     : "Íø¼Ê",
                        "filter"   : 1,
                        // "need_age" : 1,
                        "omit_address"     : 0, 
                 ]), 

        "sing":  ([     "msg_speak": CYN "¡¾»¶¸èÐ¦Óï¡¿%s³ªÖø£º%s\n" NOR,
                        "msg_color": CYN,
                        "name"     : "¸è³ª",            
                 ]),

        "bill":  ([     "msg_speak": HIY "¡¾ÉÌ¼Ö´«ÎÅ¡¿%s£º%s\n" NOR,
                        "msg_color": HIY,
                        "name"     : "½»Ò×",
                        "name_raw" : 1,
                        "omit_log" : 1,
                 ]),

        "ultra": ([     "msg_speak": HIW "¡¾´ó ×Ú Ê¦¡¿%s£º%s\n" NOR,
                        "msg_emote": HIW "¡¾´ó ×Ú Ê¦¡¿%s" NOR,
                        "msg_color": HIW,
                        "name"     : "´ó×ÚÊ¦",
                        "intermud" : GCHANNEL,
                        "intermud_emote"    : 1,
                        "intermud_channel"  : "rultra",
                        "filter"   : (: $1["MUDLIB"] == MUDLIB_NAME :)
                ]),

        "shout":([      "msg_speak": HIW "%s×ÝÉù³¤Ð¥£º%s\n" NOR,
                ]),

        "rumor":([      "msg_speak": HIM "¡¾Ò¥ÑÔËÄÆð¡¿%s£º%s\n" NOR,
                        "msg_emote": HIM "¡¾Ò¥ÑÔËÄÆð¡¿%s" NOR,
                        "msg_color": HIM,
                        "name"     : "Ò¥ÑÔ",
                        "anonymous": "Ä³ÈË",
                ]),
        /*
        "sos":  ([      "msg_speak": HIG "¡¾½­ºþ¸æ¼±¡¿%s£º%s\n" NOR,
                        "msg_color": HIG,
                        "name_raw" : 1,
                        "name"     : "ÇóÖú",
                ]),
        */
        "party":([      "msg_speak": HIG "¡¾±¾°ï»°Óï¡¿%s£º%s\n" NOR,
                        "msg_emote": HIG "¡¾±¾°ï»°Óï¡¿%s" NOR,
                        "msg_color": HIG,
                        "only"     : "party",
                        "name"     : "°ïÅÉ",
                        "omit_log" : 1,
                ]),
        "family":([     "msg_speak": HIG "¡¾Í¬ÃÅ»°Óï¡¿%s£º%s\n" NOR,
                        "msg_emote": HIG "¡¾Í¬ÃÅ»°Óï¡¿%s" NOR,
                        "msg_color": HIG,
                        "only"     : "family",
                        "name"     : "Í¬ÃÅ",
                        "omit_log" : 1,
                ]),
        "rultra":([     "msg_speak": WHT "¡¾ÈûÍâ×ÚÊ¦¡¿%s£º%s\n" NOR,
                        "msg_emote": WHT "¡¾ÈûÍâ×ÚÊ¦¡¿%s" NOR,
                        "msg_color": WHT,
                        "name"     : "ÈûÍâ×ÚÊ¦",
                        "for_listen": 1,
                ]),
]);

void create()
{
        // This is required to pass intermud access check.
        seteuid(getuid());
        set("channel_id", "ÆµµÀ¾«Áé");
}

mapping query_chann() {	return channels;}

// ¼ÇÂ¼ÆµµÀÏûÏ¢µÄÈÕÖ¾
void channel_log(string msg, string verb, object user)
{
        string lfn;
        mixed lt;
        int t;

        if (! mapp(channels[verb]) || ! objectp(user) || ! userp(user))
                return;

        if (channels[verb]["omit_log"])
                return;

        if (! stringp(msg_log)) msg_log = "";

        t = time();
        msg_log += sprintf(" %s(%s) on %s\n%s",
                           user->name(1), user->query("id"), log_time(), filter_color(msg));
        if (strlen(msg_log) > 8000 || t - log_from > 900)
        {
                lt = localtime(t);

                lfn = sprintf("channel/%d-%d-%d", lt[LT_YEAR],
                              lt[LT_MON] + 1, lt[LT_MDAY]);
                assure_file(LOG_DIR + lfn);
                log_file(lfn, msg_log);
                msg_log = "";
                log_from = t;
        }
}

// ½ÓÊÕREMOTE_Q·µ»ØÀ´µÄÐÅÏ¢²¢ÏÔÊ¾Ö®
void do_remote_channel(object me, string verb, string arg)
{
        object *obs;
        string msg;

        if (undefinedp(channels[verb]) || ! userp(me))
                return;

        // Ok, I will direct send the message to those people listening us.
        obs = all_interactive();
        if (stringp(channels[verb]["only"]))
                obs = filter_array(obs, (: filter_listener :),
                                   channels[verb]["only"], me);

        msg = sprintf(channels[verb]["msg_emote"], arg);
        message("channel:" + verb, msg, obs);
        channel_log(msg, verb, me);

        // Ïò¸÷¸öÕ¾µã·¢ËÍEMOTEÐÅÏ¢
        channels[verb]["intermud"]->send_msg(channels[verb]["intermud_channel"],
                                             me->query("id"), me->name(1),
                                             arg, 1,
                                             channels[verb]["filter"]);
}

varargs int do_channel(object me, string verb, string arg, int emote)
{
        object *obs;
        string *tuned_ch, who;
        int is_player, myemote;
        string imsg = 0, local;
        string msg;
        object *tobs;
        //object tplayer;
        object *pobs;

        string party;
        string family;
        string fname;

        // Check if this is a channel emote.
        if (sizeof(verb) > 2)
        {
                if (verb[sizeof(verb) - 1] == '*')
                {
                        emote = 1;
                        verb = verb[0..<2];
                }
        }

        if (sizeof(verb) > 2)
        {
                if (verb[sizeof(verb) - 1] == '#')
                {
                        myemote = 1;
                        verb = verb[0..<2];
                }
        }
        
        // Check if this is a channel messsage.
        if (! mapp(channels) || undefinedp(channels[verb])) return 0;

        if (me->is_chatter())
                return notify_fail("ÁÄÌì»êÆÇÄ¿Ç°²»ÄÜÊ¹ÓÃ¸÷ÖÖÆµµÀ¡£\n");

        is_player = playerp(me);
        if (is_player && ! wizardp(me))
        {
                if (! me->query("registered"))
                        return notify_fail("Äã±ØÐëÔÚ×¢²áÒÔºó²ÅÄÜ¹»Ê¹ÓÃ¸÷ÖÖÆµµÀ¡£\n");
                /*
 		if (me->query("mud_age") < 1800 && me->query("monfee") < 11)
                        return notify_fail("Äã±ØÐëÔÚÍê³É×¢²áÎå·ÖÖÓÒÔºó²ÅÄÜÊ¹ÓÃÆµµÀ£¬Õâ¶Î"
                                           "Ê±¼äÄÚÇëÏÈÔÄ¶Á°ïÖú(help newbie)¡£\n");
                */                           
                if (channels[verb]["need_age"] && me->query("age") < 18)
                        return notify_fail("Äã±ØÐë³ÉÄêÒÔºó²ÅÄÜÊ¹ÓÃ" + channels[verb]["name"] +
                                           "ÆµµÀ¡£\n");
        }

        // now we can be sure it's indeed a channel message:
        if (! stringp(arg) || arg == "" || arg == " " ) arg = "...";

        if (ultrap(me))
        {
                if (verb == "chat" && ! me->query("env/no_autoultra"))
                        verb = "ultra";
        } else
                if (is_player && verb == "ultra")
                        return notify_fail("µÈÄã³ÉÁË´ó×ÚÊ¦ÔÙ"
                                           "Ê¹ÓÃÕâ¸öÆµµÀ°É£¡\n");

        // player broadcasting need consume jing
        if (userp(me) && ! wizardp(me) && verb == "rumor" &&
            ! objectp(present("rumor generator", me)))
                if (me->query("jing") > 50) me->add("jing", -random(36))
                        ; else
                return notify_fail("ÄãÒÑ¾­Ã»Á¦ÆøÉ¢²¥Ò¥ÑÔÁË£¡\n");

        if (userp(me) && me->ban_say(1)) return 0;

        // check if rumor or chat is blocked
        if (me->query("chblk_on"))
                return notify_fail("ÄãµÄÁÄÌìÆµµÀ¸ø¹Ø±ÕÁË£¡Î¨Ò»µÄ°ì·¨¾ÍÊÇÇëÇóÔÚÏßÍæ¼ÒÍ¶Æ±¿ªÍ¨¡£\n");

        if (me->query("doing") == "scheme")
        {
                if (me->query("jing") < 100)
                        return notify_fail("ÄãÏÖÔÚµÄ¾«Éñ²»¼Ã£¬µÈÒ»»á¶ù°É¡£\n");
                me->add("jing", -50);
        }

        // if (userp(me))
        if (me->is_character() && living(me))
        {
                if (time() - me->query_temp("last_use_channel") < 4)
                {
                        if (me->query_temp("last_message") == arg)
                                return notify_fail("²»ÒªÔÚ¶ÌÆÚÄÚÊ¹ÓÃÆµµÀ"
                                                   "·¢²¼ÖØ¸´µÄÐÅÏ¢¡£\n");
                        me->set_temp("last_message", arg);
                } else
                {
                        me->set_temp("last_message", arg);
                        me->set_temp("last_use_channel", time());
                }

                switch (channels[verb]["only"])
                {
                case "imm":
                        if (wiz_level(me) < 1)
                                return 0;
                        break;
                        
                case "wiz":
                        if (wiz_level(me) < 3)
                                return 0;
                        break;

                case "arch":
                        if (wiz_level(me) < 4)
                                return 0;
                        break;

                case "party":
                        if (! (party = me->query("bunch/bunch_name")))
                                return notify_fail("Äã»¹ÊÇÏÈ¼ÓÈëÒ»¸ö°ïÅÉÔÙËµ°É¡£\n");

                        if (strlen(party) == 4)
                        {
                                party = party[0..1] + " £  " +
                                        party[2..3];
                        }

                        if (strlen(party) == 6)
                        {
                                party = party[0..1] + " " +
                                        party[2..3] + " " +
                                        party[4..5];
                        }
                        channels[verb]["msg_speak"] = HIG "¡¾" + party +
                                                      "¡¿%s£º%s\n" NOR;
                        channels[verb]["msg_emote"] = HIG "¡¾" + party +
                                                      "¡¿%s" NOR;
                        break;

                case "family":
                        if (! (family = me->query("family/family_name")))
                                return notify_fail("Äã»¹ÊÇÏÈ¼ÓÈëÒ»¸öÃÅÅÉÔÙËµ°É¡£\n");

                        if (strlen(family) == 4)
                        {
                                family = family[0..1] + " £  " +
                                         family[2..3];
                        }

                        if (strlen(family) == 6)
                        {
                                family = family[0..1] + " " +
                                         family[2..3] + " " +
                                         family[4..5];
                        }
                        channels[verb]["msg_speak"] = HIG "¡¾" + family +
                                                      "¡¿%s£º%s\n" NOR;
                        channels[verb]["msg_emote"] = HIG "¡¾" + family +
                                                      "¡¿%s" NOR;
                        break;

                case "league":
                        if (! (fname = me->query("league/league_name")))
                                return notify_fail("Äã»¹ÊÇÏÈºÍ±ðÈË½áÒåÍ¬ÃËÔÙËµ°É¡£\n");

                        switch (strlen(fname))
                        {
                        case 4:
                                fname = "¡¾ " + fname[0..1] + "  " + fname[2..3] + " ¡¿";
                                break;
        
                        case 6:
                                fname = "¡¾ " + fname + " ¡¿";
                                break;
        
                        case 8:
                                fname = "¡¾" + fname + "¡¿";
                                break;
        
                        case 10:
                                fname = "¡¾" + fname[0..7] + "¡¿";
                                break;
                        }
                        channels[verb]["msg_speak"] = HIR + fname + "%s£º%s\n" NOR;
                        channels[verb]["msg_emote"] = HIR + fname + "%s" NOR;
                        break;
                }
        }

        if (verb == "shout")
        {
                if (! arg) return notify_fail("ÄãÏëÒª´ó½ÐÊ²Ã´£¿\n");
            
                if (! wizardp(me) && userp(me))
                {
                        if (me->query("neili") < 500)
                                return notify_fail("ÄãµÄÄÚÁ¦Ì«²î£¬ÎÞ·¨º°³öÄÇÃ´´óµÄÉùÒô¡£\n");
                    
                        me->add("neili", - (random(200) + 300));
                }
                
                who = me->name(1) + "[" + me->query("id") + "]";
                msg = sprintf(channels[verb]["msg_speak"], who, arg);
                // msg = HIW + me->name(1) + "×ÝÉù³¤Ð¥£º" + arg + "\n" + NOR;
                shout(msg);
                write(HIW + "Äã×ÝÉù³¤Ð¥£º" + arg + "\n" + NOR);
                channel_log(msg, verb, me);
                return 1;
        }

        // If we speaks something in this channel, then must tune it in.
        if (userp(me))
        {
                if (! pointerp(tuned_ch = me->query("channels")))
                {
                        me->set("channels", ({ verb }));
                        write("Äã´ò¿ªÁË" + channels[verb]["name"] + "ÆµµÀ¡£\n");
                } else
                if (member_array(verb, tuned_ch) == -1)
                {
                        me->set("channels", tuned_ch + ({ verb }));
                        write("Äã´ò¿ªÁË" + channels[verb]["name"] + "ÆµµÀ¡£\n");
                }

                if (channels[verb]["for_listen"])
                {
                        write("Õâ¸öÆµµÀÖ»ÄÜÓÃÀ´ÌýÈ¡±ðÈËµÄ½»Ì¸¡£\n");
                        return 1;
                }
        }

        // Support of channel emote
        if (emote && me->is_character())
        {
                string vb, emote_arg, mud;

                if (undefinedp(channels[verb]["msg_emote"]))
                        return notify_fail("Õâ¸öÆµµÀ²»Ö§³Ö±íÇé¶¯´Ê¡£\n");

                if (sscanf(arg, "%s %s", vb, emote_arg) != 2)
                {
                        vb = arg;
                        emote_arg = "";
                }

                // internet channel emote
                if (channels[verb]["intermud_emote"])
                {
                        if (sscanf(emote_arg, "%s@%s", emote_arg, mud) == 2 &&
                            htonn(mud) != mud_nname())
                        {
                                REMOTE_Q->send_remote_q(mud, verb, me->query("id"), emote_arg, vb);
                                write("ÍøÂ·Ñ¶Ï¢ÒÑËÍ³ö£¬ÇëÉÔºò¡£\n");
                                return 1;
                        }

                        local = sprintf("%s(%s@%s)", me->name(1), capitalize(me->query("id")),
                                                     upper_case(INTERMUD_MUD_NAME));
                        imsg = EMOTE_D->do_emote(me, vb, emote_arg, 3, local,
                                                 channels[verb]["msg_color"]);
                        if (stringp(imsg))
                                arg = replace_string(imsg, local, me->name());
                        else
                                arg = 0;
                } else
                if (verb == "rumor")
                        arg = EMOTE_D->do_emote(me, vb, emote_arg, 2,
                                        channels[verb]["anonymous"],
                                        channels[verb]["msg_color"]);
                else
                        arg = EMOTE_D->do_emote(me, vb, emote_arg, 1,
                                        0, channels[verb]["msg_color"]);
        
                if (! arg && emote == 2)
                        arg = (channels[verb]["anonymous"] ? channels[verb]["anonymous"]
                                                           : me->name(channels[verb]["name_raw"])) +
                                                             vb + "\n";
        
                if (! arg)
                        return 0;
        }

        // Support of channel myemote
        if (myemote && me->is_character())
        {
                 if (undefinedp(channels[verb]["msg_emote"]))
                        return notify_fail("Õâ¸öÆµµÀ²»Ö§³Ö×Ô¶¨Òå±íÇé¡£\n");

                // internet channel emote
                if (channels[verb]["intermud_emote"])
                        return notify_fail("Õâ¸öÆµµÀ²»Ö§³Ö×Ô¶¨Òå±íÇé¡£\n");
                        
                if (stringp(arg) && 
                    ((strsrch(arg, "[") != -1) ||
                     (strsrch(arg, "]") != -1)) )
                        return notify_fail("Õâ¸öÆµµÀ½ûÖ¹Ê¹ÓÃ¡®[¡¯¡¢¡®]¡¯µÈ×Ö·û¡£\n");
        }
        
        // Make the identity of speaker.
        if (channels[verb]["anonymous"] && (! userp(me) || (emote || check_bad_words(me, arg))))
        {
                who = channels[verb]["anonymous"];
        } else
        if (is_player || ! stringp(who = me->query("channel_id")))
        {
                who = me->name(channels[verb]["name_raw"]);
                if (who == me->name(1))
                        who += channels[verb]["msg_color"] +
                               "[" + capitalize(me->query("id")) + "]";
                if (who[0] == 27) who = NOR + who;
                who += channels[verb]["msg_color"];
        }

        // Ok, now send the message to those people listening us.
        obs = all_interactive();
        if (stringp(channels[verb]["only"]))
                obs = filter_array(obs, (: filter_listener :),
                                   channels[verb]["only"], me);

        if (! arg || arg == "" || arg == " ") arg = "...";

        if (emote)
        {
                string localmsg = arg;
                string ecol = channels[verb]["msg_color"];
                if (emote == 2 && ! arg)
                        arg = me->name(channels[verb]["name_raw"]) +
                              ecol + "[" + me->query("id") + "@" +
                              INTERMUD_MUD_NAME + "]" + arg;
                if (! stringp(arg)) return 0;

                if (channels[verb]["msg_emote"])
                        localmsg = remove_addresses(arg, 0); // 98-1-22 14:30

                if (channels[verb]["omit_address"])
                        localmsg = remove_addresses(arg, 1);
                else
                if (channels[verb]["intermud_emote"])
                        localmsg = remove_addresses(arg, 0);

                if (! stringp(localmsg)) return 0;
                msg = sprintf(channels[verb]["msg_emote"],
                              sprintf(localmsg, ecol, ecol, ecol));
        } else if (myemote)
        {
                if (channels[verb]["anonymous"] && ! userp(me))
                        arg = channels[verb]["anonymous"] + arg + "\n";
                else
                        arg = me->query("name") + arg + "\n";
                msg = sprintf(channels[verb]["msg_emote"], arg);
        } else
                msg = sprintf(channels[verb]["msg_speak"], who, arg);

        if (channels[verb]["anonymous"] && userp(me))
        {
                do_channel(this_object(), "sys",
                           sprintf("%s(%s)ÕýÔÚÏò%sÆµµÀ·¢³öÐÅÏ¢¡£",
                              me->query("name"), me->query("id"), verb));
                SPECIAL_NPC->receive_report(me, verb);
        }
        
        tobs = filter_array(obs, (: $1->query_temp("tomud") :));
        pobs = obs - tobs;
        message("channel:" + ((verb == "ultra") ? "chat" : verb), msg, pobs);
        msg = replace_string(msg, "\n[2;37;0m", ""); 
        msg += NOR;
        message("channel:" + ((verb == "ultra") ? "chat" : verb), msg, tobs);
        channel_log(msg, verb, me);

        /*
        if (! check_bad_words(me, msg))
        {
                if (! me->query("badwords") || me->query("badwords") < 2)
                {
                        me->ban_say_until(60, "ÓÉÓÚÄãÑÔÓïÖÐ´øÓÐÎÛ»àÑÔ´Ê£¬ÄãËùÓÐ¹«¿ªÁÄÌìÆµµÀÔÝÊ±±»¹Ø±Õ"); 

                        message("channel:chat",
                                        HIR "¡¾ÏµÍ³Í¨¸æ¡¿Íæ¼Ò" + me->query("name") + 
                                        "ÑÔÓïÖÐ´øÓÐÎÛ»àÑÔ´Ê£¬ÔÝÊ±¹Ø±ÕÆäËùÓÐ¹«¿ªÁÄÌìÆµµÀ£¬²¢¼ÇÂ¼ÔÚ°¸£¡\n" NOR, users());
                        me->add("badwords", 1);
                }
                else
                {                               
                        message("channel:chat",
                                        HIR"¡¾ÏµÍ³Í¨¸æ¡¿Íæ¼Ò" + me->query("name") + 
                                        "Á¬ÐøÈý´ÎÑÔÓïÖÐ´øÓÐÎÛ»àÑÔ´Ê£¬±»ÔÝÊ±¼à½û£¬²¢¼ÇÂ¼ÔÚ°¸£¬µÈºò´¦Àí£¡\n" NOR, users());
                        me->delete("badwords"); 
                        // me->get_into_prison(0, 0, 180);                                
                }
        }
        */
                
        if (arrayp(channels[verb]["extra_listener"]) ) 
        {
                channels[verb]["extra_listener"] -= ({ 0 });
                if (sizeof(channels[verb]["extra_listener"]))
                        channels[verb]["extra_listener"]->relay_channel(me, verb, arg);
        }
        
        if (! undefinedp(channels[verb]["intermud"]) && me->is_character())
        {
                channels[verb]["intermud"]->send_msg(channels[verb]["intermud_channel"],
                                                     me->query("id"), me->name(1),
                                                     imsg ? imsg : arg, emote,
                                                     channels[verb]["filter"]);
        }

        return 1;
}

int filter_listener(object ppl, string only, object me)
{
        // Don't bother those in the login limbo.
        if (! environment(ppl)) return 0;

        switch (only)
        {
        case "imm":
                return (wiz_level(ppl) >= 1);
                
        case "arch":
                return (wiz_level(ppl) >= 4);

        case "wiz":
                return (wiz_level(ppl) >= 3);

        case "family":
                return (wizardp(ppl) || ppl->query("family/family_name") == me->query("family/family_name"));

        case "party":
                return (wizardp(ppl) || ppl->query("bunch/bunch_name") == me->query("bunch/bunch_name"));

        case "league":
                return (wizardp(ppl) || ppl->query("league/league_name") == me->query("league/league_name"));
        }

        return 1;
}

void register_relay_channel(string channel)
{
        object ob;
        ob = previous_object();
        
        if (undefinedp(channels[channel]) || ! ob) 
                return;
        if (arrayp(channels[channel]["extra_listener"])) 
        {
                if (member_array(ob, channels[channel]["extra_listener"]) >= 0) 
                        return;
                channels[channel]["extra_listener"] += ({ ob });
        }
        else    channels[channel]["extra_listener"] = ({ ob });
}

string remove_addresses(string msg, int all)
{
        int i;
        mixed tmp;
        string pattern;

        if (! stringp(msg)) return msg;
        if (all)
                pattern = "[(][A-Za-z]+@[a-zA-Z]+[0-9]+[.]?[)]";
        else
                pattern = "[(][A-Za-z]+@" + INTERMUD_MUD_NAME + "[)]";

        tmp = reg_assoc(msg, ({ pattern }), ({ 1 }));

        if (! arrayp(tmp)) return msg;
        msg = "";
        for (i = 0; i < sizeof(tmp[0]); i++)
                if (tmp[1][i] == 0) msg += tmp[0][i];
        return msg;
}

private int check_bad_words(object user, string msg)
{
        int i;
        string old_msg = msg;

        msg = replace_string(msg,"Òæ»ú","");
        msg = replace_string(msg,"ç¼Ë¿","");
        msg = replace_string(msg,"¹æ»¹","");
        msg = replace_string(msg,"£á","a");
        msg = replace_string(msg,"£â","b");
        msg = replace_string(msg,"£ã","c");
        msg = replace_string(msg,"£ä","d");
        msg = replace_string(msg,"£å","e");
        msg = replace_string(msg,"£æ","f");
        msg = replace_string(msg,"£ç","g");
        msg = replace_string(msg,"£è","h");
        msg = replace_string(msg,"£é","i");
        msg = replace_string(msg,"£ê","j");
        msg = replace_string(msg,"£ë","k");
        msg = replace_string(msg,"£ì","l");
        msg = replace_string(msg,"£í","m");
        msg = replace_string(msg,"£î","n");
        msg = replace_string(msg,"£ï","o");
        msg = replace_string(msg,"£ð","p");
        msg = replace_string(msg,"£ñ","q");
        msg = replace_string(msg,"£ò","r");
        msg = replace_string(msg,"£ó","s");
        msg = replace_string(msg,"£ô","t");
        msg = replace_string(msg,"£õ","u");
        msg = replace_string(msg,"£ö","v");
        msg = replace_string(msg,"£÷","w");
        msg = replace_string(msg,"£ø","x");
        msg = replace_string(msg,"£ù","y");
        msg = replace_string(msg,"£ú","z");
        msg = lower_case(msg);
        msg = replace_string(msg,",","");
        msg = replace_string(msg,".","");
        msg = replace_string(msg,";","");
        msg = replace_string(msg,"£¬","");
        msg = replace_string(msg,"¡£","");
        msg = replace_string(msg,"£»","");
        msg = replace_string(msg," ","");
        msg = replace_string(msg,"£ ","");
        msg = replace_string(msg,"'","");
        msg = replace_string(msg,"\"","");
        msg = replace_string(msg,"¡±","");
        msg = replace_string(msg,"¡°","");
        msg = replace_string(msg,"[","");
        msg = replace_string(msg,"]","");
        msg = replace_string(msg,"¡º","");
        msg = replace_string(msg,"¡»","");
        msg = replace_string(msg,"¡¾","");
        msg = replace_string(msg,"¡¿","");
        msg = replace_string(msg,"¡¯","");
        msg = replace_string(msg,"¡®","");
        
        for (i = 0; i < sizeof(bad_words);i ++)
        {
                if (strsrch(msg, bad_words[i]) != -1)
                {
                        log_file("channel/bad_word",sprintf("%s(%s)ÓÚ%sÉæÏÓ½²Ôà»°£º\n%s\n",
                                                             user->name(1),
                                                             user->query("id"),
                                                             ctime(time()),
                                                             filter_color(old_msg)) );
                        return 0;
                        break;
                }
        }
        return 1;
}
