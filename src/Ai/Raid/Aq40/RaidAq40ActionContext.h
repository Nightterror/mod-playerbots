#ifndef _PLAYERBOT_RAIDAQ40ACTIONCONTEXT_H
#define _PLAYERBOT_RAIDAQ40ACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidAq40Actions.h"

class RaidAq40ActionContext : public NamedObjectContext<Action>
{
public:
    RaidAq40ActionContext()
    {
        creators["aq40 skeram move away"] = &RaidAq40ActionContext::skeram_move_away;
        creators["aq40 bug trio move from group"] = &RaidAq40ActionContext::bug_trio_spread;
        creators["aq40 sartura move away"] = &RaidAq40ActionContext::sartura_move_away;
        creators["aq40 huhuran move from group"] = &RaidAq40ActionContext::huhuran_spread;
        creators["aq40 viscidus move from group"] = &RaidAq40ActionContext::viscidus_spread;
        creators["aq40 move from slime"] = &RaidAq40ActionContext::move_from_slime;
        creators["aq40 twins move from group"] = &RaidAq40ActionContext::twins_spread;
        creators["aq40 twins move from veklor"] = &RaidAq40ActionContext::twins_move_veklor;
        creators["aq40 twins switch target"] = &RaidAq40ActionContext::twins_switch;
        creators["aq40 twins veklor tank range"] = &RaidAq40ActionContext::twins_veklor_tank;
        creators["aq40 ouro move from group"] = &RaidAq40ActionContext::ouro_spread;
        creators["aq40 cthun move from dark glare"] = &RaidAq40ActionContext::cthun_dark_glare;
        creators["aq40 cthun move from green beam"] = &RaidAq40ActionContext::cthun_green_beam;
        creators["aq40 attack priority add"] = &RaidAq40ActionContext::attack_priority_add;
    }

private:
    static Action* skeram_move_away(PlayerbotAI* ai) { return new Aq40SkeramMoveAwayAction(ai); }
    static Action* bug_trio_spread(PlayerbotAI* ai)
    {
        return new Aq40MoveFromGroupSpreadAction(ai, "aq40 bug trio move from group");
    }
    static Action* sartura_move_away(PlayerbotAI* ai) { return new Aq40SarturaMoveAwayAction(ai); }
    static Action* huhuran_spread(PlayerbotAI* ai)
    {
        return new Aq40MoveFromGroupSpreadAction(ai, "aq40 huhuran move from group");
    }
    static Action* viscidus_spread(PlayerbotAI* ai)
    {
        return new Aq40MoveFromGroupSpreadAction(ai, "aq40 viscidus move from group");
    }
    static Action* move_from_slime(PlayerbotAI* ai) { return new Aq40MoveFromSlimeAction(ai); }
    static Action* twins_spread(PlayerbotAI* ai)
    {
        return new Aq40MoveFromGroupSpreadAction(ai, "aq40 twins move from group", 20.0f);
    }
    static Action* twins_move_veklor(PlayerbotAI* ai) { return new Aq40TwinsMoveFromVeklorAction(ai); }
    static Action* twins_switch(PlayerbotAI* ai) { return new Aq40TwinsSwitchTargetAction(ai); }
    static Action* twins_veklor_tank(PlayerbotAI* ai) { return new Aq40TwinsVeklorTankRangeAction(ai); }
    static Action* ouro_spread(PlayerbotAI* ai)
    {
        return new Aq40MoveFromGroupSpreadAction(ai, "aq40 ouro move from group");
    }
    static Action* cthun_dark_glare(PlayerbotAI* ai) { return new Aq40CthunMoveFromBeamAction(ai); }
    static Action* cthun_green_beam(PlayerbotAI* ai) { return new Aq40CthunMoveFromGreenBeamAction(ai); }
    static Action* attack_priority_add(PlayerbotAI* ai) { return new Aq40AttackPriorityAddAction(ai); }
};

#endif
