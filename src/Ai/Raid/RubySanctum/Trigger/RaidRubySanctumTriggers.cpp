#include "RaidRubySanctumTriggers.h"

#include "Playerbots.h"
#include "RaidRubySanctumHelpers.h"

using namespace RubySanctumHelpers;

bool RsBaltharusBladeTempestTrigger::IsActive()
{
    if (bot->GetMapId() != RS_MAP_ID || botAI->IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "baltharus the warborn");
    if (!boss || !boss->IsAlive())
        return false;

    return boss->HasUnitState(UNIT_STATE_CASTING) &&
           boss->FindCurrentSpellBySpellId(SPELL_BLADE_TEMPEST);
}

bool RsSavianaConflagrationTrigger::IsActive()
{
    if (bot->GetMapId() != RS_MAP_ID)
        return false;

    return bot->HasAura(SPELL_CONFLAGRATION) || bot->HasAura(SPELL_FLAME_BEACON);
}

bool RsHalionMarkTrigger::IsActive()
{
    if (bot->GetMapId() != RS_MAP_ID)
        return false;

    return bot->HasAura(SPELL_FIERY_COMBUSTION) || bot->HasAura(SPELL_SOUL_CONSUMPTION);
}

bool RsHalionMeteorFlameTrigger::IsActive()
{
    if (bot->GetMapId() != RS_MAP_ID || botAI->IsTank(bot))
        return false;

    if (!AI_VALUE2(Unit*, "find target", "halion"))
        return false;

    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (ObjectGuid const& guid : npcs)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit->GetEntry() != NPC_METEOR_STRIKE_FLAME)
            continue;

        if (bot->GetDistance2d(unit) < 8.0f)
            return true;
    }

    return false;
}

bool RsZarithrianFlamecallerTrigger::IsActive()
{
    if (bot->GetMapId() != RS_MAP_ID || botAI->IsMainTank(bot))
        return false;

    if (!AI_VALUE2(Unit*, "find target", "general zarithrian"))
        return false;

    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (ObjectGuid const& guid : npcs)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit->GetEntry() != NPC_ONYX_FLAMECALLER)
            continue;

        if (unit->IsAlive() && unit->IsInCombat())
            return true;
    }

    return false;
}
