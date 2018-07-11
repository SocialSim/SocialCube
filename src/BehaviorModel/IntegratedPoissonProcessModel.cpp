#include "IntegratedPoissonProcessModel.hpp"

using namespace std;

std::vector<unique_ptr<Event>> IntegratedPoissonProcessModel::evaluate(
        const string objectID,
        const vector<double>& mu,
        const vector<string>& typeList,
        int k,
        UserDistribution userDistribution,
        time_t t_startTime,
        time_t t_endTime
) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();

    vector<unique_ptr<Event>> events;

    if (userDistribution.getUserDistribution().size() == 0) {
        return events;
    }

    for (time_t t_currentTime = t_startTime; t_currentTime < t_endTime; ) {
        int eventNum = userDistribution.getTotalCount(t_currentTime);

        double startMinute = t_currentTime / 60;

        vector<unique_ptr<Event>> weekEvents;

        for (int i = 0; i < k; i++) {
            vector<unique_ptr<Event>> tmpEvents;
            double currentMinute = startMinute;
            vector<string> userIDs = userDistribution.getShuffledUserIDs(t_currentTime);
            string actionType = typeList[i];
            double typeMu = mu[i];
            for (int j = 0; j < eventNum; j++) {

                double u = (double) rand() / RAND_MAX;
                currentMinute += -log(u) / (typeMu + 1e-7);

                string userID = userIDs[j];
                time_t eventTime = currentMinute * 60;
                unique_ptr <Event> event(new Event(userID, objectID, actionType, eventTime));
                tmpEvents.push_back(move(event));
            }
            move(tmpEvents.begin(), tmpEvents.end(), back_inserter(weekEvents));
        }
        // Get the first eventNum events
        sort(weekEvents.begin(),
             weekEvents.end(),
             [](const unique_ptr<Event>& lhs, const unique_ptr<Event>& rhs) {
                 return lhs->getTimestamp() < rhs->getTimestamp();
             });

        if (weekEvents.size() > eventNum) {
            weekEvents.resize(eventNum);
        }

        if (weekEvents.size() > 0) {
            double endMinute = (weekEvents.back()->getTimestamp()) / 60;
            double ratio = (7*24*60) / (endMinute - startMinute);
            if (isfinite(ratio)) {
                for (auto it = weekEvents.begin(); it != weekEvents.end(); ) {
                    (*it)->warpTimestamp(startMinute * 60, ratio);
                    time_t time = (*it)->getTimestamp();
                    if ((*it)->getTimestamp() > t_endTime) {
                        it = weekEvents.erase(it);
                    } else {
                        it++;
                    }
                }
            }

        }

        if (weekEvents.size() > 0) {
            move(weekEvents.begin(), weekEvents.end(), back_inserter(events));
        }

        struct tm* tm_date = localtime(&t_currentTime);
        tm_date->tm_mday += 7;
        t_currentTime = mktime(tm_date);
    }

    return events;
}
