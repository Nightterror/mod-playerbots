#ifndef _PLAYERBOT_RAIDAQ40STRATEGY_H
#define _PLAYERBOT_RAIDAQ40STRATEGY_H

#include "Strategy.h"

class RaidAq40Strategy : public Strategy
{
public:
    RaidAq40Strategy(PlayerbotAI* ai) : Strategy(ai) {}
    std::string const getName() override { return "aq40"; }
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

#endif
