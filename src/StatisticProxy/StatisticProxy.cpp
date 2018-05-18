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

void StatisticProxy::startParsing() {
    std::cout << "m_defaultUserIDProxyFile = " << m_defaultUserIDProxyFile << std::endl;
    std::cout << "m_defaultObjectIDProxyFile = " << m_defaultObjectIDProxyFile << std::endl;

    m_userIDProxy.reset(new UserIDProxy(m_defaultUserIDProxyFile));
    m_objectIDProxy.reset(new ObjectIDProxy(m_defaultObjectIDProxyFile));
    m_objectPreferenceProxy.reset(new ObjectPreferenceProxy(m_defaultObjectPreferenceProxyFile));
    m_hourlyActionRateProxy.reset(new HourlyActionRateProxy(m_defaultHourlyActionRateProxyFile));
    m_typeDistributionProxy.reset(new TypeDistributionProxy(m_defaultTypeDistributionProxyFile));
    if (m_defaultPointProcessProxyFile.length() > 0) {
        std::cout << "Using Point model, pointProcessProxyFile =" << m_defaultPointProcessProxyFile << std::endl;
        m_pointProcessProxy.reset(new PointProcessProxy(m_defaultPointProcessProxyFile));
        m_pointProcessProxy->parse();
    }
    if (m_defaultPoissonProcessProxyFile.length() > 0) {
        std::cout << "Using Poisson model, poissonProcessProxyFile =" << m_defaultPoissonProcessProxyFile << std::endl;
        m_poissonProcessProxy.reset(new PoissonProcessProxy(m_defaultPoissonProcessProxyFile));
        m_poissonProcessProxy->parse();
    }

    m_userIDProxy->parse();
    m_objectIDProxy->parse();
    m_objectPreferenceProxy->parse();
    m_hourlyActionRateProxy->parse();
    m_typeDistributionProxy->parse();

    initProxySourceFile();
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

PoissonProcessStat& StatisticProxy::getPoissonProcessStat(const std::string &userID) const {
    return m_poissonProcessProxy->get(userID);
}

void StatisticProxy::initProxySourceFile() {

    const string socialcubePath = (getenv("SOCIALCUBEPATH"));

    m_defaultUserIDProxyFile = socialcubePath + "/statistics/user_id.json";
    m_defaultObjectIDProxyFile = socialcubePath + "/statistics/obj_id.json";
    m_defaultHourlyActionRateProxyFile = socialcubePath + "/statistics/user_action_rate.json";
    m_defaultObjectPreferenceProxyFile = socialcubePath + "/statistics/user_object_preference.json";
    m_defaultTypeDistributionProxyFile = socialcubePath + "/statistics/user_type_distribution.json";
    m_defaultPointProcessProxyFile = "";
    m_defaultPoissonProcessProxyFile = "";
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

void StatisticProxy::setPointProcessProxyFilePath(std::string pointProcessProxyFilePath) {
    m_defaultPointProcessProxyFile = (getenv("SOCIALCUBEPATH")) + pointProcessProxyFilePath;
}

void StatisticProxy::setPoissonProcessProxyFilePath(std::string poissonProcessProxyFilePath) {
    m_defaultPoissonProcessProxyFile = (getenv("SOCIALCUBEPATH")) + poissonProcessProxyFilePath;
}

uint64_t StatisticProxy::getUserCommunityTag(const std::string &userID) const {
    return m_userIDProxy->getCommunityTag(userID);
} 
