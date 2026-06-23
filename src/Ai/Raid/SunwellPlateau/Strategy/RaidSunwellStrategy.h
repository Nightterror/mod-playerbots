#ifndef _PLAYERBOT_RAIDSUNWELLSTRATEGY_H
#define _PLAYERBOT_RAIDSUNWELLSTRATEGY_H

#include "Strategy.h"

class RaidSunwellStrategy : public Strategy
{
public:
    RaidSunwellStrategy(PlayerbotAI* ai) : Strategy(ai) {}
    std::string const getName() override { return "sunwell"; }
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

#endif
