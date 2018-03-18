#ifndef __AGENT_BUILDER__
#define __AGENT_BUILDER__

#include <vector>
#include <memory>
#include "StatisticProxy/StatisticProxy.hpp"

template<class TUserAgent, class TObjectAgent>
class AgentBuilder {

private:
    shared_ptr<StatisticProxy> m_statProxy;

    std::vector<shared_ptr<TUserAgent>> m_userAgents; 

    std::vector<shared_ptr<TObjectAgent>> m_objectAgents; 

    void buildUsers();

    void buildObjects();

public:

    AgentBuilder();

    ~AgentBuilder();

    void setStatisticProxy(shared_ptr<StatisticProxy> t_statProxy);

    void build();

    std::vector<shared_ptr<TUserAgent>> getUserAgentList();

    std::vector<shared_ptr<TObjectAgent>> getObjectAgentList();
};

#include "AgentBuilder.tpp"

#endif
