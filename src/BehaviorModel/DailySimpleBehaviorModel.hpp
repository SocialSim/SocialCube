#ifndef __DAILY_SIMPLE_BEHAVIOR_MODEL__
#define __DAILY_SIMPLE_BEHAVIOR_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "Dependency/DailyActivityLevel.hpp"
#include "Dependency/ObjectPreference.hpp"
#include "Dependency/TypeDistribution.hpp"

class DailySimpleBehaviorModel {
private:

    DailySimpleBehaviorModel();

    ~DailySimpleBehaviorModel();

    static std::string chooseTarget(const ObjectPreference& t_objectPreference);

    static std::string chooseAction(const TypeDistribution& t_typeDistribution);

    static int convertISOtoDay(time_t t_currentTime);

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,

                                                        DailyActivityLevel& t_dailyActivityLevel,
                                                        ObjectPreference& t_objectPreference,
                                                        TypeDistribution& t_typeDistribution,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
