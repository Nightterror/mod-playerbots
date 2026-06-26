/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#include "ProgressionGearLimits.h"

#include "ItemTemplate.h"
#include "PlayerbotAIConfig.h"
#include "SharedDefines.h"

#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
#include "IndividualProgressionApi.h"
#include "Player.h"
#endif

namespace
{
struct TierGearEntry
{
    uint32 quality;
    uint32 maxIlvl;
};

// IP tier 0-18: gear band after final boss clear
TierGearEntry const kTierGearTable[] = {
    { ITEM_QUALITY_RARE, 63 },    // 0 pre-raid
    { ITEM_QUALITY_EPIC, 78 },    // 1 Ragnaros
    { ITEM_QUALITY_EPIC, 78 },    // 2 Onyxia
    { ITEM_QUALITY_EPIC, 83 },    // 3 Nefarian
    { ITEM_QUALITY_EPIC, 83 },    // 4 AQ war
    { ITEM_QUALITY_EPIC, 83 },    // 5 AQ open
    { ITEM_QUALITY_EPIC, 88 },    // 6 C'Thun
    { ITEM_QUALITY_EPIC, 92 },    // 7 Kel'Thuzad 40
    { ITEM_QUALITY_EPIC, 92 },    // 8 pre-TBC
    { ITEM_QUALITY_EPIC, 125 },   // 9 Malchezaar
    { ITEM_QUALITY_EPIC, 141 },   // 10 Kael'thas
    { ITEM_QUALITY_EPIC, 156 },   // 11 Illidan
    { ITEM_QUALITY_EPIC, 156 },   // 12 Zul'jin
    { ITEM_QUALITY_EPIC, 164 },   // 13 Kil'jaeden
    { ITEM_QUALITY_EPIC, 224 },   // 14 Kel'Thuzad 80
    { ITEM_QUALITY_EPIC, 245 },   // 15 Yogg-Saron
    { ITEM_QUALITY_EPIC, 258 },   // 16 Anub'arak
    { ITEM_QUALITY_EPIC, 290 },   // 17 Lich King
    { ITEM_QUALITY_EPIC, 290 },   // 18 Halion
};

constexpr uint8 kMaxProgressionTier = 18;

// Rated arena season -> max PvP item ilvl (Gladiator vendor bands)
uint32 const kArenaSeasonMaxIlvl[] = {
    0,    // unused
    123,  // S1 (TBC)
    128,  // S2
    136,  // S3 Merciless
    146,  // S4 Vengeful
    213,  // S5 Deadly
    232,  // S6 Furious
    251,  // S7 Relentless
    264,  // S8 Wrathful
};

constexpr uint32 TBC_CONTENT_ITEM_FLOOR = 23528;
constexpr uint32 WOTLK_CONTENT_ITEM_FLOOR = 33470;
constexpr uint32 WOTLK_GEM_ITEM_FLOOR = 39900;
constexpr uint32 TBC_AMMO_ITEM_FLOOR = 23728;
constexpr uint32 WOTLK_AMMO_ITEM_FLOOR = 35570;

constexpr uint32 TBC_ENCHANT_SPELL_FLOOR = 27899;
constexpr uint32 WOTLK_ENCHANT_SPELL_FLOOR = 44483;

constexpr uint32 TBC_SOCKET_GEM_ID_MIN = 23000;
constexpr uint32 WOTLK_SOCKET_GEM_IN_TBC_BAND = 36917;

// IP tier gates for TBC socket-gem bands (item level is flat 70 for most).
constexpr uint8 IP_TIER_TBC_UNLOCK = 8;    // PROGRESSION_PRE_TBC (Kara/Gruul/Mag)
constexpr uint8 IP_TIER_TBC_KARA = 9;      // post-Malchezaar (enchant default)
constexpr uint8 IP_TIER_TBC_HYJAL = 10;    // PROGRESSION_TBC_TIER_2 (Hyjal epic gems)

uint8 GetRequiredIpTierForAttunementQuest(uint32 questId)
{
    switch (questId)
    {
        case 10888:  // Trial of the Naaru: Magtheridon
        case 10901:  // The Cudgel of Kar'desh
            return IP_TIER_TBC_KARA;
        case 10445:  // The Vials of Eternity
        case 10985:  // Entry Into the Black Temple
            return IP_TIER_TBC_HYJAL;
        default:
            return IP_TIER_TBC_UNLOCK;  // Kara / CoT attunement chain
    }
}
constexpr uint8 IP_TIER_TBC_BT = 11;       // Black Temple (enchants only)
constexpr uint8 IP_TIER_TBC_SUNWELL = 12;  // Sunwell Plateau (enchants only)

enum TbcSocketGemBand : uint8
{
    TBC_GEM_BAND_EARLY = 0,  // Outland, heroic BoP, rare pre-Hyjal cuts
    TBC_GEM_BAND_HYJAL = 1,  // All epic cuts from Hyjal onward (incl. Crimson Spinel)
};

ContentPhase GetSocketGemContentPhase(uint32 itemId)
{
    if (itemId >= WOTLK_GEM_ITEM_FLOOR)
        return CONTENT_PHASE_WOTLK;
    if (itemId >= TBC_SOCKET_GEM_ID_MIN)
        return CONTENT_PHASE_TBC;
    return CONTENT_PHASE_CLASSIC;
}

TbcSocketGemBand GetTbcSocketGemBand(uint32 itemId)
{
    if ((itemId >= 32193 && itemId <= 32199) || (itemId >= 32200 && itemId <= 32231) ||
        itemId == 32249 || itemId == 37503 || (itemId >= 31116 && itemId <= 31118) ||
        (itemId >= 35487 && itemId <= 35489) || (itemId >= 35758 && itemId <= 35761) ||
        (itemId >= 33131 && itemId <= 33144))
        return TBC_GEM_BAND_HYJAL;

    return TBC_GEM_BAND_EARLY;
}

uint8 GetRequiredIpTierForTbcGemBand(TbcSocketGemBand band)
{
    if (band == TBC_GEM_BAND_HYJAL)
        return IP_TIER_TBC_HYJAL;

    return IP_TIER_TBC_UNLOCK;
}

ContentPhase GetMaxAllowedSocketGemPhase(ProgressionGearLimits const& limits)
{
    if (limits.fromProgression && limits.ipTier >= IP_TIER_TBC_UNLOCK)
        return CONTENT_PHASE_TBC;

    return limits.maxContentPhase;
}

bool IsTbcSocketGem(uint32 itemId)
{
    return itemId >= TBC_SOCKET_GEM_ID_MIN && itemId < WOTLK_GEM_ITEM_FLOOR;
}

struct TbcEnchantTierEntry
{
    uint32 spellId;
    uint8 minTier;
};

// Raid/special TBC enchants; default TBC band allows tier 9 (Kara).
TbcEnchantTierEntry const kTbcEnchantTierOverrides[] = {
    { 27981, IP_TIER_TBC_HYJAL },   // Sunfire
    { 27982, IP_TIER_TBC_HYJAL },   // Soulfrost
    { 27972, IP_TIER_TBC_HYJAL },   // Potency
    { 27975, IP_TIER_TBC_HYJAL },   // Major Spellpower
    { 27917, IP_TIER_TBC_HYJAL },   // Bracer Spellpower
    { 28003, IP_TIER_TBC_BT },      // Spellsurge
    { 28004, IP_TIER_TBC_BT },      // Battlemaster
    { 33997, IP_TIER_TBC_BT },      // Gloves Major Spellpower
    { 47051, IP_TIER_TBC_BT },      // Cloak Steelweave
    { 42974, IP_TIER_TBC_SUNWELL }, // Executioner
    { 46578, IP_TIER_TBC_SUNWELL }, // Deathfrost
};

bool IsTbcEnchantSpell(uint32 spellId)
{
    return spellId >= TBC_ENCHANT_SPELL_FLOOR && spellId < WOTLK_ENCHANT_SPELL_FLOOR;
}

uint8 GetRequiredIpTierForTbcEnchantSpell(uint32 spellId)
{
    for (TbcEnchantTierEntry const& entry : kTbcEnchantTierOverrides)
    {
        if (entry.spellId == spellId)
            return entry.minTier;
    }

    return IP_TIER_TBC_KARA;
}

float GetItemScoreMultiplier(uint32 quality)
{
    switch (quality)
    {
        case ITEM_QUALITY_POOR:
            return 1.0f;
        case ITEM_QUALITY_NORMAL:
            return 1.1f;
        case ITEM_QUALITY_UNCOMMON:
            return 1.21f;
        case ITEM_QUALITY_RARE:
            return 1.331f;
        case ITEM_QUALITY_EPIC:
            return 1.4641f;
        case ITEM_QUALITY_LEGENDARY:
            return 1.61051f;
        default:
            return 1.0f;
    }
}

uint32 CalcGearScoreLimit(uint32 ilvl, uint32 quality)
{
    if (ilvl == 0)
        return 0;

    return static_cast<uint32>(ilvl * GetItemScoreMultiplier(quality));
}

ContentPhase GetItemContentPhase(uint32 itemId)
{
    if (itemId >= WOTLK_CONTENT_ITEM_FLOOR)
        return CONTENT_PHASE_WOTLK;
    if (itemId >= TBC_CONTENT_ITEM_FLOOR)
        return CONTENT_PHASE_TBC;
    return CONTENT_PHASE_CLASSIC;
}

void FillProgressionLimitsFromTier(uint8 tier, ProgressionGearLimits& limits)
{
    if (tier > kMaxProgressionTier)
        tier = kMaxProgressionTier;

    TierGearEntry const& entry = kTierGearTable[tier];

    limits.quality = entry.quality;
    limits.maxIlvl = entry.maxIlvl;
    limits.ipTier = tier;
    limits.maxContentPhase = GetContentPhaseForTier(tier);
    limits.fromProgression = true;
    limits.gearScoreLimit = CalcGearScoreLimit(entry.maxIlvl, entry.quality);
}

ProgressionGearLimits GetConfLimits()
{
    ProgressionGearLimits limits;
    limits.quality = sPlayerbotAIConfig.autoGearQualityLimit;
    limits.maxIlvl = sPlayerbotAIConfig.autoGearScoreLimit;
    limits.fromProgression = false;
    limits.gearScoreLimit = CalcGearScoreLimit(sPlayerbotAIConfig.autoGearScoreLimit, limits.quality);

    return limits;
}

void ApplyConfCeiling(ProgressionGearLimits& limits)
{
    if (sPlayerbotAIConfig.autoGearScoreLimit == 0)
        return;

    uint32 confCap = CalcGearScoreLimit(sPlayerbotAIConfig.autoGearScoreLimit, limits.quality);

    if (limits.gearScoreLimit == 0 || confCap < limits.gearScoreLimit)
        limits.gearScoreLimit = confCap;
}

void ApplyRandomBotConfCeiling(ProgressionGearLimits& limits)
{
    if (sPlayerbotAIConfig.randomGearScoreLimit <= 0)
        return;

    uint32 quality = sPlayerbotAIConfig.randomGearQualityLimit >= 0
                         ? static_cast<uint32>(sPlayerbotAIConfig.randomGearQualityLimit)
                         : limits.quality;
    uint32 confCap = CalcGearScoreLimit(static_cast<uint32>(sPlayerbotAIConfig.randomGearScoreLimit), quality);

    if (limits.gearScoreLimit == 0 || confCap < limits.gearScoreLimit)
        limits.gearScoreLimit = confCap;
}

#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
ProgressionGearLimits GetProgressionLimitsFromMaster(Player* master)
{
    if (!IndividualProgressionApi::IsEnabled() || !master)
        return ProgressionGearLimits();

    ProgressionGearLimits limits;
    FillProgressionLimitsFromTier(IndividualProgressionApi::GetPlayerProgressionTier(master), limits);
    return limits;
}
#endif

}  // namespace

