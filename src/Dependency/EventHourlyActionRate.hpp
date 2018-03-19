#ifndef __EVENT_HOURLY_ACTION_RATE__
#define __EVENT_HOURLY_ACTION_RATE__

#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>

class EventHourlyActionRate {

    private:

        // hour -> action rate of that hour
        std::vector<double> m_prob;

        uint64_t m_activityLevel;

    public:

        EventHourlyActionRate(uint64_t t_activityLevel);

        ~EventHourlyActionRate();

        void setProb(int t_hour, double t_rate);

        double getProb(int t_hour);

        uint64_t getActivityLevel();

        void show();
};

#endif
