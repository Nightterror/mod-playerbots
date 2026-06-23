#ifndef _PLAYERBOT_RAIDRUBYSANCTUMTRIGGERS_H
#define _PLAYERBOT_RAIDRUBYSANCTUMTRIGGERS_H

#include "Trigger.h"

class RsBaltharusBladeTempestTrigger : public Trigger
{
public:
    RsBaltharusBladeTempestTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "ruby sanctum baltharus blade tempest") {}
    bool IsActive() override;
};

class RsSavianaConflagrationTrigger : public Trigger
{
public:
    RsSavianaConflagrationTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "ruby sanctum saviana conflagration") {}
    bool IsActive() override;
};

class RsHalionMarkTrigger : public Trigger
{
public:
    RsHalionMarkTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "ruby sanctum halion mark") {}
    bool IsActive() override;
};

class RsHalionMeteorFlameTrigger : public Trigger
{
public:
    RsHalionMeteorFlameTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "ruby sanctum halion meteor flame") {}
    bool IsActive() override;
};

class RsZarithrianFlamecallerTrigger : public Trigger
{
public:
    RsZarithrianFlamecallerTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "ruby sanctum zarithrian flamecaller") {}
    bool IsActive() override;
};

#endif
