#include "DailySimpleBehaviorModel.hpp"

using namespace std;

DailySimpleBehaviorModel::DailySimpleBehaviorModel() {
    return;
}

DailySimpleBehaviorModel::~DailySimpleBehaviorModel() {
    return;
}

std::vector<unique_ptr<Event>> DailySimpleBehaviorModel::evaluate(const string t_id,
                                                                  DailyActivityLevel& t_dailyActivityLevel,
                                                                  ObjectPreference& t_objectPreference,
                                                                  TypeDistribution& t_typeDistribution,
                                                                  time_t t_startTime,
                                                                  time_t t_endTime) {
    vector<unique_ptr<Event>> events;

    int startDay = DailySimpleBehaviorModel::convertISOtoDay(t_startTime);
    int endDay = DailySimpleBehaviorModel::convertISOtoDay(t_endTime);

    if (endDay - startDay > t_dailyActivityLevel.getActivityLevelSize()) {
        TimeSpanExceedException h_e;
        throw h_e;
    }

    time_t currentTime = t_startTime;

    for (int i = 0; i <= endDay - startDay; i++) {
        double activityLevel_in_double = t_dailyActivityLevel.getActivityLevel(i);
        double fraction_part = activityLevel_in_double - int(activityLevel_in_double);
        double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        int activityLevel = int(activityLevel_in_double);

        if (randnum < fraction_part) {
            activityLevel++;
        }

        for (int j = 0; j < activityLevel; j++) {
            string userID = t_id;
            string objectID = DailySimpleBehaviorModel::chooseTarget(t_objectPreference);
            string actionType = DailySimpleBehaviorModel::chooseAction(t_typeDistribution);

            int hours = rand() % 24;
            int minutes = rand() % 60;
            int seconds = rand() % 60;

            time_t eventTime = currentTime + (hours * 60 + minutes) * 60 + seconds;
            unique_ptr<Event> event(new Event(userID, objectID, actionType, eventTime));
            // event->show();
            events.push_back(move(event));
        }
        currentTime += 24 * 60 * 60;
    }

    return events;
}

string DailySimpleBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    string target = t_objectPreference.randomChooseTarget();
    return target;
}

string DailySimpleBehaviorModel::chooseAction(const TypeDistribution& t_typeDistribution) {
    string action = t_typeDistribution.randomChooseAction();
    return action;
}

int DailySimpleBehaviorModel::convertISOtoDay(time_t t_currentTime) {
    return int(t_currentTime / (24 * 60 * 60));
}

