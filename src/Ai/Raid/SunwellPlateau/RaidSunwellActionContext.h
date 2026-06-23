#ifndef _PLAYERBOT_RAIDSUNWELLACTIONCONTEXT_H
#define _PLAYERBOT_RAIDSUNWELLACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidSunwellActions.h"

class RaidSunwellActionContext : public NamedObjectContext<Action>
{
public:
    RaidSunwellActionContext()
    {
        creators["sunwell brutallus move from group"] = &RaidSunwellActionContext::brutallus_spread;
        creators["sunwell felmyst move from group"] = &RaidSunwellActionContext::felmyst_spread;
        creators["sunwell move from vapor"] = &RaidSunwellActionContext::move_vapor;
        creators["sunwell twins move from group"] = &RaidSunwellActionContext::twins_spread;
        creators["sunwell twins switch target"] = &RaidSunwellActionContext::twins_switch;
        creators["sunwell kj move from group"] = &RaidSunwellActionContext::kj_spread;
        creators["sunwell kalecgos move from group"] = &RaidSunwellActionContext::kalecgos_spread;
        creators["sunwell move from singularity"] = &RaidSunwellActionContext::move_singularity;
        creators["sunwell move from shield orb"] = &RaidSunwellActionContext::move_shield_orb;
        creators["sunwell attack priority add"] = &RaidSunwellActionContext::attack_priority_add;
        creators["sunwell kalecgos realm target"] = &RaidSunwellActionContext::kalecgos_realm;
    }

private:
    static Action* brutallus_spread(PlayerbotAI* ai)
    {
        return new SwMoveFromGroupAction(ai, "sunwell brutallus move from group");
    }
    static Action* felmyst_spread(PlayerbotAI* ai)
    {
        return new SwMoveFromGroupAction(ai, "sunwell felmyst move from group", 26.0f);
    }
    static Action* move_vapor(PlayerbotAI* ai)
    {
        return new SwMoveFromUnitAction(ai, "sunwell move from vapor", 25265, 30.0f, 15.0f);
    }
    static Action* twins_spread(PlayerbotAI* ai)
    {
        return new SwMoveFromGroupAction(ai, "sunwell twins move from group");
    }
    static Action* twins_switch(PlayerbotAI* ai) { return new SwTwinsSwitchTargetAction(ai); }
    static Action* kj_spread(PlayerbotAI* ai)
    {
        return new SwMoveFromGroupAction(ai, "sunwell kj move from group", 25.0f);
    }
    static Action* kalecgos_spread(PlayerbotAI* ai)
    {
        return new SwMoveFromGroupAction(ai, "sunwell kalecgos move from group");
    }
    static Action* move_singularity(PlayerbotAI* ai)
    {
        return new SwMoveFromUnitAction(ai, "sunwell move from singularity", 25855, 40.0f, 18.0f);
    }
    static Action* move_shield_orb(PlayerbotAI* ai)
    {
        return new SwMoveFromUnitAction(ai, "sunwell move from shield orb", 25502, 50.0f, 12.0f);
    }
    static Action* attack_priority_add(PlayerbotAI* ai) { return new SwAttackPriorityAddAction(ai); }
    static Action* kalecgos_realm(PlayerbotAI* ai) { return new SwKalecgosRealmTargetAction(ai); }
};

#endif
