#ifndef __NEW_USER_MODEL__
#define __NEW_USER_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/DailyActivityLevel.hpp"
#include "Dependency/ObjectPreference.hpp"
#include "Dependency/TypeDistribution.hpp"

class NewUserModel {
private:

    NewUserModel();

    ~NewUserModel();

    static std::string generateNodeId();

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
