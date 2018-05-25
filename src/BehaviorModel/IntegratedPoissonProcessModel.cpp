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
                cout << "eventTime = " << ctime(&eventTime) << ", time_t = " << eventTime << endl;
            }
            double ratio = (7*24*60) / (currentMinute - startMinute);
            for (auto& e : tmpEvents) {
                cout << "---------------------" << endl;
                cout << "repoID = " << objectID << ", actionType = " << actionType << ", currentMinute = " << \
                 currentMinute << ", startMinute = " << startMinute;
                cout << ", ratio = " << ratio << endl;
                e->warpTimestamp(startMinute * 60, ratio);
            }
            move(tmpEvents.begin(), tmpEvents.end(), back_inserter(weekEvents));
        }
        // Get the first eventNum events
        sort(weekEvents.begin(),
                  weekEvents.end(),
                  [](const unique_ptr<Event>& lhs, const unique_ptr<Event>& rhs) {
                      return lhs->getTimestamp() < rhs->getTimestamp();
                  });

        weekEvents.resize(eventNum);

        move(weekEvents.begin(), weekEvents.end(), back_inserter(events));

        struct tm* tm_date = localtime(&t_currentTime);
        tm_date->tm_mday += 7;
        t_currentTime = mktime(tm_date);
    }
    return events;
}