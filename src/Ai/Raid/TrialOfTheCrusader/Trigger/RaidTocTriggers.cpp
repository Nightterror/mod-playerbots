#include "RaidTocTriggers.h"

#include "Playerbots.h"
#include "RaidTocHelpers.h"

using namespace TocHelpers;

bool TocIcehowlChargeTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    Unit* icehowl = AI_VALUE2(Unit*, "find target", "icehowl");
    if (!icehowl)
        icehowl = FindHostileByEntry(bot, NPC_ICEHOWL);

    if (!icehowl)
        return false;

    if (icehowl->GetVictim() == bot || bot->HasAura(SPELL_MASSIVE_CRASH))
        return true;

    return BossCastingSpell(icehowl, SPELL_MASSIVE_CRASH);
}

bool TocLegionFlameTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    return bot->HasAura(SPELL_LEGION_FLAME) || bot->HasAura(SPELL_INCINERATE_FLESH);
}

bool TocJaraxxusAddTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    return FindHostileByEntry(bot, NPC_FELFLAME_INFERNAL) ||
           FindHostileByEntry(bot, NPC_MISTRESS_OF_PAIN);
}

bool TocFactionChampionTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    return FindTocChampionTarget(botAI, bot) != nullptr;
}

bool TocTwinVortexTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    Unit* fjola = FindHostileByEntry(bot, NPC_FJOLA);
    Unit* eydis = FindHostileByEntry(bot, NPC_EYDIS);

    if (BossCastingSpell(fjola, SPELL_LIGHT_VORTEX) && HasLightEssence(bot))
        return true;

    if (BossCastingSpell(eydis, SPELL_DARK_VORTEX) && HasDarkEssence(bot))
        return true;

    return false;
}

bool TocTwinShieldTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    Unit* fjola = FindHostileByEntry(bot, NPC_FJOLA);
    Unit* eydis = FindHostileByEntry(bot, NPC_EYDIS);

    if (fjola && fjola->HasAura(SPELL_LIGHT_SHIELD))
        return AI_VALUE(Unit*, "current target") == fjola;

    if (eydis && eydis->HasAura(SPELL_DARK_SHIELD))
        return AI_VALUE(Unit*, "current target") == eydis;

    return false;
}

bool TocAnubSpikeTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    if (bot->HasAura(SPELL_MARK_OF_SPIKE))
        return true;

    Unit* spike = FindHostileByEntry(bot, NPC_ANUB_SPIKE, 40.0f);
    return spike && bot->GetDistance2d(spike) < 15.0f;
}

bool TocAnubColdTrigger::IsActive()
{
    return InToc(bot) && bot->HasAura(SPELL_PENETRATING_COLD);
}

bool TocPriorityAddTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    Unit* add = FindPriorityAdd(botAI, bot);
    return add && AI_VALUE(Unit*, "current target") != add;
}

bool TocFireBombTrigger::IsActive()
{
    if (!InToc(bot))
        return false;

    Unit* bomb = FindHostileByEntry(bot, NPC_FIRE_BOMB, 25.0f);
    return bomb && bot->GetDistance2d(bomb) < 8.0f;
}
