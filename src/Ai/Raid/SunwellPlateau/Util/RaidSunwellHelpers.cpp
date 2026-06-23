#include "RaidSunwellHelpers.h"

namespace SunwellHelpers
{
bool InSunwell(Player* bot)
{
    return bot && bot->GetMapId() == SUNWELL_MAP_ID;
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

bool HasWrongTwinAuraForTarget(Player* bot, Unit* target)
{
    if (!bot || !target)
        return false;

    if (bot->HasAura(SPELL_DARK_FLAME))
        return true;

    bool const flameTouched = bot->HasAura(SPELL_FLAME_TOUCHED);
    bool const darkTouched = bot->HasAura(SPELL_DARK_TOUCHED);

    if (target->GetEntry() == NPC_LADY_SACROLASH && darkTouched)
        return true;

    if (target->GetEntry() == NPC_GRAND_WARLOCK_ALYTHESS && flameTouched)
        return true;

    return false;
}

Unit* FindPriorityAdd(PlayerbotAI* botAI, Player* bot)
{
    static uint32 const priority[] =
    {
        NPC_SINISTER_REFLECTION,
        NPC_DARK_FIEND,
        NPC_HAND_OF_DECEIVER,
        NPC_SHADOW_IMAGE,
        NPC_VOID_SENTINEL,
        NPC_SHADOWSWORD_FURY_MAGE,
        NPC_SHADOWSWORD_BERSERKER,
        NPC_VOID_SPAWN,
        NPC_UNYIELDING_DEAD,
        NPC_DEMONIC_VAPOR,
    };

    for (uint32 entry : priority)
    {
        if (Unit* add = FindHostileByEntry(bot, entry, 120.0f))
            return add;
    }

    return nullptr;
}
}
