#include <ansi.h>
#define QUESTHS_D(x)      ("/quest/quesths/quest/quesths" + x)

mapping query_quesths() 
{
        mapping quesths = ([]);
        if (random(50) == 25)
        	quesths = QUESTHS_D("7Ѱ")->query_quesths();
        else if (random(2) == 1)
                quesths = QUESTHS_D("1Ѱ")->query_quesths();
        else
	quesths = QUESTHS_D("1ɱ")->query_quesths();
        if (quesths["type"] == "Ѱ") 
        {
                if (random(5) == 3)
                {
                        quesths["type"] = "��";
                        quesths["name"] = "��ִ";
                } else 
                if (random(5) == 2)
                {
                        quesths["type"] = "��";
                }
        } 
        return quesths;
}