#ifndef _PLAYERBOT_RAIDAQ40TRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDAQ40TRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "RaidAq40Triggers.h"

class RaidAq40TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq40TriggerContext()
    {
        creators["aq40 skeram arcane explosion"] = &RaidAq40TriggerContext::skeram_arcane;
        creators["aq40 bug trio spread"] = &RaidAq40TriggerContext::bug_trio_spread;
        creators["aq40 sartura whirlwind"] = &RaidAq40TriggerContext::sartura_whirlwind;
        creators["aq40 huhuran noxious poison"] = &RaidAq40TriggerContext::huhuran_noxious;
        creators["aq40 viscidus spread"] = &RaidAq40TriggerContext::viscidus_spread;
        creators["aq40 viscidus slime"] = &RaidAq40TriggerContext::viscidus_slime;
        creators["aq40 twins blizzard"] = &RaidAq40TriggerContext::twins_blizzard;
        creators["aq40 twins arcane burst"] = &RaidAq40TriggerContext::twins_arcane_burst;
        creators["aq40 twins wrong target"] = &RaidAq40TriggerContext::twins_wrong_target;
        creators["aq40 twins veklor tank range"] = &RaidAq40TriggerContext::twins_veklor_tank;
        creators["aq40 ouro ground rupture"] = &RaidAq40TriggerContext::ouro_rupture;
        creators["aq40 cthun dark glare"] = &RaidAq40TriggerContext::cthun_dark_glare;
        creators["aq40 cthun green beam"] = &RaidAq40TriggerContext::cthun_green_beam;
        creators["aq40 priority add"] = &RaidAq40TriggerContext::priority_add;
    }

private:
    static Trigger* skeram_arcane(PlayerbotAI* ai) { return new Aq40SkeramArcaneExplosionTrigger(ai); }
    static Trigger* bug_trio_spread(PlayerbotAI* ai) { return new Aq40BugTrioSpreadTrigger(ai); }
    static Trigger* sartura_whirlwind(PlayerbotAI* ai) { return new Aq40SarturaWhirlwindTrigger(ai); }
    static Trigger* huhuran_noxious(PlayerbotAI* ai) { return new Aq40HuhuranNoxiousPoisonTrigger(ai); }
    static Trigger* viscidus_spread(PlayerbotAI* ai) { return new Aq40ViscidusSpreadTrigger(ai); }
    static Trigger* viscidus_slime(PlayerbotAI* ai) { return new Aq40ViscidusSlimeTrigger(ai); }
    static Trigger* twins_blizzard(PlayerbotAI* ai) { return new Aq40TwinsBlizzardTrigger(ai); }
    static Trigger* twins_arcane_burst(PlayerbotAI* ai) { return new Aq40TwinsArcaneBurstTrigger(ai); }
    static Trigger* twins_wrong_target(PlayerbotAI* ai) { return new Aq40TwinsWrongTargetTrigger(ai); }
    static Trigger* twins_veklor_tank(PlayerbotAI* ai) { return new Aq40TwinsVeklorTankRangeTrigger(ai); }
    static Trigger* ouro_rupture(PlayerbotAI* ai) { return new Aq40OuroGroundRuptureTrigger(ai); }
    static Trigger* cthun_dark_glare(PlayerbotAI* ai) { return new Aq40CthunDarkGlareTrigger(ai); }
    static Trigger* cthun_green_beam(PlayerbotAI* ai) { return new Aq40CthunGreenBeamTrigger(ai); }
    static Trigger* priority_add(PlayerbotAI* ai) { return new Aq40PriorityAddTrigger(ai); }
};

#endif
