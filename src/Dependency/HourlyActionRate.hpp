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

        std::unique_ptr<EventHourlyActionRate> m_rate;
    
        std::string m_userID;

    public:

        HourlyActionRate(const std::string &t_userID);

        ~HourlyActionRate();

        double getHourlyActionRate(int t_hour);

        void setHourlyActionRate(int t_hour, double t_rate, double t_activityLevel);

        double getActionActivityLevel();

        void show() const;

        std::unique_ptr<EventHourlyActionRate>& getRate(); 

        std::string getUserID() const;
};

#endif
