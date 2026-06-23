#include "RaidTocStrategy.h"

#include "Strategy.h"

void RaidTocStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("toc faction champion",
        { NextAction("toc attack faction champion", ACTION_RAID + 5) }));

    triggers.push_back(new TriggerNode("toc jaraxxus add",
        { NextAction("toc attack priority add", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("toc priority add",
        { NextAction("toc attack priority add", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("toc twin shield",
        { NextAction("toc twin switch target", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("toc icehowl charge",
        { NextAction("toc move from icehowl", ACTION_EMERGENCY + 9) }));

    triggers.push_back(new TriggerNode("toc anub spike",
        { NextAction("toc move from icehowl", ACTION_EMERGENCY + 9) }));

    triggers.push_back(new TriggerNode("toc twin vortex",
        { NextAction("toc twin stop dps", ACTION_EMERGENCY + 8) }));

    triggers.push_back(new TriggerNode("toc fire bomb",
        { NextAction("toc move from fire bomb", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("toc legion flame",
        { NextAction("toc legion flame move from group", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode("toc anub cold",
        { NextAction("toc anub move from group", ACTION_EMERGENCY + 4) }));
}
