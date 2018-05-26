#ifndef __INTEGRATED_POISSON_MODEL__
#define __INTEGRATED_POISSON_MODEL__

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include <time.h>
#include "common/Event.hpp"
#include "common/matOps.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/UserDistribution.hpp"

class IntegratedPoissonProcessModel {
private:

    IntegratedPoissonProcessModel() = default;

    ~IntegratedPoissonProcessModel() = default;


public:

    // static bool sortTwoEvent(const Event& e1, const Event& e2) const;

    static std::vector<std::unique_ptr<Event>> evaluate(
            const string objectID,
            const vector<double>& mu,
            const vector<string>& typeList,
            int k,
            time_t t_startTime,
            time_t t_endTime
    );

};

#endif
