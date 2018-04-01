#include "HourlyActionRateProxy.hpp"

using namespace std;

HourlyActionRateProxy::HourlyActionRateProxy(const string& file) throw() {
    try {
        m_hourlyActionRateStatisticFile.open (file);
    } catch (exception &e) {
        HourlyActionRateProxyException h_e;
        throw h_e;
    }
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
            double activityLevel;
            getline(m_hourlyActionRateStatisticFile, tmp);
            istringstream in(tmp);
            in >> userID >> activityLevel;
            for(int j = 0; j < 24; ++j) {
                double prob;
                in >> prob;
                hourlyActionRate->setHourlyActionRate(j, prob, activityLevel);
            }
        }
        m_hourlyActionRate[userID] = move(hourlyActionRate);
    }
    cout << "Hourly Action Rate has " << m_hourlyActionRate.size() << endl;
}

void HourlyActionRateProxy::show() {
    cout << m_hourlyActionRate.size() << endl; 
    for(auto& iter : m_hourlyActionRate) {
        iter.second->show();
    }
}

HourlyActionRate& HourlyActionRateProxy::get(const std::string& userID) {
    if(m_hourlyActionRate.find(userID) == m_hourlyActionRate.end()) {
        return *(m_hourlyActionRate["-1"]);
    } else {
        assert(m_hourlyActionRate.find(userID) != m_hourlyActionRate.end());
        return *(m_hourlyActionRate[userID]);
    }
}
