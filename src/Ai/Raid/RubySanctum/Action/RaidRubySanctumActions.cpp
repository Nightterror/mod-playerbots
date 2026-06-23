#include "RaidRubySanctumActions.h"

#include "Playerbots.h"
#include "RaidRubySanctumHelpers.h"

using namespace RubySanctumHelpers;

static constexpr float BLADE_TEMPEST_DISTANCE = 18.0f;
static constexpr float CONFLAGRATION_SPREAD = 22.0f;
static constexpr float HALION_MARK_SPREAD = 25.0f;
static constexpr float METEOR_FLAME_RADIUS = 10.0f;

bool RsMoveFromBaltharusAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "baltharus the warborn");
    if (!boss)
        return false;

    float distToTravel = BLADE_TEMPEST_DISTANCE - bot->GetDistance2d(boss);
    if (distToTravel <= 0)
        return false;

    bot->AttackStop();
    bot->InterruptNonMeleeSpells(false);
    return MoveAway(boss, distToTravel);
}

bool RsMoveFromGroupConflagrationAction::Execute(Event /*event*/)
{
    return MoveFromGroup(CONFLAGRATION_SPREAD);
}

bool RsMoveFromGroupHalionMarkAction::Execute(Event /*event*/)
{
    return MoveFromGroup(HALION_MARK_SPREAD);
}

bool RsAvoidMeteorFlameAction::Execute(Event /*event*/)
{
    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (ObjectGuid const& guid : npcs)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit->GetEntry() != NPC_METEOR_STRIKE_FLAME)
            continue;

        float currentDistance = bot->GetDistance2d(unit);
        if (currentDistance < METEOR_FLAME_RADIUS)
            return MoveAway(unit, METEOR_FLAME_RADIUS - currentDistance);
    }

    return false;
}

bool RsAttackFlamecallerAction::Execute(Event /*event*/)
{
    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    Unit* flamecaller = nullptr;
    float nearestDistance = 200.0f;

    for (ObjectGuid const& guid : npcs)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit->GetEntry() != NPC_ONYX_FLAMECALLER || !unit->IsAlive())
            continue;

        float distance = bot->GetDistance(unit);
        if (distance < nearestDistance)
        {
            nearestDistance = distance;
            flamecaller = unit;
        }
    }

    if (!flamecaller)
        return false;

    if (AI_VALUE(Unit*, "current target") == flamecaller)
        return false;

    return Attack(flamecaller);
}
