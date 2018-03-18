#include "AgentBuilder.hpp"

template<class TUserAgent, class TObjectAgent>
AgentBuilder<TUserAgent, TObjectAgent>::AgentBuilder() : m_statProxy(nullptr) {
    return;
}

template<class TUserAgent, class TObjectAgent>
AgentBuilder<TUserAgent, TObjectAgent>::~AgentBuilder() {
    return;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::setStatisticProxy(shared_ptr<StatisticProxy> t_statProxy) {
    m_statProxy = t_statProxy;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::build() {
    buildUsers();
    buildObjects();
}

template<class TUserAgent, class TObjectAgent>
std::vector<shared_ptr<TUserAgent>> AgentBuilder<TUserAgent, TObjectAgent>::getUserAgentList() {
    return m_userAgents;
}

template<class TUserAgent, class TObjectAgent>
std::vector<shared_ptr<TObjectAgent>> AgentBuilder<TUserAgent, TObjectAgent>::getObjectAgentList() {
    return m_objectAgents;
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildUsers() {
    std::vector<string> userIDs = m_statProxy->getUserIDs();
    for(auto userID : userIDs) {
        shared_ptr<TUserAgent> agent(new TUserAgent(userID));
        m_userAgents.push_back(agent);
    }
}

template<class TUserAgent, class TObjectAgent>
void AgentBuilder<TUserAgent, TObjectAgent>::buildObjects() {
    std::vector<string> objectIDs = m_statProxy->getObjectIDs();
    for(auto objectID : objectIDs) {
        shared_ptr<TObjectAgent> agent(new TObjectAgent(objectID));
        m_objectAgents.push_back(agent);
    }
}
