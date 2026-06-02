/*

 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it

 * and/or modify it under version 3 of the License, or (at your option), any later version.

 */



#include "ProgressionGearLimits.h"



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



// IP tier 0-18: gear band after final boss clear (see docs/playerbots-ip-autogear-implementation.md)

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

}  // namespace



ProgressionGearLimits GetAutogearLimits(Player* master, Player* /*bot*/)

{

    if (!sPlayerbotAIConfig.autoGearFollowProgression)

        return GetConfLimits();



#ifdef PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION

    if (!IndividualProgressionApi::IsEnabled() || !master)

        return GetConfLimits();



    uint8 tier = IndividualProgressionApi::GetPlayerProgressionTier(master);

    if (tier > kMaxProgressionTier)

        tier = kMaxProgressionTier;



    TierGearEntry const& entry = kTierGearTable[tier];



    ProgressionGearLimits limits;

    limits.quality = entry.quality;

    limits.maxIlvl = entry.maxIlvl;

    limits.ipTier = tier;

    limits.fromProgression = true;

    limits.gearScoreLimit = CalcGearScoreLimit(entry.maxIlvl, entry.quality);



    ApplyConfCeiling(limits);



    return limits;

#else

    return GetConfLimits();

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


