#include "RaidSunwellActions.h"

#include "Playerbots.h"
#include "RaidSunwellHelpers.h"

using namespace SunwellHelpers;

bool SwMoveFromGroupAction::Execute(Event /*event*/)
{
    return MoveFromGroup(_distance);
}

bool SwMoveFromUnitAction::Execute(Event /*event*/)
{
    Unit* unit = FindHostileByEntry(bot, _entry, _searchRange);
    if (!unit)
        return false;

    float dist = _moveDistance - bot->GetDistance2d(unit);
    if (dist <= 0)
        return false;

    return MoveAway(unit, dist);
}

bool SwAttackPriorityAddAction::Execute(Event /*event*/)
{
    Unit* add = FindPriorityAdd(botAI, bot);
    if (!add)
        return false;

    return Attack(add);
}

bool SwTwinsSwitchTargetAction::Execute(Event /*event*/)
{
    Unit* current = AI_VALUE(Unit*, "current target");
    if (!current)
        return false;

    uint32 const otherEntry = current->GetEntry() == NPC_LADY_SACROLASH
        ? NPC_GRAND_WARLOCK_ALYTHESS
        : NPC_LADY_SACROLASH;

    Unit* other = FindHostileByEntry(bot, otherEntry);
    if (!other || HasWrongTwinAuraForTarget(bot, other))
        return false;

    return Attack(other);
}

bool SwKalecgosRealmTargetAction::isUseful()
{
    if (!InSunwell(bot))
        return false;

    if (bot->GetPositionZ() < 50.0f)
        return FindHostileByEntry(bot, NPC_SATHROVARR) != nullptr;

    return FindHostileByEntry(bot, NPC_KALECGOS_DRAGON) != nullptr;
}

bool SwKalecgosRealmTargetAction::Execute(Event /*event*/)
{
    Unit* target = bot->GetPositionZ() < 50.0f
        ? FindHostileByEntry(bot, NPC_SATHROVARR)
        : FindHostileByEntry(bot, NPC_KALECGOS_DRAGON);

    if (!target)
        return false;

    return Attack(target);
}
