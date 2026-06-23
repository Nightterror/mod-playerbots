#include "RaidAq40Strategy.h"

#include "Strategy.h"

void RaidAq40Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("aq40 twins wrong target",
        { NextAction("aq40 twins switch target", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("aq40 twins veklor tank range",
        { NextAction("aq40 twins veklor tank range", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("aq40 priority add",
        { NextAction("aq40 attack priority add", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("aq40 cthun dark glare",
        { NextAction("aq40 cthun move from dark glare", ACTION_EMERGENCY + 9) }));

    triggers.push_back(new TriggerNode("aq40 cthun green beam",
        { NextAction("aq40 cthun move from green beam", ACTION_EMERGENCY + 8) }));

    triggers.push_back(new TriggerNode("aq40 sartura whirlwind",
        { NextAction("aq40 sartura move away", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("aq40 ouro ground rupture",
        { NextAction("aq40 ouro move from group", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("aq40 viscidus slime",
        { NextAction("aq40 move from slime", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode("aq40 twins arcane burst",
        { NextAction("aq40 twins move from veklor", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode("aq40 skeram arcane explosion",
        { NextAction("aq40 skeram move away", ACTION_EMERGENCY + 5) }));

    triggers.push_back(new TriggerNode("aq40 twins blizzard",
        { NextAction("aq40 twins move from group", ACTION_EMERGENCY + 5) }));

    triggers.push_back(new TriggerNode("aq40 huhuran noxious poison",
        { NextAction("aq40 huhuran move from group", ACTION_EMERGENCY + 4) }));

    triggers.push_back(new TriggerNode("aq40 viscidus spread",
        { NextAction("aq40 viscidus move from group", ACTION_EMERGENCY + 4) }));

    triggers.push_back(new TriggerNode("aq40 bug trio spread",
        { NextAction("aq40 bug trio move from group", ACTION_EMERGENCY + 3) }));
}
