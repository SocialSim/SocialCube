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

    const std::unique_ptr<EventHourlyActionRate>& m_rate = t_hourlyActionRate.getRate();
    double dailyActivityLevel = m_rate->getActivityLevel();
    double prob = t_hourlyActionRate.getHourlyActionRate(t_currentTime % 24);

    while(dailyActivityLevel > 0.0) {
        if(dailyActivityLevel < 1.0) {
            prob *= dailyActivityLevel;
        }
        if(((double)rand() / RAND_MAX) < prob) {
            string userID = t_objectPreference.getUserID();
            string objectID = SimpleBehaviorModel::chooseTarget(t_objectPreference);
            string actionType = SimpleBehaviorModel::chooseAction();
            unique_ptr<Event> event(new Event(userID, objectID, actionType, t_currentTime));
            events.push_back(move(event));
        }
        dailyActivityLevel -= 0.1;
    }

    return events;
}

string SimpleBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    string target = t_objectPreference.randomChooseTarget();
    return target;
}

string SimpleBehaviorModel::chooseAction() {
    return "ha?";
}
