#ifndef __SIMPLE_BEHAVIOR_MODEL__
#define __SIMPLE_BEHAVIOR_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "Dependency/HourlyActionRate.hpp"
#include "Dependency/ObjectPreference.hpp"
#include "Dependency/TypeDistribution.hpp"

class SimpleBehaviorModel {
    private:

        SimpleBehaviorModel();

        ~SimpleBehaviorModel();

        static std::string chooseTarget(const ObjectPreference& t_objectPreference);

        static std::string chooseAction(const TypeDistribution& t_typeDistribution);

    public:

    static std::vector<std::unique_ptr<Event>> evaluate(HourlyActionRate& t_hourlyActionRate,
            ObjectPreference &t_objectPreference,
            TypeDistribution &t_typeDistribution,
            uint64_t t_currentTime,
            uint64_t t_unitTime
            );

};

#endif