ContentPhase GetContentPhaseForTier(uint8 ipTier)
{
    if (ipTier <= 8)
        return CONTENT_PHASE_CLASSIC;
    if (ipTier <= 13)
        return CONTENT_PHASE_TBC;
    return CONTENT_PHASE_WOTLK;
}

char const* GetContentPhaseLabel(ContentPhase phase)
{
    switch (phase)
    {
        case CONTENT_PHASE_CLASSIC:
            return "classic";
        case CONTENT_PHASE_TBC:
            return "TBC";
        case CONTENT_PHASE_WOTLK:
            return "WotLK";
        default:
            return "unknown";
    }
}

bool IsItemAllowedForProgression(ItemTemplate const* proto, ProgressionGearLimits const& limits)
{
    if (!proto)
        return false;

    if (!limits.fromProgression)
        return true;

    if (GetItemContentPhase(proto->ItemId) > limits.maxContentPhase)
        return false;

    return true;
}

bool IsGemAllowedForProgression(ItemTemplate const* gem, ProgressionGearLimits const& limits, uint32 botLevel)
{
    if (!gem)
        return false;

    if (!limits.fromProgression)
        return true;

    if (GetSocketGemContentPhase(gem->ItemId) > GetMaxAllowedSocketGemPhase(limits))
        return false;

    if (limits.maxContentPhase <= CONTENT_PHASE_TBC && gem->ItemId >= WOTLK_GEM_ITEM_FLOOR)
        return false;

    if (limits.maxContentPhase <= CONTENT_PHASE_TBC && gem->ItemId >= WOTLK_SOCKET_GEM_IN_TBC_BAND)
        return false;

    if (IsTbcSocketGem(gem->ItemId))
    {
        TbcSocketGemBand const band = GetTbcSocketGemBand(gem->ItemId);
        if (limits.ipTier < GetRequiredIpTierForTbcGemBand(band))
            return false;
    }

    if (gem->ItemLevel > limits.maxIlvl)
        return false;

    if (gem->RequiredLevel > botLevel)
        return false;

    return true;
}

