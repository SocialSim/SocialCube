#ifndef __WEEKLYEVENTCOUNT__
#define __WEEKLYEVENTCOUNT__

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <numeric>

class WeeklyEventCount {
    private:

        std::vector<double> m_eventCountList;
        std::string m_userID;

    public:

        WeeklyEventCount(const std::string &t_userID);

        ~WeeklyEventCount();

        double getEventCount(int t_day);

        int getEventCountSize();

        int getEventCountSum();

        void addEventCount(double t_activityLevel);

        void show() const;

        std::string getUserID() const;
};

#endif
