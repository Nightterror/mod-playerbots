/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license.
 */

#ifndef _RANDOM_PLAYERBOT_PVP_SWAP_H_
#define _RANDOM_PLAYERBOT_PVP_SWAP_H_

#include "Define.h"

class Player;

class RandomPlayerbotPvPSwap
{
public:
    static bool EnterPvPMode(Player* bot);
    static bool LeavePvPMode(Player* bot);
    static bool IsInPvPMode(Player* bot);

    static int MapPvePremadeToPvpPremade(uint8 cls, int premadeIndex);
};

#endif
