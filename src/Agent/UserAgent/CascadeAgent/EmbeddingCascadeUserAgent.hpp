#ifndef __EMBEDDING_CASCADE_USER_AGENT__
#define __EMBEDDING_CASCADE_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/EmbeddingCascadeModel.hpp"
#include "common/Event.hpp"

class EmbeddingCascadeUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

    PostScale& m_postScale;

    PostLifespanDistribution& m_postLifespanDistribution;

//    ScoreMatrix& m_scoreMatrix;

public:
    EmbeddingCascadeUserAgent(const std::string& t_id);

    virtual ~EmbeddingCascadeUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;

};

#endif
