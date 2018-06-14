#ifndef __HOURLY_ACTION_RATE__
#define __HOURLY_ACTION_RATE__

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <cassert>

class DailyActivityLevel {
    private:

        std::vector<double> m_activityLevels;
        std::string m_userID;

    public:

        DailyActivityLevel(const std::string &t_userID);

        ~DailyActivityLevel();

        double getActivityLevel(int t_day);

        void addActivityLevel(double t_activityLevel);

        void show() const;

        std::string getUserID() const;
};

#endif
