#include "WeeklyEventCountBehaviorModel.hpp"

using namespace std;

WeeklyEventCountBehaviorModel::WeeklyEventCountBehaviorModel() {
    return;
}

WeeklyEventCountBehaviorModel::~WeeklyEventCountBehaviorModel() {
    return;
}

std::vector<unique_ptr<Event>> WeeklyEventCountBehaviorModel::evaluate(const string& t_id, 
                                                                  const string& t_cc, 
                                                                  const int& t_al,
                                                                  vector<float> temp_pref_weekly,
                                                                  DailyActivityLevel& t_dailyActivityLevel,
                                                                  WeeklyEventCount& t_weeklyEventCount,
                                                                  ObjectPreference& t_objectPreference,
                                                                  TypeDistribution& t_typeDistribution,
                                                                  time_t t_startTime,
                                                                  time_t t_endTime) {
    vector<unique_ptr<Event>> events;

    int startDay = WeeklyEventCountBehaviorModel::convertISOtoDay(t_startTime);
    int endDay = WeeklyEventCountBehaviorModel::convertISOtoDay(t_endTime);

    if (endDay - startDay > t_dailyActivityLevel.getActivityLevelSize()) {
        TimeSpanExceedException h_e;
        throw h_e;
    }

    if (endDay - startDay > t_weeklyEventCount.getEventCountSize()) {
        TimeSpanExceedWeeklyEventCountException h_ece;
        throw h_ece;
    }

    time_t currentTime = t_startTime;

    bool use_weekly_event_count = true;
    if (t_weeklyEventCount.getEventCountSum() == 0) {
        use_weekly_event_count = false;
    } else {
        cout << "Using LSTM analysis for user " << t_id << endl;
    }

    int dayCount = WeeklyEventCountBehaviorModel::currentDow(currentTime);
    for (int i = 0; i <= endDay - startDay; i++) {
        // Uses Temporal Preferences of Users
        if (t_al > temp_pref_weekly[dayCount - 1] && !use_weekly_event_count) {
            continue;
        }

        int push_event_cap = t_weeklyEventCount.getEventCount(i);

        double activityLevel_in_double = t_dailyActivityLevel.getActivityLevel(i);
        double fraction_part = activityLevel_in_double - int(activityLevel_in_double);
        double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        int activityLevel = int(activityLevel_in_double);

        if (randnum < fraction_part) {
            activityLevel++;
        }

        int push_event_count = 0;
        
        for (int j = 0; j < activityLevel; j++) {

            string actionType = WeeklyEventCountBehaviorModel::chooseAction(t_typeDistribution);

            if (use_weekly_event_count) {
                if (actionType == "PushEvent") {
                    push_event_count++;
                }

                if (push_event_count > push_event_cap) {
                    continue;
                }
            }

            string userID = t_id;
            string objectID = WeeklyEventCountBehaviorModel::chooseTarget(t_objectPreference);

            int hours = rand() % 24;
            int minutes = rand() % 60;
            int seconds = rand() % 60;

            time_t eventTime = currentTime + (hours * 60 + minutes) * 60 + seconds;
            unique_ptr<Event> event(new Event(userID, objectID, actionType, eventTime));
            // event->show();
            events.push_back(move(event));
        }

        if (push_event_count < push_event_cap && use_weekly_event_count) {
            for (int k = push_event_count; k < push_event_cap; k++) {
                string actionType = "PushEvent";

                string userID = t_id;
                string objectID = WeeklyEventCountBehaviorModel::chooseTarget(t_objectPreference);

                int hours = rand() % 24;
                int minutes = rand() % 60;
                int seconds = rand() % 60;

                time_t eventTime = currentTime + (hours * 60 + minutes) * 60 + seconds;
                unique_ptr<Event> event(new Event(userID, objectID, actionType, eventTime));

                events.push_back(move(event));         
            }
        }

        currentTime += 24 * 60 * 60;
        if (dayCount >= 7) {
            dayCount = 1;
        } else {
            dayCount++;
        }
    }

    return events;
}

string WeeklyEventCountBehaviorModel::chooseTarget(const ObjectPreference& t_objectPreference) {
    string target = t_objectPreference.randomChooseTarget();
    return target;
}

string WeeklyEventCountBehaviorModel::chooseAction(const TypeDistribution& t_typeDistribution) {
    string action = t_typeDistribution.randomChooseAction();
    return action;
}

int WeeklyEventCountBehaviorModel::convertISOtoDay(time_t t_currentTime) {
    return int(t_currentTime / (24 * 60 * 60));
}

int WeeklyEventCountBehaviorModel::currentDow(time_t now) {
    const tm currentTimeUtc = *gmtime(addressof(now));

    ostringstream dowStream;

    // static const char format[] = "%A, %d %B %Y %H:%M:%S UCT"; // standard UTC time presentation for reference
    static const char dowFormat[] = "%u";

    dowStream << put_time(addressof(currentTimeUtc), dowFormat);
    
    string stringDow = dowStream.str();

    return stoi(stringDow);
}
