#ifndef PRICINGRULE_H
#define PRICINGRULE_H

#include "Platform.h"
#include <QTime>

class PricingRule
{
    Platform platform;
    int playerCount;
    int price;

public:
    PricingRule();
    PricingRule(Platform platform, int playerCount, int price);
    PricingRule(const PricingRule &other);
    QTime calculateTimeFromMoney(int money);
    int calculateMoneyFromTime(QTime time);
    int getPlayerCount() const;
    Platform getPlatform() const;
};

#endif // PRICINGRULE_H
