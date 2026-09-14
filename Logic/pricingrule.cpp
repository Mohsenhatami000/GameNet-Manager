#include "pricingrule.h"

PricingRule::PricingRule(Platform platform, int playerCount, int price):
    platform(platform)
    , playerCount(playerCount)
    , price(price)
    {};

PricingRule::PricingRule(){};

PricingRule::PricingRule(const PricingRule &other): platform(other.platform)
    , playerCount(other.playerCount)
    , price(other.price){};

QTime PricingRule::calculateTimeFromMoney(int money){
    int totalSeconds = money / (double)price * 3600;
    int minutes = (totalSeconds / 60) % 60;
    int hours = totalSeconds / 3600;
    int seconds = totalSeconds % 60;
    return QTime(hours, minutes, seconds);
}

int PricingRule::calculateMoneyFromTime(QTime time){
    int tmp = (time.hour() + (time.minute() / 60)) * price;
    return tmp;
}

int PricingRule::getPlayerCount() const{
    return playerCount;
}

Platform PricingRule::getPlatform() const{
    return platform;
}