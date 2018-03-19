#include "SimpleBehaviorModel.hpp"

using namespace std;

SimpleBehaviorModel::SimpleBehaviorModel() {
    return;
}

SimpleBehaviorModel::~SimpleBehaviorModel() {
    return;
}

std::vector<Event> SimpleBehaviorModel::evaluate(
        const HourlyActionRate& t_hourlyActionRate,
        const ObjectPreference& t_objectPreference,
        uint64_t t_currentTime,
        uint64_t t_unitTime
        ) {
    vector<Event> events;
    return events;
}
