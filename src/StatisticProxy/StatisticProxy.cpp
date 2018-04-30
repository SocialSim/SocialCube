#include "StatisticProxy.hpp"

using namespace std;

StatisticProxy& StatisticProxy::getInstance() {
    static StatisticProxy instance;
    return instance;
}

StatisticProxy::StatisticProxy() {

    initProxySourceFile();

    m_userIDProxy.reset(new ClusteredUserIDProxy(m_defaultUserIDProxyFile));
    m_objectIDProxy.reset(new ObjectIDProxy(m_defaultObjectIDProxyFile));
    m_objectPreferenceProxy.reset(new ObjectPreferenceProxy(m_defaultObjectPreferenceProxyFile));
    m_hourlyActionRateProxy.reset(new HourlyActionRateProxy(m_defaultHourlyActionRateProxyFile));
    m_typeDistributionProxy.reset(new TypeDistributionProxy(m_defaultTypeDistributionProxyFile));
    m_pointProcessProxy.reset(new PointProcessProxy(m_defaultPointProcessProxyFile));

    m_userIDProxy->parse();
    m_objectIDProxy->parse();
    m_objectPreferenceProxy->parse();
    m_hourlyActionRateProxy->parse();
    m_typeDistributionProxy->parse();
    m_pointProcessProxy->parse();

    return;
}

StatisticProxy::~StatisticProxy() {
    return;
}

vector<string>& StatisticProxy::getUserIDs() const {
    return m_userIDProxy->get();
}

vector<string>& StatisticProxy::getObjectIDs() const {
    return m_objectIDProxy->get();
}

HourlyActionRate& StatisticProxy::getUserHourlyActionRate(const string &userID) const {
    return m_hourlyActionRateProxy->get(userID);
}

ObjectPreference& StatisticProxy::getUserObjectPreference(const string &userID) const {
    return m_objectPreferenceProxy->get(userID);
}

TypeDistribution& StatisticProxy::getUserTypeDistribution(const std::string &userID) const {
    return m_typeDistributionProxy->get(userID);
} 

PointProcessStat& StatisticProxy::getPointProcessStat(const std::string &userID) const {
    return m_pointProcessProxy->get(userID);
} 

void StatisticProxy::initProxySourceFile() {

    const string socialcubePath = (getenv("SOCIALCUBEPATH"));

    m_defaultUserIDProxyFile = socialcubePath + "/statistics/user_id.json";
    m_defaultObjectIDProxyFile = socialcubePath + "/statistics/obj_id.json";
    m_defaultHourlyActionRateProxyFile = socialcubePath + "/statistics/user_action_rate.json";
    m_defaultObjectPreferenceProxyFile= socialcubePath + "/statistics/user_object_preference.json";
    m_defaultTypeDistributionProxyFile = socialcubePath + "/statistics/user_type_distribution.json";
    m_defaultPointProcessProxyFile = socialcubePath + "/statistics/point_process.json";
}

uint64_t StatisticProxy::getUserCommunityTag(const std::string &userID) const {
    return m_userIDProxy->getCommunityTag(userID);
} 
