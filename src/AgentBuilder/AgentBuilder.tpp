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
void AgentBuilder<TUserAgent, TObjectAgent>::build() {
    buildUsers();
    buildObjects();
}

template<class TUserAgent, class TObjectAgent>
std::vector<std::unique_ptr<TUserAgent>>& AgentBuilder<TUserAgent, TObjectAgent>::getUserAgentList() {
    return m_userAgents;
}

template<class TUserAgent, class TObjectAgent>
std::vector<std::unique_ptr<TObjectAgent>>& AgentBuilder<TUserAgent, TObjectAgent>::getObjectAgentList() {
    return m_objectAgents;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildUsers() {
    const std::vector<std::string>& userIDs = m_statProxy.getUserIDs();
    for(auto& userID : userIDs) {
        std::unique_ptr<TUserAgent> agent(new TUserAgent(userID));
        m_userAgents.push_back(move(agent));
    }
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildObjects() {
    const std::vector<std::string>& objectIDs = m_statProxy.getObjectIDs();
    for(auto& objectID : objectIDs) {
        std::unique_ptr<TObjectAgent> agent(new TObjectAgent(objectID));
        m_objectAgents.push_back(move(agent));
    }
}
