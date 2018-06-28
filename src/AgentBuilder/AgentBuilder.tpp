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
        m_statProxy.setUserDistributionProxyFilePath(filePath);
    }
    // 10 event type user distribution proxy files
    else if (fileName == "commitCommentEventUserDistributionProxyFile") {
        m_statProxy.setCommitCommentEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "deleteEventUserDistributionProxyFile") {
        m_statProxy.setDeleteEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "issueCommentEventUserDistributionProxyFile") {
        m_statProxy.setIssueCommentEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "pullRequestEventUserDistributionProxyFile") {
        m_statProxy.setPullRequestEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "pushEventUserDistributionProxyFile") {
        m_statProxy.setPushEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "createEventUserDistributionProxyFile") {
        m_statProxy.setCreateEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "forkEventUserDistributionProxyFile") {
        m_statProxy.setForkEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "issueEventUserDistributionProxyFile") {
        m_statProxy.setIssueEventUserDistributionProxyFilePath(filePath);
    } else if (fileName == "pullRequestReviewCommentEventUserDistributionProxyFile") {
        m_statProxy.setPullRequestReviewCommentEventUserDistributionProxyFile(filePath);
    } else if (fileName == "watchEventUserDistributionProxyFile") {
        m_statProxy.setWatchEventUserDistributionProxyFile(filePath);
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
    // ClassifiedPointProcess model
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, ClassifiedPointProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parsePointProcessStats();
        m_statProxy.parseClassifiedUserDistributionStats();
        buildObjects();
    }
    // PoissonProcess model
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, PoissonProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parsePoissonProcessStats();
        buildObjects();
    }
    // ClassifiedPoissonProcess model
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, ClassifiedPoissonProcessObjectAgent>::value) {
        m_statProxy.parseObjectID();
        m_statProxy.parsePoissonProcessStats();
        m_statProxy.parseClassifiedUserDistributionStats();
        buildObjects();
    }
    // SimpleBehavior model (user centric)
    else if (std::is_same<TUserAgent, SimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, SimpleGithubObjectAgent>::value) {
        m_statProxy.parseUserID();
        m_statProxy.parseHourlyActionRate();
        m_statProxy.parseObjectPreference();
        m_statProxy.parseTypeDistribution();
        buildUsers();
    }
    // DailySimpleBehavior model
    else if (std::is_same<TUserAgent, DailySimpleGithubUserAgent>::value && \
    std::is_same<TObjectAgent, SimpleGithubObjectAgent>::value) {
        m_statProxy.parseUserID();
        m_statProxy.parseDailyActivityLevel();
        m_statProxy.parseObjectPreference();
        m_statProxy.parseTypeDistribution();
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
    m_statProxy.initProxySourceFile();
}

template<class TUserAgent, class TObjectAgent>
std::vector<std::shared_ptr<TUserAgent>>& AgentBuilder<TUserAgent, TObjectAgent>::getUserAgentList() {
    return m_userAgents;
}

template<class TUserAgent, class TObjectAgent>
std::vector<std::shared_ptr<TObjectAgent>>& AgentBuilder<TUserAgent, TObjectAgent>::getObjectAgentList() {
    return m_objectAgents;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildUsers() {
    const std::vector<std::string>& userIDs = m_statProxy.getUserIDs();

    for(auto& userID : userIDs) {
        std::shared_ptr<TUserAgent> agent(new TUserAgent(userID));
        m_userAgents.push_back(move(agent));
    }
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildObjects() {
    const std::vector<std::string>& objectIDs = m_statProxy.getObjectIDs();
    for(auto& objectID : objectIDs) {
        std::shared_ptr<TObjectAgent> agent(new TObjectAgent(objectID));
        m_objectAgents.push_back(move(agent));
    }
}

