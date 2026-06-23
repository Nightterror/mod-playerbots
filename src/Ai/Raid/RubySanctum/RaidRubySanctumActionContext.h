#ifndef _PLAYERBOT_RAIDRUBYSANCTUMACTIONCONTEXT_H
#define _PLAYERBOT_RAIDRUBYSANCTUMACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidRubySanctumActions.h"

class RaidRubySanctumActionContext : public NamedObjectContext<Action>
{
public:
    RaidRubySanctumActionContext()
    {
        creators["ruby sanctum move from baltharus"] =
            &RaidRubySanctumActionContext::move_from_baltharus;
        creators["ruby sanctum move from group conflagration"] =
            &RaidRubySanctumActionContext::move_from_group_conflagration;
        creators["ruby sanctum move from group halion mark"] =
            &RaidRubySanctumActionContext::move_from_group_halion_mark;
        creators["ruby sanctum avoid meteor flame"] =
            &RaidRubySanctumActionContext::avoid_meteor_flame;
        creators["ruby sanctum attack flamecaller"] =
            &RaidRubySanctumActionContext::attack_flamecaller;
    }

private:
    static Action* move_from_baltharus(PlayerbotAI* ai)
    {
        return new RsMoveFromBaltharusAction(ai);
    }
    static Action* move_from_group_conflagration(PlayerbotAI* ai)
    {
        return new RsMoveFromGroupConflagrationAction(ai);
    }
    static Action* move_from_group_halion_mark(PlayerbotAI* ai)
    {
        return new RsMoveFromGroupHalionMarkAction(ai);
    }
    static Action* avoid_meteor_flame(PlayerbotAI* ai)
    {
        return new RsAvoidMeteorFlameAction(ai);
    }
    static Action* attack_flamecaller(PlayerbotAI* ai)
    {
        return new RsAttackFlamecallerAction(ai);
    }
};

#endif
