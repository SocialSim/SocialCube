#include "AgentBuilder.hpp"

DBG(static const string tag="AgentBuilder";)

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
    } else if (fileName == "hourlyActionRateFile") {
        m_statProxy.setHourlyActionRateProxyFilePath(filePath);
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
        // cout << "objectID: " << objectID << endl;
        std::shared_ptr<TObjectAgent> agent(new TObjectAgent(objectID));
        m_objectAgents.push_back(move(agent));
    }
}

