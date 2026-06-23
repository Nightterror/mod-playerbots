#ifndef _PLAYERBOT_RAIDSUNWELLTRIGGERS_H
#define _PLAYERBOT_RAIDSUNWELLTRIGGERS_H

#include "Trigger.h"

class SwBrutallusBurnTrigger : public Trigger
{
public:
    SwBrutallusBurnTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell brutallus burn") {}
    bool IsActive() override;
};

class SwFelmystEncapsulateTrigger : public Trigger
{
public:
    SwFelmystEncapsulateTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell felmyst encapsulate") {}
    bool IsActive() override;
};

class SwFelmystVaporTrigger : public Trigger
{
public:
    SwFelmystVaporTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell felmyst vapor") {}
    bool IsActive() override;
};

class SwTwinsSpreadTrigger : public Trigger
{
public:
    SwTwinsSpreadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell twins spread") {}
    bool IsActive() override;
};

class SwKjFireBloomTrigger : public Trigger
{
public:
    SwKjFireBloomTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell kj fire bloom") {}
    bool IsActive() override;
};

class SwKalecgosCurseTrigger : public Trigger
{
public:
    SwKalecgosCurseTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell kalecgos curse") {}
    bool IsActive() override;
};

class SwSingularityTrigger : public Trigger
{
public:
    SwSingularityTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell singularity") {}
    bool IsActive() override;
};

class SwShieldOrbTrigger : public Trigger
{
public:
    SwShieldOrbTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell shield orb") {}
    bool IsActive() override;
};

class SwPriorityAddTrigger : public Trigger
{
public:
    SwPriorityAddTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell priority add") {}
    bool IsActive() override;
};

class SwTwinsWrongTargetTrigger : public Trigger
{
public:
    SwTwinsWrongTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell twins wrong target") {}
    bool IsActive() override;
};

class SwKalecgosRealmTrigger : public Trigger
{
public:
    SwKalecgosRealmTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sunwell kalecgos realm") {}
    bool IsActive() override;
};

#endif
