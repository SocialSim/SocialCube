#include "IntegratedPoissonProcessModel.hpp"

using namespace std;

std::vector<unique_ptr<Event>> IntegratedPoissonProcessModel::evaluate(
        const string objectID,
        const vector<double>& mu,
        const vector<string>& typeList,
        int k,
        time_t t_startTime,
        time_t t_endTime
) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();

    UserDistribution userDistribution = m_statProxy.getRepoUserDistribution(objectID);

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
            double ratio = (7*24*60) / (currentMinute - startMinute);

            for (auto it = tmpEvents.begin(); it != tmpEvents.end(); ) {
                (*it)->warpTimestamp(startMinute * 60, ratio);
                time_t time = (*it)->getTimestamp();
                if ((*it)->getTimestamp() > t_endTime) {
                    it = tmpEvents.erase(it);
                } else {
                    it++;
                }
            }
            for (auto& iter : tmpEvents) {
                cout << iter->getTimestamp() << endl;
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

        move(weekEvents.begin(), weekEvents.end(), back_inserter(events));

        struct tm* tm_date = localtime(&t_currentTime);
        tm_date->tm_mday += 7;
        t_currentTime = mktime(tm_date);
    }

    return events;
}