bool IsEnchantSpellAllowedForProgression(uint32 enchantSpellId, ProgressionGearLimits const& limits)
{
    if (!limits.fromProgression)
        return true;

    if (limits.maxContentPhase == CONTENT_PHASE_CLASSIC && enchantSpellId >= TBC_ENCHANT_SPELL_FLOOR)
        return false;

    if (limits.maxContentPhase <= CONTENT_PHASE_TBC && enchantSpellId >= WOTLK_ENCHANT_SPELL_FLOOR)
        return false;

    if (IsTbcEnchantSpell(enchantSpellId) &&
        limits.ipTier < GetRequiredIpTierForTbcEnchantSpell(enchantSpellId))
        return false;

    return true;
}

ProgressionGearLimits GetProgressionLimitsForTier(uint8 tier)
{
    ProgressionGearLimits limits;
    FillProgressionLimitsFromTier(tier, limits);
    return limits;
}

ProgressionGearLimits GetRandomBotConfLimits()
{
    ProgressionGearLimits limits;
    limits.quality = sPlayerbotAIConfig.randomGearQualityLimit >= 0
                         ? static_cast<uint32>(sPlayerbotAIConfig.randomGearQualityLimit)
                         : ITEM_QUALITY_EPIC;
    if (sPlayerbotAIConfig.randomGearScoreLimit > 0)
    {
        limits.maxIlvl = static_cast<uint32>(sPlayerbotAIConfig.randomGearScoreLimit);
        limits.gearScoreLimit = CalcGearScoreLimit(limits.maxIlvl, limits.quality);
    }
    return limits;
}

