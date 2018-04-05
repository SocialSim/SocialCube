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
        TypeDistribution& t_typeDistribution,
        time_t t_currentTime,
        time_t t_unitTime
        ) {
    vector<unique_ptr<Event>> events;

    int currentHour = SimpleBehaviorModel::convertISOtoHour(t_currentTime);

    const std::unique_ptr<EventHourlyActionRate>& m_rate = t_hourlyActionRate.getRate();
    double dailyActivityLevel = m_rate->getActivityLevel();
    double prob = t_hourlyActionRate.getHourlyActionRate(currentHour % 24);

    while(dailyActivityLevel > 0.0) {
        if(dailyActivityLevel < 1.0) {
            prob *= dailyActivityLevel;
        }
        if(((double)rand() / RAND_MAX) < prob) {
            string userID = t_objectPreference.getUserID();
            string objectID = SimpleBehaviorModel::chooseTarget(t_objectPreference);
            string actionType = SimpleBehaviorModel::chooseAction(t_typeDistribution);
            unique_ptr<Event> event(new Event(userID, objectID, actionType, t_currentTime));
            events.push_back(move(event));
        }
        dailyActivityLevel -= 1.0;
    }

    return events;
}

string SimpleBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    string target = t_objectPreference.randomChooseTarget();
    return target;
}

string SimpleBehaviorModel::chooseAction(const TypeDistribution& t_typeDistribution) {
    string action = t_typeDistribution.randomChooseAction();
    return action;
}

int SimpleBehaviorModel::convertISOtoHour(time_t t_currentTime) {
    return gmtime(&t_currentTime)->tm_hour;
}
