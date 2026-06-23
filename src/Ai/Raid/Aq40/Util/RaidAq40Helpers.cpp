#include "RaidAq40Helpers.h"

#include "AiObjectContext.h"
#include "Group.h"

#include <algorithm>
#include <vector>

namespace Aq40Helpers
{
bool InAq40(Player* bot)
{
    return bot && bot->GetMapId() == AQ40_MAP_ID;
}

Unit* FindHostileByEntry(Player* bot, uint32 entry, float range)
{
    if (!bot)
        return nullptr;

    return bot->FindNearestCreature(entry, range, true);
}

Unit* FindCThunEyeOrBody(Player* bot)
{
    if (Unit* eye = FindHostileByEntry(bot, NPC_EYE_OF_CTHUN))
        return eye;

    return FindHostileByEntry(bot, NPC_CTHUN);
}

bool BossCastingSpell(Unit* boss, uint32 spellId)
{
    return boss && boss->IsAlive() && boss->HasUnitState(UNIT_STATE_CASTING) &&
           boss->FindCurrentSpellBySpellId(spellId);
}

bool AnyBugTrioActive(PlayerbotAI* botAI, Player* bot)
{
    AiObjectContext* context = botAI->GetAiObjectContext();
    return context->GetValue<Unit*>("find target", "lord kri")->Get() ||
           context->GetValue<Unit*>("find target", "vem")->Get() ||
           context->GetValue<Unit*>("find target", "princess yauj")->Get() ||
           FindHostileByEntry(bot, NPC_LORD_KRI) ||
           FindHostileByEntry(bot, NPC_VEM) ||
           FindHostileByEntry(bot, NPC_PRINCESS_YAUJ);
}

bool TwinsFightActive(PlayerbotAI* /*botAI*/, Player* bot)
{
    if (!bot)
        return false;

    Unit* veknilash = FindHostileByEntry(bot, NPC_EMPEROR_VEKNILASH);
    if (veknilash && veknilash->IsInCombat())
        return true;

    Unit* veklor = FindHostileByEntry(bot, NPC_EMPEROR_VEKLOR);
    return veklor && veklor->IsInCombat();
}

bool CthunFightActive(Player* bot)
{
    if (!bot)
        return false;

    Unit* eye = FindHostileByEntry(bot, NPC_EYE_OF_CTHUN);
    if (eye && eye->IsInCombat())
        return true;

    Unit* body = FindHostileByEntry(bot, NPC_CTHUN);
    return body && body->IsInCombat();
}

static bool IsCthunTentacleEntry(uint32 entry)
{
    return entry == NPC_FLESH_TENTACLE || entry == NPC_GIANT_EYE_TENTACLE ||
           entry == NPC_GIANT_CLAW_TENTACLE || entry == NPC_EYE_TENTACLE ||
           entry == NPC_CLAW_TENTACLE;
}

uint32 GetAssignedTwinEmperorEntry(PlayerbotAI* botAI, Player* bot)
{
    if (botAI->IsMainTank(bot))
        return NPC_EMPEROR_VEKNILASH;

    if (botAI->IsAssistTankOfIndex(bot, 0, true))
        return NPC_EMPEROR_VEKLOR;

    Group* group = bot->GetGroup();
    if (!group)
        return NPC_EMPEROR_VEKNILASH;

    std::vector<ObjectGuid> members;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->GetSource();
        if (!member || !member->IsAlive() || botAI->IsTank(member))
            continue;

        members.push_back(member->GetGUID());
    }

    std::sort(members.begin(), members.end());

    auto it = std::find(members.begin(), members.end(), bot->GetGUID());
    if (it == members.end())
        return NPC_EMPEROR_VEKNILASH;

    size_t const idx = static_cast<size_t>(std::distance(members.begin(), it));
    return (idx % 2 == 0) ? NPC_EMPEROR_VEKNILASH : NPC_EMPEROR_VEKLOR;
}

Unit* GetAssignedTwinEmperor(PlayerbotAI* botAI, Player* bot)
{
    return FindHostileByEntry(bot, GetAssignedTwinEmperorEntry(botAI, bot));
}

Unit* FindPriorityAdd(PlayerbotAI* botAI, Player* bot)
{
    if (TwinsFightActive(botAI, bot))
        return nullptr;

    static uint32 const priority[] =
    {
        NPC_YAUJ_BROOD,
        NPC_VEKNISS_HATCHLING,
        NPC_GLOB_OF_VISCIDUS,
        NPC_OURO_SCARAB,
        NPC_FLESH_TENTACLE,
        NPC_GIANT_EYE_TENTACLE,
        NPC_GIANT_CLAW_TENTACLE,
        NPC_EYE_TENTACLE,
        NPC_CLAW_TENTACLE,
        NPC_SARTURA_GUARD,
    };

    for (uint32 entry : priority)
    {
        if (IsCthunTentacleEntry(entry) && !CthunFightActive(bot))
            continue;

        if (Unit* add = FindHostileByEntry(bot, entry, 120.0f))
            return add;
    }

    return nullptr;
}
}
