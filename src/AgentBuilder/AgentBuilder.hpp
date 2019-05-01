#ifndef __AGENT_BUILDER__
#define __AGENT_BUILDER__

#include <vector>
#include <memory>
#include <iostream>
#include "StatisticProxy/StatisticProxy.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/UserAgent/GithubAgent/DailySimpleGithubUserAgent.hpp"
#include "Agent/UserAgent/CascadeAgent/CascadeUserAgent.hpp"
#include "Agent/UserAgent/CascadeAgent/SeedCascadeUserAgent.hpp"
#include "Agent/UserAgent/CascadeAgent/EmbeddingCascadeUserAgent.hpp"
#include "Agent/UserAgent/CascadeAgent/SeedEmbeddingCascadeUserAgent.hpp"
#include "Agent/UserAgent/GithubAgent/SeedGithubUserAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/IntegratedPointProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/IntegratedPoissonProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/PointProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/PoissonProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/ClassifiedPointProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/ClassifiedPoissonProcessObjectAgent.hpp"
#include "Log/Log.hpp"

template<class TUserAgent, class TObjectAgent>
class AgentBuilder{

private:
    StatisticProxy& m_statProxy;

    std::vector<std::shared_ptr<TUserAgent>> m_userAgents; 

    std::vector<std::shared_ptr<TObjectAgent>> m_objectAgents; 

    void buildUsers();

    void buildObjects();

    void buildInfoIDUsers();

public:

    AgentBuilder(const std::string &default_file_path);

    ~AgentBuilder();

    void build();

    void setFilePath(const std::string fileName, const std::string filePath);

    std::vector<std::shared_ptr<TUserAgent>>& getUserAgentList();

    std::vector<std::shared_ptr<TObjectAgent>>& getObjectAgentList();
};

#include "AgentBuilder.tpp"

#endif
