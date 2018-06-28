#ifndef __WEEKLY_EVENT_COUNT_BEHAVIOR_MODEL__
#define __WEEKLY_EVENT_COUNT_BEHAVIOR_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "Dependency/DailyActivityLevel.hpp"
#include "Dependency/WeeklyEventCount.hpp"
#include "Dependency/ObjectPreference.hpp"
#include "Dependency/TypeDistribution.hpp"

class WeeklyEventCountBehaviorModel {
private:

    WeeklyEventCountBehaviorModel();

    ~WeeklyEventCountBehaviorModel();

    static std::string chooseTarget(const ObjectPreference& t_objectPreference);

    static std::string chooseAction(const TypeDistribution& t_typeDistribution);

    static int currentDow(time_t now);

    static int convertISOtoDay(time_t t_currentTime);

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string& t_id, 
                                                        const std::string& t_cc, 
                                                        const int& t_al,
                                                        std::vector<float> temp_pref_weekly,
                                                        DailyActivityLevel& t_dailyActivityLevel,
                                                        WeeklyEventCount& t_weeklyEventCount,
                                                        ObjectPreference& t_objectPreference,
                                                        TypeDistribution& t_typeDistribution,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
