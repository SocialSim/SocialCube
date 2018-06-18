#ifndef __DAILYACTIVITYLEVEL__
#define __DAILYACTIVITYLEVEL__

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

        int getActivityLevelSize();

        void addActivityLevel(double t_activityLevel);

        void show() const;

        std::string getUserID() const;
};

#endif
