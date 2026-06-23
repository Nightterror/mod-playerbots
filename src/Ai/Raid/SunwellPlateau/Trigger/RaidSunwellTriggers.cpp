#include "RaidSunwellTriggers.h"

#include "Playerbots.h"
#include "RaidSunwellHelpers.h"

using namespace SunwellHelpers;

bool SwBrutallusBurnTrigger::IsActive()
{
    return InSunwell(bot) &&
           (bot->HasAura(SPELL_BURN) || bot->HasAura(SPELL_BURN_DAMAGE));
}

bool SwFelmystEncapsulateTrigger::IsActive()
{
    return InSunwell(bot) && bot->HasAura(SPELL_ENCAPSULATE);
}

bool SwFelmystVaporTrigger::IsActive()
{
    if (!InSunwell(bot))
        return false;

    Unit* vapor = FindHostileByEntry(bot, NPC_DEMONIC_VAPOR, 30.0f);
    return vapor && bot->GetDistance2d(vapor) < 12.0f;
}

bool SwTwinsSpreadTrigger::IsActive()
{
    if (!InSunwell(bot))
        return false;

    return bot->HasAura(SPELL_CONFLAGRATION) || bot->HasAura(SPELL_SHADOW_NOVA);
}

bool SwKjFireBloomTrigger::IsActive()
{
    return InSunwell(bot) && bot->HasAura(SPELL_FIRE_BLOOM);
}

bool SwKalecgosCurseTrigger::IsActive()
{
    return InSunwell(bot) && bot->HasAura(SPELL_CURSE_BOUNDLESS_AGONY);
}

bool SwSingularityTrigger::IsActive()
{
    if (!InSunwell(bot) || botAI->IsTank(bot))
        return false;

    Unit* singularity = FindHostileByEntry(bot, NPC_SINGULARITY, 40.0f);
    return singularity && bot->GetDistance2d(singularity) < 15.0f;
}

bool SwShieldOrbTrigger::IsActive()
{
    if (!InSunwell(bot) || botAI->IsTank(bot))
        return false;

    Unit* orb = FindHostileByEntry(bot, NPC_SHIELD_ORB, 50.0f);
    return orb && bot->GetDistance2d(orb) < 8.0f;
}

bool SwPriorityAddTrigger::IsActive()
{
    if (!InSunwell(bot))
        return false;

    Unit* add = FindPriorityAdd(botAI, bot);
    if (!add)
        return false;

    Unit* current = AI_VALUE(Unit*, "current target");
    if (current == add)
        return false;

    if (current && (current->GetEntry() == NPC_KILJAEDEN ||
                    current->GetEntry() == NPC_ENTROPIUS ||
                    current->GetEntry() == NPC_BRUTALLUS ||
                    current->GetEntry() == NPC_FELMYST))
        return true;

    return !current || current->GetEntry() != add->GetEntry();
}

bool SwTwinsWrongTargetTrigger::IsActive()
{
    if (!InSunwell(bot))
        return false;

    Unit* current = AI_VALUE(Unit*, "current target");
    if (!current)
        return false;

    if (current->GetEntry() != NPC_LADY_SACROLASH &&
        current->GetEntry() != NPC_GRAND_WARLOCK_ALYTHESS)
        return false;

    return HasWrongTwinAuraForTarget(bot, current);
}

bool SwKalecgosRealmTrigger::IsActive()
{
    if (!InSunwell(bot))
        return false;

    bool const spectral = bot->GetPositionZ() < 50.0f;
    Unit* desired = spectral
        ? FindHostileByEntry(bot, NPC_SATHROVARR)
        : FindHostileByEntry(bot, NPC_KALECGOS_DRAGON);

    if (!desired)
        return false;

    Unit* current = AI_VALUE(Unit*, "current target");
    return !current || current->GetEntry() != desired->GetEntry();
}
