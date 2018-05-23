#include "StatisticProxy.hpp"
#include <fstream>

using namespace std;

StatisticProxy& StatisticProxy::getInstance() {
    static StatisticProxy instance;
    return instance;
}

StatisticProxy::StatisticProxy() {

    initProxySourceFile();

    return;
}

StatisticProxy::~StatisticProxy() {
    return;
}

void StatisticProxy::parseUserID() {
    m_userIDProxy.reset(new UserIDProxy(m_defaultUserIDProxyFile));
    m_userIDProxy->parse();
}

void StatisticProxy::parseObjectID() {
    m_objectIDProxy.reset(new ObjectIDProxy(m_defaultObjectIDProxyFile));
    m_objectIDProxy->parse();
}

void StatisticProxy::parseObjectPreference() {
    m_objectPreferenceProxy.reset(new ObjectPreferenceProxy(m_defaultObjectPreferenceProxyFile));
    m_objectPreferenceProxy->parse();
}

void StatisticProxy::parseHourlyActionRate() {
    m_hourlyActionRateProxy.reset(new HourlyActionRateProxy(m_defaultHourlyActionRateProxyFile));
    m_hourlyActionRateProxy->parse();
}

void StatisticProxy::parseTypeDistribution() {
    m_typeDistributionProxy.reset(new TypeDistributionProxy(m_defaultTypeDistributionProxyFile));
    m_typeDistributionProxy->parse();
}

void StatisticProxy::parseUserDistribution() {
    m_userDistributionProxy.reset(new UserDistributionProxy(m_defaultUserDistributionProxyFile));
    m_userDistributionProxy->parse();
}

void StatisticProxy::parsePointProcessStats() {
    m_pointProcessProxy.reset(new PointProcessProxy(m_defaultPointProcessStatsProxyFile));
    m_pointProcessProxy->parse();
}

void StatisticProxy::parsePoissonProcessStats() {
    m_poissonProcessProxy.reset(new PoissonProcessProxy(m_defaultPoissonProcessStatsProxyFile));
    m_poissonProcessProxy->parse();
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

UserDistribution& StatisticProxy::getRepoUserDistribution(const std::string &repoID) const {
        return m_userDistributionProxy->get(repoID);
}

PointProcessStat& StatisticProxy::getPointProcessStats(const std::string &userID) const {
    return m_pointProcessProxy->get(userID);
}

PoissonProcessStat& StatisticProxy::getPoissonProcessStats(const std::string &userID) const {
    return m_poissonProcessProxy->get(userID);
}

void StatisticProxy::initProxySourceFile() {

    const string socialcubePath = (getenv("SOCIALCUBEPATH"));

    m_defaultUserIDProxyFile = socialcubePath + "/statistics/user_id.json";
    m_defaultObjectIDProxyFile = socialcubePath + "/statistics/obj_id.json";
    m_defaultHourlyActionRateProxyFile = socialcubePath + "/statistics/user_action_rate.json";
    m_defaultObjectPreferenceProxyFile = socialcubePath + "/statistics/user_object_preference.json";
    m_defaultTypeDistributionProxyFile = socialcubePath + "/statistics/user_type_distribution.json";
    m_defaultUserDistributionProxyFile = "";
    m_defaultPointProcessStatsProxyFile = "";
    m_defaultPoissonProcessStatsProxyFile = "";
}

void StatisticProxy::setUserIDProxyFilePath(std::string userIDProxyFilePath) {
    m_defaultUserIDProxyFile = (getenv("SOCIALCUBEPATH")) + userIDProxyFilePath;
}

void StatisticProxy::setObjectIDProxyFilePath(std::string objectIDProxyFilePath) {
    m_defaultObjectIDProxyFile = (getenv("SOCIALCUBEPATH")) + objectIDProxyFilePath;
}

void StatisticProxy::setHourlyActionRateProxyFilePath(std::string hourlyActionRateProxyFilePath) {
    m_defaultHourlyActionRateProxyFile = (getenv("SOCIALCUBEPATH")) + hourlyActionRateProxyFilePath;
}

void StatisticProxy::setObjectPreferenceProxyFilePath(std::string objectPreferenceProxyFilePath) {
    m_defaultObjectPreferenceProxyFile = (getenv("SOCIALCUBEPATH")) + objectPreferenceProxyFilePath;
}

void StatisticProxy::setTypeDistributionProxyFilePath(std::string typeDistributionProxyFilePath) {
    m_defaultTypeDistributionProxyFile = (getenv("SOCIALCUBEPATH")) + typeDistributionProxyFilePath;
}

void StatisticProxy::setUserDistributionProxyFilePath(std::string userDistributionProxyFilePath) {
    m_defaultUserDistributionProxyFile = (getenv("SOCIALCUBEPATH")) + userDistributionProxyFilePath;
}

void StatisticProxy::setPointProcessStatsProxyFilePath(std::string pointProcessStatsProxyFilePath) {
    m_defaultPointProcessStatsProxyFile = (getenv("SOCIALCUBEPATH")) + pointProcessStatsProxyFilePath;
}

void StatisticProxy::setPoissonProcessStatsProxyFilePath(std::string poissonProcessProxyStatsFilePath) {
    m_defaultPoissonProcessStatsProxyFile = (getenv("SOCIALCUBEPATH")) + poissonProcessProxyStatsFilePath;
}

uint64_t StatisticProxy::getUserCommunityTag(const std::string &userID) const {
    return m_userIDProxy->getCommunityTag(userID);
} 
