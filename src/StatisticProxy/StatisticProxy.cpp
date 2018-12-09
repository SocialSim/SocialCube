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
    // initProxySourceFile();
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

void StatisticProxy::parseSubEventTypeProbability() {
    DBG(LOGD(TAG, "\nsubEventTypeProbability: " + m_defaultSubEventTypeProbabilityProxyFile);)
    cout << "in parseSubEventTypeProbability"<< endl;
    std::ifstream filestream;

    filestream.open(m_defaultSubEventTypeProbabilityProxyFile);

    string tmp;
    while (getline(filestream, tmp)) {
        string key = tmp.substr(0, tmp.find("="));
        double p = stod(tmp.substr(tmp.find("=") + 1));
        m_subEventTypeProbability[key] = p;
    }

    cout << "parseSubEventTypeProbability()" << endl;
    for (auto i : m_subEventTypeProbability) {
        cout << i.first << " = " << i.second << endl;
    }
}

void StatisticProxy::parsePostScale() {
    DBG(LOGD(TAG, "\npostScaleProxyFile: " + m_defaultPostScaleProxyFile);)
    m_postScaleProxy.reset(new PostScaleProxy(m_defaultPostScaleProxyFile));
    m_postScaleProxy->parse();
}

void StatisticProxy::parseCommentProbability() {
    DBG(LOGD(TAG, "\ncommentProbabilityProxyFile: " + m_defaultCommentProbabilityProxyFile);)
    m_commentProbabilityProxy.reset(new CommentProbabilityProxy(m_defaultCommentProbabilityProxyFile));
    m_commentProbabilityProxy->parse();
}

void StatisticProxy::parsePostLifespanDistribution() {
    DBG(LOGD(TAG, "\nparsePostLifespanDistributionProxyFile: " + m_defaultPostLifespanDistributionProxyFile);)
    m_postLifespanDistributionProxy.reset(new PostLifespanDistributionProxy(m_defaultPostLifespanDistributionProxyFile));
    m_postLifespanDistributionProxy->parse();
}

void StatisticProxy::parseScoreMatrix() {
    DBG(LOGD(TAG, "\nscoreMatrixProxyFile: " + m_defaultScoreMatrixProxyFile);)
    m_scoreMatrixProxy.reset(new ScoreMatrixProxy(m_defaultScoreMatrixProxyFile, m_defaultInactiveUserFile));
    m_scoreMatrixProxy->parse();
}

void StatisticProxy::parseCommunityDistribution() {
    DBG(LOGD(TAG, "\ncommunityDistributionProxyFile: " + m_defaultCommunityDistributionProxyFile);)
    m_communityDistributionProxy.reset(new CommunityDistributionProxy(m_defaultCommunityDistributionProxyFile));
    m_communityDistributionProxy->parse();
}

void StatisticProxy::parseMiscellaneous() {
    DBG(LOGD(TAG, "\nmiscellaneousProxyFile: " + m_defaultMiscellaneousProxyFile);)
    m_miscellaneousProxy.reset(new MiscellaneousProxy(m_defaultMiscellaneousProxyFile));
    m_miscellaneousProxy->parse();
}

