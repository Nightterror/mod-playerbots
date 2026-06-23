#ifndef _PLAYERBOT_RAIDSUNWELLTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDSUNWELLTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "RaidSunwellTriggers.h"

class RaidSunwellTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidSunwellTriggerContext()
    {
        creators["sunwell brutallus burn"] = &RaidSunwellTriggerContext::brutallus_burn;
        creators["sunwell felmyst encapsulate"] = &RaidSunwellTriggerContext::felmyst_encapsulate;
        creators["sunwell felmyst vapor"] = &RaidSunwellTriggerContext::felmyst_vapor;
        creators["sunwell twins spread"] = &RaidSunwellTriggerContext::twins_spread;
        creators["sunwell twins wrong target"] = &RaidSunwellTriggerContext::twins_wrong_target;
        creators["sunwell kj fire bloom"] = &RaidSunwellTriggerContext::kj_fire_bloom;
        creators["sunwell kalecgos curse"] = &RaidSunwellTriggerContext::kalecgos_curse;
        creators["sunwell singularity"] = &RaidSunwellTriggerContext::singularity;
        creators["sunwell shield orb"] = &RaidSunwellTriggerContext::shield_orb;
        creators["sunwell priority add"] = &RaidSunwellTriggerContext::priority_add;
        creators["sunwell kalecgos realm"] = &RaidSunwellTriggerContext::kalecgos_realm;
    }

private:
    static Trigger* brutallus_burn(PlayerbotAI* ai) { return new SwBrutallusBurnTrigger(ai); }
    static Trigger* felmyst_encapsulate(PlayerbotAI* ai) { return new SwFelmystEncapsulateTrigger(ai); }
    static Trigger* felmyst_vapor(PlayerbotAI* ai) { return new SwFelmystVaporTrigger(ai); }
    static Trigger* twins_spread(PlayerbotAI* ai) { return new SwTwinsSpreadTrigger(ai); }
    static Trigger* twins_wrong_target(PlayerbotAI* ai) { return new SwTwinsWrongTargetTrigger(ai); }
    static Trigger* kj_fire_bloom(PlayerbotAI* ai) { return new SwKjFireBloomTrigger(ai); }
    static Trigger* kalecgos_curse(PlayerbotAI* ai) { return new SwKalecgosCurseTrigger(ai); }
    static Trigger* singularity(PlayerbotAI* ai) { return new SwSingularityTrigger(ai); }
    static Trigger* shield_orb(PlayerbotAI* ai) { return new SwShieldOrbTrigger(ai); }
    static Trigger* priority_add(PlayerbotAI* ai) { return new SwPriorityAddTrigger(ai); }
    static Trigger* kalecgos_realm(PlayerbotAI* ai) { return new SwKalecgosRealmTrigger(ai); }
};

#endif
