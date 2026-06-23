#ifndef _PLAYERBOT_RAIDTOCACTIONCONTEXT_H
#define _PLAYERBOT_RAIDTOCACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidTocActions.h"

class RaidTocActionContext : public NamedObjectContext<Action>
{
public:
    RaidTocActionContext()
    {
        creators["toc move from icehowl"] = &RaidTocActionContext::move_icehowl;
        creators["toc move from fire bomb"] = &RaidTocActionContext::move_fire_bomb;
        creators["toc legion flame move from group"] = &RaidTocActionContext::legion_flame;
        creators["toc anub move from group"] = &RaidTocActionContext::anub_cold;
        creators["toc attack priority add"] = &RaidTocActionContext::attack_priority_add;
        creators["toc attack faction champion"] = &RaidTocActionContext::attack_champion;
        creators["toc twin switch target"] = &RaidTocActionContext::twin_switch;
        creators["toc twin stop dps"] = &RaidTocActionContext::twin_stop_dps;
    }

private:
    static Action* move_icehowl(PlayerbotAI* ai) { return new TocMoveFromIcehowlAction(ai); }
    static Action* move_fire_bomb(PlayerbotAI* ai) { return new TocMoveFromFireBombAction(ai); }
    static Action* legion_flame(PlayerbotAI* ai)
    {
        return new TocMoveFromGroupAction(ai, "toc legion flame move from group", 26.0f);
    }
    static Action* anub_cold(PlayerbotAI* ai)
    {
        return new TocMoveFromGroupAction(ai, "toc anub move from group");
    }
    static Action* attack_priority_add(PlayerbotAI* ai) { return new TocAttackPriorityAddAction(ai); }
    static Action* attack_champion(PlayerbotAI* ai) { return new TocAttackFactionChampionAction(ai); }
    static Action* twin_switch(PlayerbotAI* ai) { return new TocTwinSwitchTargetAction(ai); }
    static Action* twin_stop_dps(PlayerbotAI* ai) { return new TocTwinStopDpsAction(ai); }
};

#endif
