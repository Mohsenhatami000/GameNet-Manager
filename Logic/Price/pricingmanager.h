#ifndef PRICINGMANAGER_H
#define PRICINGMANAGER_H

#include <unordered_map>
#include "pricingrule.h"

class PricingManager
{
    std::unordered_map<Platform, std::unordered_map<int, PricingRule>> PriceTable;

public:
    PricingManager();
    void addPricingRule(PricingRule rule);
    void removeRule(Platform platform, int playerCount);
    PricingRule getRule(Platform platform, int playerCount);

};

#endif // PRICINGMANAGER_H
