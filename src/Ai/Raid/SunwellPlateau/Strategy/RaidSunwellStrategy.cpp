#include "RaidSunwellStrategy.h"

#include "Strategy.h"

void RaidSunwellStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("sunwell priority add",
        { NextAction("sunwell attack priority add", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("sunwell twins wrong target",
        { NextAction("sunwell twins switch target", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("sunwell kalecgos realm",
        { NextAction("sunwell kalecgos realm target", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("sunwell shield orb",
        { NextAction("sunwell move from shield orb", ACTION_EMERGENCY + 8) }));

    triggers.push_back(new TriggerNode("sunwell singularity",
        { NextAction("sunwell move from singularity", ACTION_EMERGENCY + 8) }));

    triggers.push_back(new TriggerNode("sunwell felmyst vapor",
        { NextAction("sunwell move from vapor", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("sunwell kj fire bloom",
        { NextAction("sunwell kj move from group", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode("sunwell kalecgos curse",
        { NextAction("sunwell kalecgos move from group", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode("sunwell felmyst encapsulate",
        { NextAction("sunwell felmyst move from group", ACTION_EMERGENCY + 5) }));

    triggers.push_back(new TriggerNode("sunwell twins spread",
        { NextAction("sunwell twins move from group", ACTION_EMERGENCY + 5) }));

    triggers.push_back(new TriggerNode("sunwell brutallus burn",
        { NextAction("sunwell brutallus move from group", ACTION_EMERGENCY + 4) }));
}
