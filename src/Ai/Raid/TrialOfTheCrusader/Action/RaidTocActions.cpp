#include "RaidTocActions.h"

#include "Playerbots.h"
#include "RaidTocHelpers.h"

using namespace TocHelpers;

bool TocMoveFromGroupAction::Execute(Event /*event*/)
{
    return MoveFromGroup(_distance);
}

bool TocMoveFromIcehowlAction::Execute(Event /*event*/)
{
    Unit* icehowl = FindHostileByEntry(bot, NPC_ICEHOWL, 80.0f);
    if (!icehowl)
        return false;

    bot->AttackStop();
    bot->InterruptNonMeleeSpells(false);
    return MoveAway(icehowl, 30.0f);
}

bool TocMoveFromFireBombAction::Execute(Event /*event*/)
{
    Unit* bomb = FindHostileByEntry(bot, NPC_FIRE_BOMB, 25.0f);
    if (!bomb)
        return false;

    return MoveAway(bomb, 12.0f);
}

bool TocAttackPriorityAddAction::Execute(Event /*event*/)
{
    Unit* add = FindPriorityAdd(botAI, bot);
    if (!add)
        return false;

    return Attack(add);
}

bool TocAttackFactionChampionAction::Execute(Event /*event*/)
{
    Unit* champion = FindTocChampionTarget(botAI, bot);
    if (!champion)
        return false;

    return Attack(champion);
}

bool TocTwinSwitchTargetAction::Execute(Event /*event*/)
{
    Unit* current = AI_VALUE(Unit*, "current target");
    if (!current)
        return false;

    uint32 const otherEntry = current->GetEntry() == NPC_FJOLA ? NPC_EYDIS : NPC_FJOLA;
    Unit* other = FindHostileByEntry(bot, otherEntry);
    if (!other)
        return false;

    return Attack(other);
}

bool TocTwinStopDpsAction::Execute(Event /*event*/)
{
    bot->AttackStop();
    return MoveFromGroup(5.0f);
}
