#include "StatisticProxy.hpp"

using namespace std;

StatisticProxy& StatisticProxy::getInstance() {
    static StatisticProxy instance;
    return instance;
}

StatisticProxy::StatisticProxy() :
    m_userIDProxy(new UserIDProxy),
    m_objectIDProxy(new ObjectIDProxy),
    m_objectPreferenceProxy(new ObjectPreferenceProxy),
    m_hourlyActionRateProxy(new HourlyActionRateProxy) {

    m_userIDProxy->parse();
    m_objectIDProxy->parse();
    m_objectPreferenceProxy->parse();
    m_hourlyActionRateProxy->parse();

    return;
}

StatisticProxy::~StatisticProxy() {
    return;
}

vector<string>& StatisticProxy::getUserIds() {
    return m_userIDProxy->get();
}

vector<string>& StatisticProxy::getObjectIds() {
    return m_objectIDProxy->get();
}

HourlyActionRate& StatisticProxy::getUserHourlyActionRate(const string &userID) {
    return m_hourlyActionRateProxy->get(userID);
}

ObjectPreference& StatisticProxy::getUserObjectPreference(const string &userID) {
    return m_objectPreferenceProxy->get(userID);
}
