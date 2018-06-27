#ifndef __INTEGRATED_POINT_MODEL__
#define __INTEGRATED_POINT_MODEL__

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include <time.h>
#include "common/Event.hpp"
#include "common/matOps.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/UserDistribution.hpp"

class IntegratedPointProcessModel {
private:

    IntegratedPointProcessModel() = default;

    ~IntegratedPointProcessModel() = default;

public:

    static std::vector<std::unique_ptr<Event>> evaluate (
            const std::string objectID,
            const std::vector<double>& mu,
            const std::vector<std::vector<double>>& alpha,
            const std::vector<double>& beta,
            const std::vector<std::string>& typeList,
            int k,
            UserDistribution& userDistribution,
            time_t t_startTime,
            time_t t_endTime
    );

};

#endif
