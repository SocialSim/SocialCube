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

        double m_activityLevel;

        double m_probSum;

    public:

        EventHourlyActionRate(double t_activityLevel);

        ~EventHourlyActionRate();

        void setProb(int t_hour, double t_rate);

        double getProb(int t_hour);

        double getProbSum();

        uint64_t getActivityLevel();

        void show();
};

#endif
