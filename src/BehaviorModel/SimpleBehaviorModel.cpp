#include "SimpleBehaviorModel.hpp"

using namespace std;

SimpleBehaviorModel::SimpleBehaviorModel() {
    return;
}

SimpleBehaviorModel::~SimpleBehaviorModel() {
    return;
}

std::vector<unique_ptr<Event>> SimpleBehaviorModel::evaluate(
        HourlyActionRate& t_hourlyActionRate,
        ObjectPreference& t_objectPreference,
        uint64_t t_currentTime,
        uint64_t t_unitTime
        ) {
    vector<unique_ptr<Event>> events;

    const std::unordered_map<std::string, std::unique_ptr<EventHourlyActionRate>>& m_rate = t_hourlyActionRate.getRate();

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
                string userID = t_objectPreference.getUserID();
                string objectID = SimpleBehaviorModel::chooseTarget(t_objectPreference);
                string actionType = hourlyActionRateIter.first;
                unique_ptr<Event> event(new Event(userID, objectID, actionType, t_currentTime));
                events.push_back(move(event));
            }
        }
    }

    return events;
}

std::string SimpleBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    string target = t_objectPreference.randomChooseTarget();
    return target;
}
