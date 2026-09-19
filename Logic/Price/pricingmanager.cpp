#include "pricingmanager.h"

PricingManager::PricingManager() {}

void PricingManager::addPricingRule(PricingRule rule){
    PriceTable[rule.getPlatform()][rule.getPlayerCount()] = rule;
}

void PricingManager::removeRule(Platform platform, int playerCount){
    PriceTable[platform].erase(playerCount);
}

PricingRule PricingManager::getRule(Platform platform, int playerCount){
    return PriceTable[platform][playerCount];
}

