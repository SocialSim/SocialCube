#include "StatisticProxy.hpp"
#include <fstream>

using namespace std;

DBG(static const string tag="StatisticProxy";)

const std::unordered_map<std::string, std::string> StatisticProxy::m_event_types{
        {"issueEventUserDistributionProxyFile", "IssuesEvent"},
        {"pullRequestReviewCommentEventUserDistributionProxyFile", "PullRequestReviewCommentEvent"},
        {"pushEventUserDistributionProxyFile", "PushEvent"},
        {"pullRequestEventUserDistributionProxyFile", "PullRequestEvent"},
        {"issueCommentEventUserDistributionProxyFile", "IssueCommentEvent"},
        {"createEventUserDistributionProxyFile", "CreateEvent"},
        {"watchEventUserDistributionProxyFile", "WatchEvent"},
        {"forkEventUserDistributionProxyFile", "ForkEvent"},
        {"deleteEventUserDistributionProxyFile", "DeleteEvent"},
        {"commitCommentEventUserDistributionProxyFile", "CommitCommentEvent"}};

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
    DBG(LOGD(TAG, "\nuserIDProxyFile: " + m_defaultUserIDProxyFile);)
    m_userIDProxy.reset(new UserIDProxy(m_defaultUserIDProxyFile));
    m_userIDProxy->parse();
}

void StatisticProxy::parseObjectID() {
    DBG(LOGD(TAG, "\nobjectIDProxyFile: " + m_defaultObjectIDProxyFile);)
    m_objectIDProxy.reset(new ObjectIDProxy(m_defaultObjectIDProxyFile));
    m_objectIDProxy->parse();
}

void StatisticProxy::parseObjectPreference() {
    DBG(LOGD(TAG, "\nobjectPreferenceProxyFile: " + m_defaultObjectPreferenceProxyFile);)
    m_objectPreferenceProxy.reset(new ObjectPreferenceProxy(m_defaultObjectPreferenceProxyFile));
    m_objectPreferenceProxy->parse();
}

void StatisticProxy::parseHourlyActionRate() {
    DBG(LOGD(TAG, "\nhourlyActionRateProxyFile: " + m_defaultHourlyActionRateProxyFile);)
    m_hourlyActionRateProxy.reset(new HourlyActionRateProxy(m_defaultHourlyActionRateProxyFile));
    m_hourlyActionRateProxy->parse();
}

void StatisticProxy::parseDailyActivityLevel() {
    DBG(LOGD(TAG, "\ndailyActivityLevel: " + m_defaultDailyActivityLevelProxyFile);)
    m_dailyActivityLevelProxy.reset(new DailyActivityLevelProxy(m_defaultDailyActivityLevelProxyFile));
    m_dailyActivityLevelProxy->parse();
}

void StatisticProxy::parseTypeDistribution() {
    DBG(LOGD(TAG, "\ntypeDistributionProxyFile: " + m_defaultTypeDistributionProxyFile);)
    m_typeDistributionProxy.reset(new TypeDistributionProxy(m_defaultTypeDistributionProxyFile));
    m_typeDistributionProxy->parse();
}

void StatisticProxy::parseUserDistribution() {
    DBG(LOGD(TAG, "\nuserDistributionProxyFile: " + m_defaultUserDistributionProxyFile);)
    m_userDistributionProxy.reset(new UserDistributionProxy(m_defaultUserDistributionProxyFile));
    m_userDistributionProxy->parse();
}

void StatisticProxy::parsePointProcessStats() {
    DBG(LOGD(TAG, "\npointProcessStatsProxyFile: " + m_defaultPointProcessStatsProxyFile);)
    m_pointProcessProxy.reset(new PointProcessProxy(m_defaultPointProcessStatsProxyFile));
    m_pointProcessProxy->parse();
}

void StatisticProxy::parsePoissonProcessStats() {
    DBG(LOGD(TAG, "\npoissonProcessStatsProxyFile: " + m_defaultPoissonProcessStatsProxyFile);)
    m_poissonProcessProxy.reset(new PoissonProcessProxy(m_defaultPoissonProcessStatsProxyFile));
    m_poissonProcessProxy->parse();
}

