#ifndef _PLAYERBOT_RAIDRUBYSANCTUMSTRATEGY_H
#define _PLAYERBOT_RAIDRUBYSANCTUMSTRATEGY_H

#include "Strategy.h"

class RaidRubySanctumStrategy : public Strategy
{
public:
    RaidRubySanctumStrategy(PlayerbotAI* ai) : Strategy(ai) {}
    std::string const getName() override { return "wotlk-rs"; }
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

#endif
