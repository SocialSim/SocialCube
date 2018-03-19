#include "SimpleBehaviorModel.hpp"

using namespace std;

SimpleBehaviorModel::SimpleBehaviorModel() {
    return;
}

SimpleBehaviorModel::~SimpleBehaviorModel() {
    return;
}

std::vector<Event> SimpleBehaviorModel::evaluate(
        HourlyActionRate& t_hourlyActionRate,
        ObjectPreference& t_objectPreference,
        uint64_t t_currentTime,
        uint64_t t_unitTime
        ) {
    vector<Event> events;

    const std::unordered_map<std::string, std::unique_ptr<EventHourlyActionRate>>& m_rate = 
    t_hourlyActionRate.getRate();

    for(auto& hourlyActionRateIter : m_rate) {
        uint64_t activityLevel = hourlyActionRateIter.second->getActivityLevel();
        double probSum = hourlyActionRateIter.second->getProbSum();
        if(probSum == 0.0)
            continue;
        if(activityLevel == 0)
            continue;

        double prob = hourlyActionRateIter.second->getProb(t_currentTime % 24);

        for(uint64_t i = 0; i < activityLevel; ++i) {
            if(((double)rand() / RAND_MAX) < prob) {
                string userID = t_hourlyActionRate.getUserID();
                string objectID = SimpleBehaviorModel::chooseTarget(t_objectPreference);
                string actionType = hourlyActionRateIter.first;
                Event event(userID, objectID, actionType, t_currentTime);
                events.push_back(event);
            }
        }
    }

    return events;
}

std::string SimpleBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    double d = ((double)rand()) / RAND_MAX;
    string target = t_objectPreference.chooseTarget(d);
    return target;
}