void StatisticProxy::parseClassifiedUserDistributionStats() {
    for (auto& iter : m_defaultClassifiedUserDistributionProxyFiles) {
        DBG(LOGD(TAG, "\n" + iter.first + ": " + iter.second);)
        unique_ptr<UserDistributionProxy> userDistributionProxy(new UserDistributionProxy(iter.second));
        userDistributionProxy->parse();
        m_classifiedUserDistributionProxies.insert(std::make_pair(m_event_types.find(iter.first)->second, move(userDistributionProxy)));
    }
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

DailyActivityLevel& StatisticProxy::getDailyActivityLevel(const string &userID) const {
    return m_dailyActivityLevelProxy->get(userID);
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

PointProcessStat& StatisticProxy::getPointProcessStats(const std::string &repoID) const {
    return m_pointProcessProxy->get(repoID);
}

PoissonProcessStat& StatisticProxy::getPoissonProcessStats(const std::string &repoID) const {
    return m_poissonProcessProxy->get(repoID);
}

UserDistribution& StatisticProxy::getClassifiedUserTypeDistribution(const std::string &event_type, const std::string &repoID) {
    auto pos = m_classifiedUserDistributionProxies.find(event_type);
    return (pos->second)->get(repoID);
};

std::vector<std::string>& StatisticProxy::getEventTypes() const {
    vector<string> eventTypes;
    for(auto it = m_event_types.begin(); it != m_event_types.end(); ++it) {
        eventTypes.push_back(it->second);
    }

    return eventTypes;
}

void StatisticProxy::initProxySourceFile() {

    const string socialcubePath = (getenv("SOCIALCUBEPATH"));

    m_defaultUserIDProxyFile = socialcubePath + "/statistics/user_id.json";
    m_defaultObjectIDProxyFile = socialcubePath + "/statistics/obj_id.json";
    m_defaultHourlyActionRateProxyFile = socialcubePath + "/statistics/user_action_rate.json";
    m_defaultDailyActivityLevelProxyFile = socialcubePath + "/statistics/daily_activity_level.json";
    m_defaultObjectPreferenceProxyFile = socialcubePath + "/statistics/user_object_preference.json";
    m_defaultTypeDistributionProxyFile = socialcubePath + "/statistics/user_type_distribution.json";
    m_defaultUserDistributionProxyFile = "/statistics/repo_user_distribution.json";
    m_defaultPointProcessStatsProxyFile = "/statistics/point_stats.json";
    m_defaultPoissonProcessStatsProxyFile = "/statistics/poisson_stats.json";
}

void StatisticProxy::setUserIDProxyFilePath(std::string userIDProxyFilePath) {
    m_defaultUserIDProxyFile = userIDProxyFilePath;
}

void StatisticProxy::setObjectIDProxyFilePath(std::string objectIDProxyFilePath) {
    m_defaultObjectIDProxyFile = objectIDProxyFilePath;
}

void StatisticProxy::setHourlyActionRateProxyFilePath(std::string hourlyActionRateProxyFilePath) {
    m_defaultHourlyActionRateProxyFile = hourlyActionRateProxyFilePath;
}

void StatisticProxy::setDailyActivityLevelProxyFilePath(std::string dailyActivityLevelProxyFilePath) {
    m_defaultDailyActivityLevelProxyFile = dailyActivityLevelProxyFilePath;
}

void StatisticProxy::setObjectPreferenceProxyFilePath(std::string objectPreferenceProxyFilePath) {
    m_defaultObjectPreferenceProxyFile = objectPreferenceProxyFilePath;
}

void StatisticProxy::setTypeDistributionProxyFilePath(std::string typeDistributionProxyFilePath) {
    m_defaultTypeDistributionProxyFile = typeDistributionProxyFilePath;
}

void StatisticProxy::setUserDistributionProxyFilePath(std::string userDistributionProxyFilePath) {
    m_defaultUserDistributionProxyFile = userDistributionProxyFilePath;
}

void StatisticProxy::setPointProcessStatsProxyFilePath(std::string pointProcessStatsProxyFilePath) {
    m_defaultPointProcessStatsProxyFile = pointProcessStatsProxyFilePath;
}

void StatisticProxy::setPoissonProcessStatsProxyFilePath(std::string poissonProcessProxyStatsFilePath) {
    m_defaultPoissonProcessStatsProxyFile = poissonProcessProxyStatsFilePath;
}

uint64_t StatisticProxy::getUserCommunityTag(const std::string &userID) const {
    return m_userIDProxy->getCommunityTag(userID);
}

void StatisticProxy::setCommitCommentEventUserDistributionProxyFilePath(std::string path) {
    m_defaultCommitCommentEventUserDistributionProxyFile = path;
}

void StatisticProxy::setDeleteEventUserDistributionProxyFilePath(std::string path) {
    m_defaultDeleteEventUserDistributionProxyFile = path;
}

void StatisticProxy::setIssueCommentEventUserDistributionProxyFilePath(std::string path) {
    m_defaultIssueCommentEventUserDistributionProxyFile = path;
}

void StatisticProxy::setPullRequestEventUserDistributionProxyFilePath(std::string path){
    m_defaultPullRequestEventUserDistributionProxyFile = path;
}

void StatisticProxy::setPushEventUserDistributionProxyFilePath(std::string path) {
    m_defaultPushEventUserDistributionProxyFile = path;
}

void StatisticProxy::setCreateEventUserDistributionProxyFilePath(std::string path) {
    m_defaultCreateEventUserDistributionProxyFile = path;
}

void StatisticProxy::setForkEventUserDistributionProxyFilePath(std::string path) {
    m_defaultForkEventUserDistributionProxyFile = path;
}

void StatisticProxy::setIssueEventUserDistributionProxyFilePath(std::string path) {
    m_defaultIssueEventUserDistributionProxyFile = path;
}

void StatisticProxy::setPullRequestReviewCommentEventUserDistributionProxyFile(std::string path) {
    m_defaultPullRequestReviewCommentEventUserDistributionProxyFile = path;
}

void StatisticProxy::setWatchEventUserDistributionProxyFile(std::string path) {
    m_defaultWatchEventUserDistributionProxyFile = path;
}
