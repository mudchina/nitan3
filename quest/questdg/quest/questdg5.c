#include <ansi.h>
#define QUESTDG_D(x)      ("/quest/questdg/quest/questdg" + x)

mapping query_questdg() 
{
        mapping questdg = ([]);

        if (random(50) == 25)
        	questdg = QUESTDG_D("7Ѱ")->query_questdg();
        else if (random(2) == 1)
                questdg = QUESTDG_D("5Ѱ")->query_questdg();
        else
	questdg = QUESTDG_D("5ɱ")->query_questdg();
        if (questdg["type"] == "Ѱ") 
        {
                if (random(5) == 3)
                {
                        questdg["type"] = "��";
                        questdg["name"] = "��ִ";
                }
        } 
        if (questdg["type"] == "ɱ") 
        {
                if (random(3) == 2)
                {
                        questdg["type"] = "��";
                }
        } 
        return questdg;
}
