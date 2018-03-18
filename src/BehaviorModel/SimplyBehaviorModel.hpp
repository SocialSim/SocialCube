#ifndef __SIMPLE_BEHAVIOR_MODEL__
#define __SIMPLE_BEHAVIOR_MODEL__

#include <vector>

class SimpleBehaviorModel {
    private:

        SimpleBehaviorModel();

        ~SimpleBehaviorModel();

    public:

    static std::vector<Event> evaluate(const HourlyActionRate& t_hourlyActionRate,
            const ObjectPreference &t_objectPreference,
            uint64_t t_currentTime,
            uint64_t t_unitTime
            );

};

#endif
