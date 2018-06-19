#include "AgentBuilder.hpp"

template<class TUserAgent, class TObjectAgent>
AgentBuilder<TUserAgent, TObjectAgent>::AgentBuilder() : m_statProxy(StatisticProxy::getInstance()) {
    return;
}

template<class TUserAgent, class TObjectAgent>
AgentBuilder<TUserAgent, TObjectAgent>::~AgentBuilder() {
    return;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::setFilePath(const std::string fileName, const std::string filePath) {
    if (fileName == "userIDProxyFile") {
        m_statProxy.setUserIDProxyFilePath(filePath);
    } else if (fileName == "objectIDProxyFile") {
        m_statProxy.setObjectIDProxyFilePath(filePath);
    } else if (fileName == "hourlyActionRateProxyFile") {
        m_statProxy.setHourlyActionRateProxyFilePath(filePath);
    } else if (fileName == "dailyActivityLevelProxyFile") {
        cout << "set dailyActivityLevelFile path" << endl;
        m_statProxy.setDailyActivityLevelProxyFilePath(filePath);
    } else if (fileName == "objectPreferenceProxyFile") {
        m_statProxy.setObjectPreferenceProxyFilePath(filePath);
    } else if (fileName == "typeDistributionProxyFile") {
        m_statProxy.setTypeDistributionProxyFilePath(filePath);
    } else if (fileName == "pointProcessStatsProxyFile") {
        m_statProxy.setPointProcessStatsProxyFilePath(filePath);
    } else if (fileName == "poissonProcessStatsProxyFile") {
        m_statProxy.setPoissonProcessStatsProxyFilePath(filePath);
    } else if (fileName == "userDistributionProxyFile") {
        m_statProxy.setUserDistributionProxyFilePath((filePath));
    } else if (fileName == "countryCodesProxyFile") {
        m_statProxy.setCountryCodesFilePath(filePath);
    } else if (fileName == "activityLevelsProxyFile") {
        m_statProxy.setActivityLevelFilePath(filePath);
    } else if (fileName == "ccStatsProxyFile") {
        m_statProxy.setCcStatsProxyFilePath(filePath);
    }
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::build() {
    // PointProcess model
    if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, PointProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parsePointProcessStats();
        buildObjects();
    }
    // PoissonProcess model
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, PoissonProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parsePoissonProcessStats();
        buildObjects();
    }
    // SimpleBehavior model (user centric)
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, SimpleGithubObjectAgent>::value) {
        m_statProxy.parseUserID();
        m_statProxy.parseHourlyActionRate();
        m_statProxy.parseObjectPreference();
        m_statProxy.parseTypeDistribution();
        m_statProxy.parseCountryCodesStats();
        m_statProxy.parseActivityLevelStats();
        buildUsers();
    }
    // DailySimpleBehavior model
    else if (std::is_same<TUserAgent, DailySimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, SimpleGithubObjectAgent>::value) {
        m_statProxy.parseUserID();
        m_statProxy.parseDailyActivityLevel();
        m_statProxy.parseObjectPreference();
        m_statProxy.parseTypeDistribution();
        m_statProxy.parseCountryCodesStats();
        m_statProxy.parseActivityLevelStats();
        buildUsers();
    }
    // IntegratedPointProcess model
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, IntegratedPointProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parseUserDistribution();
        m_statProxy.parsePointProcessStats();
        buildObjects();
    } else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, IntegratedPoissonProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parseUserDistribution();
        m_statProxy.parsePoissonProcessStats();
        buildObjects();
    } else {
        cout << "Wrong agent type combination" << endl;
    }
    // Reset proxy source files
    // m_statProxy.initProxySourceFile();
}

template<class TUserAgent, class TObjectAgent>
std::vector<std::shared_ptr<TUserAgent>>& AgentBuilder<TUserAgent, TObjectAgent>::getUserAgentList() {
    return m_userAgents;
}

template<class TUserAgent, class TObjectAgent>
std::vector<std::shared_ptr<TObjectAgent>>& AgentBuilder<TUserAgent, TObjectAgent>::getObjectAgentList() {
    std::cout << "Hello" << std::endl;
    return m_objectAgents;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildUsers() {
    const std::vector<std::string>& userIDs = m_statProxy.getUserIDs();
    const std::vector<std::string>& countryCodes = m_statProxy.getCountryCodes();
    const std::vector<std::string>& activityLevels = m_statProxy.getActivityLevels();

    int count = 0;
    for (int i = 0; i < userIDs.size(); i++) {
        // DBG(LOGD(TAG, "Activity Level #" + activityLevels[i]));
        std::shared_ptr<TUserAgent> agent(new TUserAgent(userIDs[i], countryCodes[i], stoi(activityLevels[i])));
        m_userAgents.push_back(move(agent));
        count++;
    }
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildObjects() {
    const std::vector<std::string>& objectIDs = m_statProxy.getObjectIDs();
    for(auto& objectID : objectIDs) {
        std::shared_ptr<TObjectAgent> agent(new TObjectAgent(objectID, "us", 1));
        m_objectAgents.push_back(move(agent));
    }
}

