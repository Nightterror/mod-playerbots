/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license.
 */

#include "RandomPlayerbotPvPSwap.h"

#include "Log.h"
#include "Player.h"
#include "PlayerbotAI.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotFactory.h"
#include "Playerbots.h"
#include "ProgressionGearLimits.h"
#include "RandomPlayerbotMgr.h"
#include "SharedDefines.h"

namespace
{
    char const* PRE_PVP_SPEC_KEY = "prePvpSpecNo";
    char const* IN_PVP_MODE_KEY = "inPvpMode";
    char const* PVP_GEAR_SWAPPED_KEY = "pvpGearSwapped";

    bool IsPremadePvpSpec(uint8 cls, int premadeIndex)
    {
        if (premadeIndex < 0 || premadeIndex >= MAX_SPECNO)
            return false;

        std::string const& name = sPlayerbotAIConfig.premadeSpecName[cls][premadeIndex];
        return !name.empty() && name.find("pvp") != std::string::npos;
    }

    bool HasPremadeSpec(uint8 cls, int premadeIndex)
    {
        if (premadeIndex < 0 || premadeIndex >= MAX_SPECNO)
            return false;

        return !sPlayerbotAIConfig.premadeSpecName[cls][premadeIndex].empty();
    }

    void ApplyPremadeSpec(Player* bot, int premadeIndex)
    {
        PlayerbotFactory::InitTalentsBySpecNo(bot, premadeIndex, true);

        PlayerbotFactory factory(bot, bot->GetLevel());
        factory.InitGlyphs(false);

        if (PlayerbotAI* botAI = GET_PLAYERBOT_AI(bot))
            botAI->ResetStrategies(false);
    }

    void ApplyGear(Player* bot, ProgressionGearLimits const& limits, bool pvpWeights)
    {
        PlayerbotFactory factory(bot, bot->GetLevel(), limits, limits.quality, limits.gearScoreLimit);
        factory.SetForcePvpGear(pvpWeights);
        factory.InitEquipment(false, sPlayerbotAIConfig.twoRoundsGearInit);
        factory.InitAmmo();
        if (bot->GetLevel() >= sPlayerbotAIConfig.minEnchantingBotLevel)
            factory.ApplyEnchantAndGemsNew();
        bot->DurabilityRepairAll(false, 1.0f, false);
    }

    void ApplyRandomBotPvEGear(Player* bot)
    {
        PlayerbotFactory factory = PlayerbotFactory::CreateForRandomBot(bot, bot->GetLevel());
        factory.InitEquipment(false, sPlayerbotAIConfig.twoRoundsGearInit);
        factory.InitAmmo();
        if (bot->GetLevel() >= sPlayerbotAIConfig.minEnchantingBotLevel)
            factory.ApplyEnchantAndGemsNew();
        bot->DurabilityRepairAll(false, 1.0f, false);
    }
}

int RandomPlayerbotPvPSwap::MapPvePremadeToPvpPremade(uint8 cls, int premadeIndex)
{
    if (premadeIndex < 0 || premadeIndex >= MAX_SPECNO)
        return -1;

    if (IsPremadePvpSpec(cls, premadeIndex))
        return premadeIndex;

    switch (cls)
    {
        case CLASS_DRUID:
            switch (premadeIndex)
            {
                case 0: return 4;
                case 1: return 5;
                case 2: return 6;
                case 3: return 5;
                default: break;
            }
            break;
        case CLASS_DEATH_KNIGHT:
            switch (premadeIndex)
            {
                case 0: return 4;
                case 1: return 5;
                case 2: return 6;
                case 3: return 4;
                default: break;
            }
            break;
        case CLASS_MAGE:
            switch (premadeIndex)
            {
                case 0: return 4;
                case 1: return 5;
                case 2: return 6;
                case 3: return 6;
                default: break;
            }
            break;
        default:
            if (premadeIndex >= 0 && premadeIndex <= 2 && HasPremadeSpec(cls, premadeIndex + 3))
                return premadeIndex + 3;
            break;
    }

    return -1;
}

bool RandomPlayerbotPvPSwap::IsInPvPMode(Player* bot)
{
    if (!bot)
        return false;

    return sRandomPlayerbotMgr.GetValue(bot->GetGUID().GetCounter(), IN_PVP_MODE_KEY) != 0;
}

