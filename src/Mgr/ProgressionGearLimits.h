/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_PROGRESSIONGEARLIMITS_H
#define _PLAYERBOT_PROGRESSIONGEARLIMITS_H

#include "Define.h"

class Player;

struct ItemTemplate;

enum ContentPhase : uint8
{
    CONTENT_PHASE_CLASSIC = 0,
    CONTENT_PHASE_TBC     = 1,
    CONTENT_PHASE_WOTLK   = 2
};

struct ProgressionGearLimits
{
    uint32 quality = 0;
    uint32 gearScoreLimit = 0;
    uint32 maxIlvl = 0;
    uint8 ipTier = 0;
    ContentPhase maxContentPhase = CONTENT_PHASE_WOTLK;
    bool fromProgression = false;
};

ContentPhase GetContentPhaseForTier(uint8 ipTier);
char const* GetContentPhaseLabel(ContentPhase phase);

bool IsItemAllowedForProgression(ItemTemplate const* proto, ProgressionGearLimits const& limits);
bool IsGemAllowedForProgression(ItemTemplate const* gem, ProgressionGearLimits const& limits, uint32 botLevel);
bool IsEnchantSpellAllowedForProgression(uint32 enchantSpellId, ProgressionGearLimits const& limits);

ProgressionGearLimits GetAutogearLimits(Player* master, Player* bot);
ProgressionGearLimits GetMaintenanceLimits(Player* master, Player* bot);
void TrySyncProgressionToGroup(Player* master);

bool IsAttunementQuestAllowedForPlayer(uint32 questId, Player* player);

#endif