ProgressionGearLimits GetRandomBotProgressionGearLimits()
{
    if (!sPlayerbotAIConfig.autoGearFollowProgression)
        return GetRandomBotConfLimits();

#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
    if (!IndividualProgressionApi::IsEnabled())
        return GetRandomBotConfLimits();

    uint8 serverTier = IndividualProgressionApi::GetServerProgressionTier();
    if (!serverTier)
        return GetRandomBotConfLimits();

    ProgressionGearLimits limits = GetProgressionLimitsForTier(serverTier);
    ApplyRandomBotConfCeiling(limits);
    return limits;
#else
    return GetRandomBotConfLimits();
#endif
}

ProgressionGearLimits GetRandomBotPvPGearLimits()
{
#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
    if (IndividualProgressionApi::IsEnabled())
    {
        uint8 serverTier = IndividualProgressionApi::GetServerProgressionTier();
        uint8 arenaSeason = IndividualProgressionApi::GetServerArenaSeason();

        if (arenaSeason >= 1 && arenaSeason <= 8)
        {
            ProgressionGearLimits limits;
            if (serverTier)
                FillProgressionLimitsFromTier(serverTier, limits);
            else
            {
                limits.quality = ITEM_QUALITY_EPIC;
                limits.maxContentPhase = CONTENT_PHASE_WOTLK;
            }

            limits.maxIlvl = kArenaSeasonMaxIlvl[arenaSeason];
            limits.quality = ITEM_QUALITY_EPIC;
            limits.gearScoreLimit = CalcGearScoreLimit(limits.maxIlvl, limits.quality);
            limits.fromProgression = true;
            return limits;
        }
    }
#endif

    return GetRandomBotProgressionGearLimits();
}

ProgressionGearLimits GetAutogearLimits(Player* master, Player* /*bot*/)
{
    if (!sPlayerbotAIConfig.autoGearFollowProgression)
        return GetConfLimits();

#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
    ProgressionGearLimits limits = GetProgressionLimitsFromMaster(master);
    if (!limits.fromProgression)
        return GetConfLimits();

    ApplyConfCeiling(limits);
    return limits;
#else
    return GetConfLimits();
#endif
}

ProgressionGearLimits GetMaintenanceLimits(Player* master, Player* /*bot*/)
{
    ProgressionGearLimits limits;

    if (!sPlayerbotAIConfig.maintenanceFollowProgression)
        return limits;

#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
    limits = GetProgressionLimitsFromMaster(master);
    if (!limits.fromProgression && !sPlayerbotAIConfig.maintenanceFollowProgressionFallback)
        return limits;

    return limits;
#else
    return limits;
#endif
}

void TrySyncProgressionToGroup(Player* master)
{
    if (!master || !sPlayerbotAIConfig.autoGearSyncProgressionToGroup)
        return;

#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
    if (!IndividualProgressionApi::IsEnabled())
        return;

    IndividualProgressionApi::SyncGroupBotsToLeader(master);
#endif
}

bool IsAttunementQuestAllowedForPlayer(uint32 questId, Player* player)
{
#ifndef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION
    (void)questId;
    (void)player;
    return true;
#else
    if (!player || !IndividualProgressionApi::IsEnabled())
        return true;

    uint8 ipTier = IndividualProgressionApi::GetPlayerProgressionTier(player);
    return ipTier >= GetRequiredIpTierForAttunementQuest(questId);
#endif
}
