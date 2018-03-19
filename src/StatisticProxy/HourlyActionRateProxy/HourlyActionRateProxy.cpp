#include "HourlyActionRateProxy.hpp"

using namespace std;

HourlyActionRateProxy::HourlyActionRateProxy() {
    m_hourlyActionRateStatisticFile.open ("/home/parallels/Desktop/SocialCube/statistics/user_action_rate.json");
    assert(m_hourlyActionRateStatisticFile.is_open());
    return;
}

HourlyActionRateProxy::~HourlyActionRateProxy() {
    m_hourlyActionRateStatisticFile.close();
    return;
}

void HourlyActionRateProxy::parse() {
    string tmp;
    while (getline(m_hourlyActionRateStatisticFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string eventTypeCount = tmp.substr(tmp.find(" ") + 1);
        unique_ptr<HourlyActionRate> hourlyActionRate(new HourlyActionRate(userID));
        for(int i = 0; i < stoi(eventTypeCount); ++i) {
            uint64_t activityLevel;
            string eventType;
            getline(m_hourlyActionRateStatisticFile, tmp);
            istringstream in(tmp);
            in >> userID >> activityLevel >> eventType;
            for(int j = 0; j < 24; ++j) {
                double prob;
                in >> prob;
                hourlyActionRate->setHourlyActionRate(eventType, j, prob, activityLevel);
            }
        }
        m_hourlyActionRate[userID] = move(hourlyActionRate);
    }
}

void HourlyActionRateProxy::show() {
    cout << m_hourlyActionRate.size() << endl; 
    for(auto& iter : m_hourlyActionRate) {
        iter.second->show();
    }
}

HourlyActionRate& HourlyActionRateProxy::get(const std::string& userID) {
    return *(m_hourlyActionRate[userID]);
}
