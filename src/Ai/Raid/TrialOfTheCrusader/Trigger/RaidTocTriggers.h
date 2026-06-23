#ifndef _PLAYERBOT_RAIDTOCTRIGGERS_H
#define _PLAYERBOT_RAIDTOCTRIGGERS_H

#include "Trigger.h"

class TocIcehowlChargeTrigger : public Trigger
{
public:
    TocIcehowlChargeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc icehowl charge") {}
    bool IsActive() override;
};

class TocLegionFlameTrigger : public Trigger
{
public:
    TocLegionFlameTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc legion flame") {}
    bool IsActive() override;
};

class TocJaraxxusAddTrigger : public Trigger
{
public:
    TocJaraxxusAddTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc jaraxxus add") {}
    bool IsActive() override;
};

class TocFactionChampionTrigger : public Trigger
{
public:
    TocFactionChampionTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc faction champion") {}
    bool IsActive() override;
};

class TocTwinVortexTrigger : public Trigger
{
public:
    TocTwinVortexTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc twin vortex") {}
    bool IsActive() override;
};

class TocTwinShieldTrigger : public Trigger
{
public:
    TocTwinShieldTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc twin shield") {}
    bool IsActive() override;
};

class TocAnubSpikeTrigger : public Trigger
{
public:
    TocAnubSpikeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc anub spike") {}
    bool IsActive() override;
};

class TocAnubColdTrigger : public Trigger
{
public:
    TocAnubColdTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc anub cold") {}
    bool IsActive() override;
};

class TocPriorityAddTrigger : public Trigger
{
public:
    TocPriorityAddTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc priority add") {}
    bool IsActive() override;
};

class TocFireBombTrigger : public Trigger
{
public:
    TocFireBombTrigger(PlayerbotAI* botAI) : Trigger(botAI, "toc fire bomb") {}
    bool IsActive() override;
};

#endif
