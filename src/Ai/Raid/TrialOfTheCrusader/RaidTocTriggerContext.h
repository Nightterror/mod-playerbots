#ifndef _PLAYERBOT_RAIDTOCTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDTOCTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "RaidTocTriggers.h"

class RaidTocTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidTocTriggerContext()
    {
        creators["toc icehowl charge"] = &RaidTocTriggerContext::icehowl_charge;
        creators["toc fire bomb"] = &RaidTocTriggerContext::fire_bomb;
        creators["toc legion flame"] = &RaidTocTriggerContext::legion_flame;
        creators["toc jaraxxus add"] = &RaidTocTriggerContext::jaraxxus_add;
        creators["toc faction champion"] = &RaidTocTriggerContext::faction_champion;
        creators["toc twin vortex"] = &RaidTocTriggerContext::twin_vortex;
        creators["toc twin shield"] = &RaidTocTriggerContext::twin_shield;
        creators["toc anub spike"] = &RaidTocTriggerContext::anub_spike;
        creators["toc anub cold"] = &RaidTocTriggerContext::anub_cold;
        creators["toc priority add"] = &RaidTocTriggerContext::priority_add;
    }

private:
    static Trigger* icehowl_charge(PlayerbotAI* ai) { return new TocIcehowlChargeTrigger(ai); }
    static Trigger* fire_bomb(PlayerbotAI* ai) { return new TocFireBombTrigger(ai); }
    static Trigger* legion_flame(PlayerbotAI* ai) { return new TocLegionFlameTrigger(ai); }
    static Trigger* jaraxxus_add(PlayerbotAI* ai) { return new TocJaraxxusAddTrigger(ai); }
    static Trigger* faction_champion(PlayerbotAI* ai) { return new TocFactionChampionTrigger(ai); }
    static Trigger* twin_vortex(PlayerbotAI* ai) { return new TocTwinVortexTrigger(ai); }
    static Trigger* twin_shield(PlayerbotAI* ai) { return new TocTwinShieldTrigger(ai); }
    static Trigger* anub_spike(PlayerbotAI* ai) { return new TocAnubSpikeTrigger(ai); }
    static Trigger* anub_cold(PlayerbotAI* ai) { return new TocAnubColdTrigger(ai); }
    static Trigger* priority_add(PlayerbotAI* ai) { return new TocPriorityAddTrigger(ai); }
};

#endif
