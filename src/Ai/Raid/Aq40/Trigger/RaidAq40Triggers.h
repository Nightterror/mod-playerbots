#ifndef _PLAYERBOT_RAIDAQ40TRIGGERS_H
#define _PLAYERBOT_RAIDAQ40TRIGGERS_H

#include "Trigger.h"

class Aq40SkeramArcaneExplosionTrigger : public Trigger
{
public:
    Aq40SkeramArcaneExplosionTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 skeram arcane explosion") {}
    bool IsActive() override;
};

class Aq40BugTrioSpreadTrigger : public Trigger
{
public:
    Aq40BugTrioSpreadTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 bug trio spread") {}
    bool IsActive() override;
};

class Aq40SarturaWhirlwindTrigger : public Trigger
{
public:
    Aq40SarturaWhirlwindTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 sartura whirlwind") {}
    bool IsActive() override;
};

class Aq40HuhuranNoxiousPoisonTrigger : public Trigger
{
public:
    Aq40HuhuranNoxiousPoisonTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 huhuran noxious poison") {}
    bool IsActive() override;
};

class Aq40ViscidusSpreadTrigger : public Trigger
{
public:
    Aq40ViscidusSpreadTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 viscidus spread") {}
    bool IsActive() override;
};

class Aq40ViscidusSlimeTrigger : public Trigger
{
public:
    Aq40ViscidusSlimeTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 viscidus slime") {}
    bool IsActive() override;
};

class Aq40TwinsBlizzardTrigger : public Trigger
{
public:
    Aq40TwinsBlizzardTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 twins blizzard") {}
    bool IsActive() override;
};

class Aq40TwinsArcaneBurstTrigger : public Trigger
{
public:
    Aq40TwinsArcaneBurstTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 twins arcane burst") {}
    bool IsActive() override;
};

class Aq40TwinsWrongTargetTrigger : public Trigger
{
public:
    Aq40TwinsWrongTargetTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 twins wrong target") {}
    bool IsActive() override;
};

class Aq40TwinsVeklorTankRangeTrigger : public Trigger
{
public:
    Aq40TwinsVeklorTankRangeTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 twins veklor tank range") {}
    bool IsActive() override;
};

class Aq40OuroGroundRuptureTrigger : public Trigger
{
public:
    Aq40OuroGroundRuptureTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 ouro ground rupture") {}
    bool IsActive() override;
};

class Aq40CthunDarkGlareTrigger : public Trigger
{
public:
    Aq40CthunDarkGlareTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 cthun dark glare") {}
    bool IsActive() override;
};

class Aq40CthunGreenBeamTrigger : public Trigger
{
public:
    Aq40CthunGreenBeamTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 cthun green beam") {}
    bool IsActive() override;
};

class Aq40PriorityAddTrigger : public Trigger
{
public:
    Aq40PriorityAddTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 priority add") {}
    bool IsActive() override;
};

#endif
