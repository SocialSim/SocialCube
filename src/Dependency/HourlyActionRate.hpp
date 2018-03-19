#ifndef __HOURLY_ACTION_RATE__
#define __HOURLY_ACTION_RATE__

#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <cassert>
#include "EventHourlyActionRate.hpp"

class HourlyActionRate {
    private:

        // eventType -> action rate in 24 hours
        std::unordered_map<std::string, std::unique_ptr<EventHourlyActionRate>> m_rate;
    
        std::string m_userID;

    public:

        HourlyActionRate(const std::string &t_userID);

        ~HourlyActionRate();

        double getHourlyActionRate(const std::string &t_eventType, int t_hour);

        void setHourlyActionRate(const std::string &t_eventType, int t_hour, double t_rate, uint64_t t_activityLevel);

        uint64_t getActionActivityLevel(const std::string &t_eventType);

        void show() const;

        std::unordered_map<std::string, std::unique_ptr<EventHourlyActionRate>>& getRate(); 

        std::string getUserID() const;
};

#endif
