#include "RaidAq40Actions.h"

#include "Playerbots.h"
#include "RaidAq40Helpers.h"

using namespace Aq40Helpers;

bool Aq40MoveFromBossAction::Execute(Event /*event*/)
{
    Unit* boss = GetBoss();
    if (!boss)
        return false;

    float distToTravel = _distance - bot->GetDistance2d(boss);
    if (distToTravel <= 0)
        return false;

    bot->AttackStop();
    bot->InterruptNonMeleeSpells(false);
    return MoveAway(boss, distToTravel);
}

Unit* Aq40SkeramMoveAwayAction::GetBoss()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "the prophet skeram");
    return boss ? boss : FindHostileByEntry(bot, NPC_PROPHET_SKERAM);
}

Unit* Aq40CthunMoveFromBeamAction::GetBoss()
{
    return FindCThunEyeOrBody(bot);
}

Unit* Aq40CthunMoveFromGreenBeamAction::GetBoss()
{
    return FindCThunEyeOrBody(bot);
}

bool Aq40MoveFromGroupSpreadAction::Execute(Event /*event*/)
{
    return MoveFromGroup(_distance);
}

bool Aq40SarturaMoveAwayAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "battleguard sartura");
    if (!boss)
        boss = FindHostileByEntry(bot, NPC_BATTLEGUARD_SARTURA);

    if (!boss)
        return false;

    return MoveAway(boss, 25.0f);
}

bool Aq40TwinsMoveFromVeklorAction::Execute(Event /*event*/)
{
    Unit* veklor = FindHostileByEntry(bot, NPC_EMPEROR_VEKLOR, 80.0f);
    if (!veklor)
        return false;

    return MoveAway(veklor, 15.0f);
}

bool Aq40TwinsSwitchTargetAction::Execute(Event /*event*/)
{
    Unit* boss = GetAssignedTwinEmperor(botAI, bot);
    if (!boss)
        return false;

    return Attack(boss);
}

bool Aq40TwinsVeklorTankRangeAction::Execute(Event /*event*/)
{
    Unit* veklor = FindHostileByEntry(bot, NPC_EMPEROR_VEKLOR, 80.0f);
    if (!veklor)
        return false;

    if (AI_VALUE(Unit*, "current target") != veklor)
        Attack(veklor);

    float const dist = bot->GetDistance2d(veklor);
    if (dist < 12.0f)
        return MoveAway(veklor, 18.0f);

    if (dist > 42.0f)
        return ChaseTo(veklor, 28.0f);

    return false;
}

bool Aq40MoveFromSlimeAction::Execute(Event /*event*/)
{
    Unit* slime = FindHostileByEntry(bot, NPC_TOXIC_SLIME, 25.0f);
    if (!slime)
        return false;

    return MoveAway(slime, 15.0f);
}

bool Aq40AttackPriorityAddAction::Execute(Event /*event*/)
{
    Unit* add = FindPriorityAdd(botAI, bot);
    if (!add)
        return false;

    return Attack(add);
}