bool RandomPlayerbotPvPSwap::EnterPvPMode(Player* bot)
{
    if (!bot)
        return false;

    if (!sRandomPlayerbotMgr.IsRandomBot(bot))
        return false;

    if (IsInPvPMode(bot))
        return false;

    if (!sPlayerbotAIConfig.randomBotPvpSpecOnQueueJoin &&
        !sPlayerbotAIConfig.randomBotPvpGearOnQueueJoin)
        return false;

    bool changed = false;
    uint32 botId = bot->GetGUID().GetCounter();

    if (sPlayerbotAIConfig.randomBotPvpSpecOnQueueJoin)
    {
        uint32 storedSpecNo = sRandomPlayerbotMgr.GetValue(botId, "specNo");
        if (storedSpecNo)
        {
            int premadeIndex = static_cast<int>(storedSpecNo) - 1;
            int pvpPremadeIndex = MapPvePremadeToPvpPremade(bot->getClass(), premadeIndex);
            if (pvpPremadeIndex >= 0 && pvpPremadeIndex != premadeIndex)
            {
                sRandomPlayerbotMgr.SetValue(botId, PRE_PVP_SPEC_KEY, storedSpecNo);
                ApplyPremadeSpec(bot, pvpPremadeIndex);

                LOG_DEBUG("playerbots", "Bot {} <{}> swapped to PvP spec {} ({}) for queue",
                          bot->GetGUID().ToString(), bot->GetName(), pvpPremadeIndex,
                          sPlayerbotAIConfig.premadeSpecName[bot->getClass()][pvpPremadeIndex]);

                changed = true;
            }
        }
    }

    if (sPlayerbotAIConfig.randomBotPvpGearOnQueueJoin)
    {
        ProgressionGearLimits limits = GetRandomBotPvPGearLimits();
        ApplyGear(bot, limits, true);
        sRandomPlayerbotMgr.SetValue(botId, PVP_GEAR_SWAPPED_KEY, 1);

        LOG_DEBUG("playerbots", "Bot {} <{}> re-geared for PvP (IP tier {}, ilvl cap {})",
                  bot->GetGUID().ToString(), bot->GetName(), static_cast<uint32>(limits.ipTier),
                  limits.maxIlvl);

        changed = true;
    }

    if (!changed)
        return false;

    sRandomPlayerbotMgr.SetValue(botId, IN_PVP_MODE_KEY, 1);
    return true;
}

bool RandomPlayerbotPvPSwap::LeavePvPMode(Player* bot)
{
    if (!bot)
        return false;

    if (!sRandomPlayerbotMgr.IsRandomBot(bot))
        return false;

    if (!IsInPvPMode(bot))
        return false;

    uint32 botId = bot->GetGUID().GetCounter();
    uint32 prePvpSpecNo = sRandomPlayerbotMgr.GetValue(botId, PRE_PVP_SPEC_KEY);
    bool gearSwapped = sRandomPlayerbotMgr.GetValue(botId, PVP_GEAR_SWAPPED_KEY) != 0;

    sRandomPlayerbotMgr.SetValue(botId, IN_PVP_MODE_KEY, 0);
    sRandomPlayerbotMgr.SetValue(botId, PRE_PVP_SPEC_KEY, 0);
    sRandomPlayerbotMgr.SetValue(botId, PVP_GEAR_SWAPPED_KEY, 0);

    bool restored = false;

    if (prePvpSpecNo && sPlayerbotAIConfig.randomBotPvpSpecOnQueueJoin)
    {
        int premadeIndex = static_cast<int>(prePvpSpecNo) - 1;
        if (premadeIndex >= 0 && premadeIndex < MAX_SPECNO)
        {
            ApplyPremadeSpec(bot, premadeIndex);

            LOG_DEBUG("playerbots", "Bot {} <{}> restored PvE spec {} ({}) after PvP",
                      bot->GetGUID().ToString(), bot->GetName(), premadeIndex,
                      sPlayerbotAIConfig.premadeSpecName[bot->getClass()][premadeIndex]);

            restored = true;
        }
    }

    if (gearSwapped && sPlayerbotAIConfig.randomBotPvpGearOnQueueJoin)
    {
        ProgressionGearLimits limits = GetRandomBotProgressionGearLimits();
        ApplyRandomBotPvEGear(bot);

        LOG_DEBUG("playerbots", "Bot {} <{}> restored PvE gear (IP tier {}, ilvl cap {})",
                  bot->GetGUID().ToString(), bot->GetName(), static_cast<uint32>(limits.ipTier),
                  limits.maxIlvl);

        restored = true;
    }

    return restored;
}
