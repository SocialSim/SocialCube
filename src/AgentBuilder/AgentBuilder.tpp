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
    } else if (fileName == "pointProcessProxyFile") {
        m_statProxy.setPointProcessProxyFilePath(filePath);
    } else if (fileName == "poissonProcessProxyFile") {
        m_statProxy.setPoissonProcessProxyFilePath(filePath);
    }
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::build() {
    m_statProxy.startParsing();
    buildUsers();
    buildObjects();
    DBG(LOGD(TAG, "Agent Builder generates "+stringfy(m_userAgents.size())+" user agents");)
    DBG(LOGD(TAG, "Agent Builder generates "+stringfy(m_objectAgents.size())+" object agents");)
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
