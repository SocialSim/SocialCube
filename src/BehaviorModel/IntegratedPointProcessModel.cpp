#include "IntegratedPointProcessModel.hpp"

using namespace std;

std::vector<unique_ptr<Event>> IntegratedPointProcessModel::evaluate(
        const string objectID,
        const vector<double>& mu,
        const vector<vector<double>>& alpha,
        const vector<double>& beta,
        const vector<string>& typeList,
        int k,
        time_t t_startTime,
        time_t t_endTime
) {
    // cout << "-------------objectID: " << objectID << "------------" << endl;
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();

    UserDistribution userDistribution = m_statProxy.getRepoUserDistribution(objectID);

    vector<unique_ptr<Event>> events;

    // cout << "in model, userDistribution.getUserDistribution().size() = " << userDistribution.getUserDistribution().size() << endl;

    if (userDistribution.getUserDistribution().size() == 0) {
        return events;
    }
    for (time_t t_currentTime = t_startTime; t_currentTime < t_endTime; ) {
        int eventNum = userDistribution.getTotalCount(t_currentTime);
        vector<string> userIDs = userDistribution.getShuffledUserIDs(t_currentTime);

        // cout << "t_currentTime = " << ctime(&t_currentTime) << ", eventNum = " << eventNum << endl;
        vector<unique_ptr<Event>> weekEvents;

        double currentMinute = t_currentTime / 60;
        double startMinute = t_currentTime / 60;

        int simulationCount = 0;

        vector<double> upperIntensity = mu;

        while(weekEvents.size() < eventNum) {
            auto interval = matops::mul(matops::ones(k), 10000);

            // Avoid infinite simulation, restart the simulation.
            if(weekEvents.size() > 100000) {
                currentMinute = t_currentTime / 60;
                upperIntensity = mu;
                weekEvents.clear();
                simulationCount++;
            }

            for(int i = 0; i < k; ++i) {
                double temInterval = 0.0;
                while(1) {
                    double intensity = mu[i] + ((upperIntensity[i] - mu[i]) * exp(-beta[i] * temInterval));
                    double u = (double)rand() / RAND_MAX;
                    double delta = -log(u) / (intensity + 1e-7);
                    temInterval += delta;
                    double s = (double)rand() / RAND_MAX;
                    double temIntensity = mu[i] + (intensity - mu[i]) * exp(-beta[i] * delta);
                    if(s <= (temIntensity + 1e-7) / (intensity + 1e-7)) {
                        interval[i] = temInterval;
                        break;
                    }
                }
            }

            int j = matops::minargs(interval);
            string actionType = typeList[j];
            double minInterval = interval[j];
            currentMinute += minInterval;

            string userID = userIDs[weekEvents.size()];

            time_t eventTime = currentMinute * 60;
            unique_ptr<Event> event(new Event(userID, objectID, actionType, eventTime));
            weekEvents.push_back(move(event));

            upperIntensity = matops::add(mu, matops::mul(matops::minus(upperIntensity, mu), matops::exp(matops::mul(matops::inv(beta), minInterval))));
            upperIntensity = matops::add(upperIntensity, matops::mul(alpha[j], beta));
        }

        double ratio = (7*24*60) / (currentMinute - startMinute);
        // cout << "ratio = " << ratio << endl;
        for (auto& e : weekEvents) {
            e->warpTimestamp(startMinute * 60, ratio);
        }

        move(weekEvents.begin(), weekEvents.end(), back_inserter(events));
        // cout << "weekEvent.size = " << weekEvents.size() << "event.size = " << events.size() << endl;
        // Add 1 week
        struct tm* tm_date = localtime(&t_currentTime);
        tm_date->tm_mday += 7;
        t_currentTime = mktime(tm_date);
    }
    return events;
}
