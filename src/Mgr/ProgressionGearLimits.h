/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_PROGRESSIONGEARLIMITS_H
#define _PLAYERBOT_PROGRESSIONGEARLIMITS_H

#include "Define.h"

class Player;

struct ProgressionGearLimits
{
    uint32 quality = 0;
    uint32 gearScoreLimit = 0;
    uint32 maxIlvl = 0;
    uint8 ipTier = 0;
    bool fromProgression = false;
};

ProgressionGearLimits GetAutogearLimits(Player* master, Player* bot);
void TrySyncProgressionToGroup(Player* master);

#endif
