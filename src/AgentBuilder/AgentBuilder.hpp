#ifndef __AGENT_BUILDER__
#define __AGENT_BUILDER__

#include <vector>
#include <memory>
#include "StatisticProxy/StatisticProxy.hpp"

template<class TUserAgent, class TObjectAgent>
class AgentBuilder {

private:
    const StatisticProxy& m_statProxy;

    std::vector<std::unique_ptr<TUserAgent>> m_userAgents; 

    std::vector<std::unique_ptr<TObjectAgent>> m_objectAgents; 

    void buildUsers();

    void buildObjects();

public:

    AgentBuilder();

    ~AgentBuilder();

    void build();

    std::vector<std::unique_ptr<TUserAgent>>& getUserAgentList();

    std::vector<std::unique_ptr<TObjectAgent>>& getObjectAgentList();
};

#include "AgentBuilder.tpp"

#endif
