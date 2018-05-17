#ifndef __AGENT_BUILDER__
#define __AGENT_BUILDER__

#include <vector>
#include <memory>
#include <iostream>
#include "StatisticProxy/StatisticProxy.hpp"
#include "Log/Log.hpp"

template<class TUserAgent, class TObjectAgent>
class AgentBuilder{

private:
    StatisticProxy& m_statProxy;

    std::vector<std::shared_ptr<TUserAgent>> m_userAgents; 

    std::vector<std::shared_ptr<TObjectAgent>> m_objectAgents; 

    void buildUsers();

    void buildObjects();

public:

    AgentBuilder();

    ~AgentBuilder();

    void build();

    void setFilePath(const std::string fileName, const std::string filePath);

    std::vector<std::shared_ptr<TUserAgent>>& getUserAgentList();

    std::vector<std::shared_ptr<TObjectAgent>>& getObjectAgentList();
};

#include "AgentBuilder.tpp"

#endif
