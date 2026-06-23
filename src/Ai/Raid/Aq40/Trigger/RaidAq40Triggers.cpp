#include "RaidAq40Triggers.h"

#include "Playerbots.h"
#include "RaidAq40Helpers.h"

using namespace Aq40Helpers;

bool Aq40SkeramArcaneExplosionTrigger::IsActive()
{
    if (!InAq40(bot) || botAI->IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "the prophet skeram");
    if (!boss)
        boss = FindHostileByEntry(bot, NPC_PROPHET_SKERAM);

    return BossCastingSpell(boss, SPELL_ARCANE_EXPLOSION);
}

bool Aq40BugTrioSpreadTrigger::IsActive()
{
    if (!InAq40(bot))
        return false;

    if (!AnyBugTrioActive(botAI, bot))
        return false;

    return bot->HasAura(SPELL_TOXIC_VOLLEY) || bot->HasAura(SPELL_POISONBOLT_VOLLEY);
}

bool Aq40SarturaWhirlwindTrigger::IsActive()
{
    if (!InAq40(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "battleguard sartura");
    if (!boss)
        boss = FindHostileByEntry(bot, NPC_BATTLEGUARD_SARTURA);

    if (!boss)
        return false;

    if (boss->HasAura(SPELL_WHIRLWIND) && boss->GetVictim() == bot)
        return true;

    return bot->HasAura(SPELL_GUARD_WHIRLWIND);
}

bool Aq40HuhuranNoxiousPoisonTrigger::IsActive()
{
    return InAq40(bot) && bot->HasAura(SPELL_NOXIOUS_POISON);
}

bool Aq40ViscidusSpreadTrigger::IsActive()
{
    if (!InAq40(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "viscidus");
    if (!boss)
        boss = FindHostileByEntry(bot, NPC_VISCIDUS);

    return boss && (bot->HasAura(SPELL_POISONBOLT_VOLLEY) ||
                    BossCastingSpell(boss, SPELL_POISONBOLT_VOLLEY));
}

bool Aq40ViscidusSlimeTrigger::IsActive()
{
    if (!InAq40(bot))
        return false;

    Unit* slime = FindHostileByEntry(bot, NPC_TOXIC_SLIME, 25.0f);
    return slime && bot->GetDistance2d(slime) < 12.0f;
}

bool Aq40TwinsBlizzardTrigger::IsActive()
{
    if (!InAq40(bot) || botAI->IsTank(bot))
        return false;

    if (!TwinsFightActive(botAI, bot))
        return false;

    Unit* veklor = AI_VALUE2(Unit*, "find target", "emperor vek'lor");
    if (!veklor)
        veklor = FindHostileByEntry(bot, NPC_EMPEROR_VEKLOR);

    return BossCastingSpell(veklor, SPELL_BLIZZARD);
}

bool Aq40TwinsArcaneBurstTrigger::IsActive()
{
    if (!InAq40(bot) || botAI->IsTank(bot) || PlayerbotAI::IsRanged(bot))
        return false;

    if (!TwinsFightActive(botAI, bot))
        return false;

    Unit* veklor = FindHostileByEntry(bot, NPC_EMPEROR_VEKLOR, 80.0f);
    return veklor && bot->GetDistance2d(veklor) < 8.0f;
}

bool Aq40TwinsWrongTargetTrigger::IsActive()
{
    if (!InAq40(bot) || !TwinsFightActive(botAI, bot))
        return false;

    Unit* assigned = GetAssignedTwinEmperor(botAI, bot);
    if (!assigned)
        return false;

    Unit* current = AI_VALUE(Unit*, "current target");
    return !current || current->GetGUID() != assigned->GetGUID();
}

bool Aq40TwinsVeklorTankRangeTrigger::IsActive()
{
    if (!InAq40(bot) || !TwinsFightActive(botAI, bot))
        return false;

    if (!botAI->IsAssistTankOfIndex(bot, 0, true))
        return false;

    Unit* veklor = FindHostileByEntry(bot, NPC_EMPEROR_VEKLOR, 80.0f);
    if (!veklor)
        return false;

    float const dist = bot->GetDistance2d(veklor);
    return dist < 12.0f || dist > 42.0f;
}

bool Aq40OuroGroundRuptureTrigger::IsActive()
{
    if (!InAq40(bot) || botAI->IsTank(bot))
        return false;

    if (!AI_VALUE2(Unit*, "find target", "ouro") && !FindHostileByEntry(bot, NPC_OURO))
        return false;

    return bot->HasAura(SPELL_GROUND_RUPTURE);
}

bool Aq40CthunDarkGlareTrigger::IsActive()
{
    if (!InAq40(bot) || botAI->IsTank(bot) || !CthunFightActive(bot))
        return false;

    Unit* boss = FindCThunEyeOrBody(bot);
    return BossCastingSpell(boss, SPELL_DARK_GLARE);
}

bool Aq40CthunGreenBeamTrigger::IsActive()
{
    if (!InAq40(bot) || botAI->IsTank(bot) || !CthunFightActive(bot))
        return false;

    Unit* boss = FindCThunEyeOrBody(bot);
    return BossCastingSpell(boss, SPELL_GREEN_BEAM);
}

bool Aq40PriorityAddTrigger::IsActive()
{
    if (!InAq40(bot) || TwinsFightActive(botAI, bot))
        return false;

    Unit* add = FindPriorityAdd(botAI, bot);
    return add && AI_VALUE(Unit*, "current target") != add;
}
