#include "SeedHourlySimpleBehaviorModel.hpp"

using namespace std;

SeedHourlySimpleBehaviorModel::SeedHourlySimpleBehaviorModel() {
    return;
}

SeedHourlySimpleBehaviorModel::~SeedHourlySimpleBehaviorModel() {
    return;
}

std::vector<unique_ptr<Event>> SeedHourlySimpleBehaviorModel::evaluate(const string t_id,
                                                                  time_t t_startTime,
                                                                  time_t t_endTime) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();


    vector<unique_ptr<Event>> events;

    time_t currentTime = t_startTime;

    DailyActivityLevel hourlyActivityLevel = m_statProxy.getDailyActivityLevel(t_id);

    int startHour = SeedHourlySimpleBehaviorModel::convertISOtoHour(t_startTime);
    int endHour = SeedHourlySimpleBehaviorModel::convertISOtoHour(t_endTime);

    if (endHour - startHour > hourlyActivityLevel.getActivityLevelSize()) {
        TimeSpanExceedException h_e;
        throw h_e;
    }

    for (int i = 0; i <= endHour - startHour; i++) {
        string repoID = SeedHourlySimpleBehaviorModel::chooseTarget(m_statProxy.getRepoPreference(t_id));

        string userID = SeedHourlySimpleBehaviorModel::chooseTarget(m_statProxy.getUserPreference(repoID));

        string actionType = SeedHourlySimpleBehaviorModel::chooseAction(m_statProxy.getUserTypeDistribution(userID));

        int minutes = rand() % 60;
        int seconds = rand() % 60;

        time_t eventTime = currentTime + minutes * 60 + seconds;

        unique_ptr<Event> event(new Event(userID, repoID, actionType, eventTime));
        event->setPlatform("github");
        event->setInfoID(t_id);

        // event->show();
        events.push_back(move(event));
    }

    return events;
}

string SeedHourlySimpleBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    string target = t_objectPreference.randomChooseTarget();
    return target;
}

string SeedHourlySimpleBehaviorModel::chooseAction(const TypeDistribution& t_typeDistribution) {
    string action = t_typeDistribution.randomChooseAction();
    return action;
}

int SeedHourlySimpleBehaviorModel::convertISOtoHour(time_t t_currentTime) {
    return int(t_currentTime / (60 * 60));
}

