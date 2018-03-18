#include "StatisticProxy.hpp"

using namespace std;

StatisticProxy& StatisticProxy::getInstance() {
    static StatisticProxy instance;
    return instance;
}

StatisticProxy::StatisticProxy() {
    return;
}

StatisticProxy::~StatisticProxy() {
    return;
}

void StatisticProxy::retrieveStatistics() {
    retrieveUserIDs();
    retrieveObjIDs();
    retrieveUserActionRate();
    retrieveObjectPreference();
    retrieveUserDependency();
}

void StatisticProxy::retrieveUserIDs() {
}

void StatisticProxy::retrieveObjIDs() {
}

void StatisticProxy::retrieveUserActionRate() {
}

void StatisticProxy::retrieveObjectPreference() {
}

void StatisticProxy::retrieveUserDependency() {
}

vector<string>& StatisticProxy::getUserIds() {
    return m_userIDs;
}

vector<string>& StatisticProxy::getObjectIds() {
    return m_objectIDs;
}

UserActionRate& StatisticProxy::getUserHourlyActionRate(const string &userID) {
    return m_allUserActionRate[userID];
}

ObjectPreference& StatisticProxy::getUserObjectPreference(const string &userID) {
    return m_allObjectPreference[userID];
}

UserDependency& StatisticProxy::getUserDependency(const string &userID) {
    return m_allUserDepency[userID];
}
