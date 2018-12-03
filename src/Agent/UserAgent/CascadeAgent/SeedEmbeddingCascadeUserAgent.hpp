#ifndef __SEED_EMBEDDING_CASCADE_USER_AGENT__
#define __SEED_EMBEDDING_CASCADE_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/SeedEmbeddingCascadeModel.hpp"
#include "common/Event.hpp"

class SeedEmbeddingCascadeUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

    PostScale& m_postScale;

    PostLifespanDistribution& m_postLifespanDistribution;

    std::unordered_map<std::string, double> m_communityDistribution;

public:
    SeedEmbeddingCascadeUserAgent(const std::string& t_id);

    virtual ~SeedEmbeddingCascadeUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;

};

#endif
