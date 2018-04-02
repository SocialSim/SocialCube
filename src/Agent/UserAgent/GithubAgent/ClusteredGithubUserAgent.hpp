#ifndef __CLUSTERED_GITHUB_USER__AGENT__
#define __CLUSTERED_GITHUB_USER__AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "SimpleGithubUserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/SimpleBehaviorModel.hpp"
#include "common/Event.hpp"

class ClusteredGithubUserAgent : public SimpleGithubUserAgent {
    protected:

        uint64_t m_communityTag;

    public:
        ClusteredGithubUserAgent(const std::string& t_id);

        virtual ~ClusteredGithubUserAgent() = default;
};

#endif