void StatisticProxy::parseSeedEvents() {
    DBG(LOGD(TAG, "\nseedEventsProxyFile: " + m_defaultSeedEventsProxyFile);)
    m_seedEventsProxy.reset(new SeedEventsProxy(m_defaultSeedEventsProxyFile));
    m_seedEventsProxy->parse();
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

PostScale& StatisticProxy::getPostScale(const std::string &userID) const {
    return m_postScaleProxy->get(userID);
}

CommentProbability& StatisticProxy::getCommentProbability(const std::string &userID) const {
    return m_commentProbabilityProxy->get(userID);
}

PostLifespanDistribution& StatisticProxy::getPostLifespanDistribution(const std::string &userID) const {
    return m_postLifespanDistributionProxy->get(userID);
}

unordered_map<string, double> StatisticProxy::getCommunityDistribution(const std::string &userID) const {
    return m_communityDistributionProxy->get(userID);
}

unordered_map<string, double> StatisticProxy::getActionTypeDistribution() const {
    return m_miscellaneousProxy->getActionTypeDistribution();
}

double* StatisticProxy::getQuartile() const {
    return m_miscellaneousProxy->getQuartile();
}

unordered_map<string, double> StatisticProxy::getEmbeddingParams() const {
    return m_miscellaneousProxy->getEmbeddingParams();
};

vector<double> StatisticProxy::getPostHourDistribution() const {
    return m_miscellaneousProxy->getPostHourDistribution();
}

ScoreMatrix& StatisticProxy::getScoreMatrix() const {
    return m_scoreMatrixProxy->get();
}

vector<Event> StatisticProxy::getSeedEvents(string t_user_id) const {
    return m_seedEventsProxy->get(t_user_id);
}

std::unordered_map<std::string, double> StatisticProxy::getSubEventTypeProbability() const {
    return m_subEventTypeProbability;
}

UserDistribution& StatisticProxy::getClassifiedUserTypeDistribution(const std::string &event_type, const std::string &repoID) {
    auto pos = m_classifiedUserDistributionProxies.find(event_type);
    return (pos->second)->get(repoID);
}

std::vector<std::string> StatisticProxy::getEventTypes() const {
    vector<string> eventTypes;
    for(auto it = m_event_types.begin(); it != m_event_types.end(); ++it) {
        eventTypes.push_back(it->second);
    }
    cout << "eventTypes size = " << eventTypes.size() << endl;

    return eventTypes;
}

void StatisticProxy::initProxySourceFile(const std::string &default_file_path) {

    const string socialcubePath = default_file_path;

    m_defaultUserIDProxyFile = default_file_path + "/user_id.json";
    m_defaultObjectIDProxyFile = default_file_path + "/obj_id.json";
    m_defaultHourlyActionRateProxyFile = default_file_path + "/user_action_rate.json";
    m_defaultDailyActivityLevelProxyFile = default_file_path + "/daily_activity_level.json";
    m_defaultObjectPreferenceProxyFile = default_file_path + "/user_object_preference.json";
    m_defaultTypeDistributionProxyFile = default_file_path + "/user_type_distribution.json";
    m_defaultUserDistributionProxyFile = default_file_path + "/repo_user_distribution.json";
    m_defaultPointProcessStatsProxyFile = default_file_path + "/point_stats.json";
    m_defaultPoissonProcessStatsProxyFile = default_file_path + "/poisson_stats.json";
    m_defaultSubEventTypeProbabilityProxyFile = default_file_path + "/subEventTypeProbability.csv";
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

void StatisticProxy::setSubEventTypeProbabilityProxyFilePath(std::string subEventTypeProbabilityProxyFilePath) {
    m_defaultSubEventTypeProbabilityProxyFile = subEventTypeProbabilityProxyFilePath;
}

void StatisticProxy::setPostScaleProxyFilePath(std::string postScaleProxyFilePath) {
    m_defaultPostScaleProxyFile = postScaleProxyFilePath;
}
void StatisticProxy::setCommentProbabilityProxyFilePath(std::string commentProbabilityFilePath) {
    m_defaultCommentProbabilityProxyFile = commentProbabilityFilePath;
}

void StatisticProxy::setCommunityDistributionProxyFilePath(std::string communityDistributionFilePath) {
    m_defaultCommunityDistributionProxyFile = communityDistributionFilePath;
}

void StatisticProxy::setMiscellaneousProxyFilePath(std::string miscellaneousFilePath) {
    cout << "in StatisticProxy::setMiscellaneousProxyFilePath, miscellaneousFilePath = " << miscellaneousFilePath << endl;
    m_defaultMiscellaneousProxyFile = miscellaneousFilePath;
}

void StatisticProxy::setPostLifespanDistributionProxyFilePath(std::string postLifespanDistributionFilePath) {
    m_defaultPostLifespanDistributionProxyFile = postLifespanDistributionFilePath;
}

void StatisticProxy::setScoreMatrixProxyFilePath(std::string scoreMatrixProxyFilePath) {
    m_defaultScoreMatrixProxyFile = scoreMatrixProxyFilePath;
}

void StatisticProxy::setInactiveUserFilePath(std::string inactiveUserFilePath) {
    m_defaultInactiveUserFile = inactiveUserFilePath;
}

void StatisticProxy::setSeedEventsFilePath(std::string seedEventsFilePath) {
    m_defaultSeedEventsProxyFile = seedEventsFilePath;
}


uint64_t StatisticProxy::getUserCommunityTag(const std::string &userID) const {
    return m_userIDProxy->getCommunityTag(userID);
}

void StatisticProxy::setCommitCommentEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["commitCommentEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setDeleteEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["deleteEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setIssueCommentEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["issueCommentEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setPullRequestEventUserDistributionProxyFilePath(std::string path){
    m_defaultClassifiedUserDistributionProxyFiles["pullRequestEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setPushEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["pushEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setCreateEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["createEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setForkEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["forkEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setIssueEventUserDistributionProxyFilePath(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["issueEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setPullRequestReviewCommentEventUserDistributionProxyFile(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["pullRequestReviewCommentEventUserDistributionProxyFile"] = path;
}

void StatisticProxy::setWatchEventUserDistributionProxyFile(std::string path) {
    m_defaultClassifiedUserDistributionProxyFiles["watchEventUserDistributionProxyFile"] = path;
}