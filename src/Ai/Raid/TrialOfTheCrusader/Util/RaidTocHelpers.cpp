#include "RaidTocHelpers.h"

#include "AiObjectContext.h"

namespace TocHelpers
{
bool InToc(Player* bot)
{
    return bot && bot->GetMapId() == TOC_MAP_ID;
}

Unit* FindHostileByEntry(Player* bot, uint32 entry, float range)
{
    if (!bot)
        return nullptr;

    return bot->FindNearestCreature(entry, range, true);
}

bool BossCastingSpell(Unit* boss, uint32 spellId)
{
    return boss && boss->IsAlive() && boss->HasUnitState(UNIT_STATE_CASTING) &&
           boss->FindCurrentSpellBySpellId(spellId);
}

bool IsTocHealerEntry(uint32 entry)
{
    for (uint32 healerEntry : HEALER_ENTRIES)
        if (entry == healerEntry)
            return true;
    return false;
}

bool IsTocCasterEntry(uint32 entry)
{
    for (uint32 casterEntry : CASTER_ENTRIES)
        if (entry == casterEntry)
            return true;
    return false;
}

bool HasLightEssence(Player* bot)
{
    return bot && bot->HasAura(SPELL_LIGHT_ESSENCE);
}

bool HasDarkEssence(Player* bot)
{
    return bot && bot->HasAura(SPELL_DARK_ESSENCE);
}

Unit* FindTocChampionTarget(PlayerbotAI* botAI, Player* bot)
{
    GuidVector npcs = botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest hostile npcs")->Get();
    Unit* healer = nullptr;
    Unit* caster = nullptr;
    Unit* fallback = nullptr;

    for (ObjectGuid const& guid : npcs)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !unit->IsInCombat())
            continue;

        uint32 entry = unit->GetEntry();
        if (IsTocHealerEntry(entry))
            return unit;

        if (IsTocCasterEntry(entry) && !caster)
            caster = unit;

        if (!fallback)
            fallback = unit;
    }

    if (caster)
        return caster;

    return fallback;
}

Unit* FindPriorityAdd(PlayerbotAI* botAI, Player* bot)
{
    static uint32 const priority[] =
    {
        NPC_SNOBOLD,
        NPC_FELFLAME_INFERNAL,
        NPC_MISTRESS_OF_PAIN,
        NPC_NERUBIAN_BURROWER,
        NPC_SWARM_SCARAB,
        NPC_FROST_SPHERE,
    };

    for (uint32 entry : priority)
    {
        if (Unit* add = FindHostileByEntry(bot, entry, 120.0f))
            return add;
    }

    if (Unit* champion = FindTocChampionTarget(botAI, bot))
        return champion;

    return nullptr;
}
}
