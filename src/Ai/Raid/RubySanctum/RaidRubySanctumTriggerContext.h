#ifndef _PLAYERBOT_RAIDRUBYSANCTUMTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDRUBYSANCTUMTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "RaidRubySanctumTriggers.h"

class RaidRubySanctumTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidRubySanctumTriggerContext()
    {
        creators["ruby sanctum baltharus blade tempest"] =
            &RaidRubySanctumTriggerContext::baltharus_blade_tempest;
        creators["ruby sanctum saviana conflagration"] =
            &RaidRubySanctumTriggerContext::saviana_conflagration;
        creators["ruby sanctum halion mark"] =
            &RaidRubySanctumTriggerContext::halion_mark;
        creators["ruby sanctum halion meteor flame"] =
            &RaidRubySanctumTriggerContext::halion_meteor_flame;
        creators["ruby sanctum zarithrian flamecaller"] =
            &RaidRubySanctumTriggerContext::zarithrian_flamecaller;
    }

private:
    static Trigger* baltharus_blade_tempest(PlayerbotAI* ai)
    {
        return new RsBaltharusBladeTempestTrigger(ai);
    }
    static Trigger* saviana_conflagration(PlayerbotAI* ai)
    {
        return new RsSavianaConflagrationTrigger(ai);
    }
    static Trigger* halion_mark(PlayerbotAI* ai) { return new RsHalionMarkTrigger(ai); }
    static Trigger* halion_meteor_flame(PlayerbotAI* ai)
    {
        return new RsHalionMeteorFlameTrigger(ai);
    }
    static Trigger* zarithrian_flamecaller(PlayerbotAI* ai)
    {
        return new RsZarithrianFlamecallerTrigger(ai);
    }
};

#endif
