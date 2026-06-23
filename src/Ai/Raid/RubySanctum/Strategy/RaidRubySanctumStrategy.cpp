#include "RaidRubySanctumStrategy.h"

#include "Strategy.h"

void RaidRubySanctumStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("ruby sanctum baltharus blade tempest",
        { NextAction("ruby sanctum move from baltharus", ACTION_EMERGENCY + 2) }));

    triggers.push_back(new TriggerNode("ruby sanctum saviana conflagration",
        { NextAction("ruby sanctum move from group conflagration", ACTION_EMERGENCY + 3) }));

    triggers.push_back(new TriggerNode("ruby sanctum halion mark",
        { NextAction("ruby sanctum move from group halion mark", ACTION_EMERGENCY + 3) }));

    triggers.push_back(new TriggerNode("ruby sanctum halion meteor flame",
        { NextAction("ruby sanctum avoid meteor flame", ACTION_EMERGENCY + 4) }));

    triggers.push_back(new TriggerNode("ruby sanctum zarithrian flamecaller",
        { NextAction("ruby sanctum attack flamecaller", ACTION_RAID + 1) }));
}
