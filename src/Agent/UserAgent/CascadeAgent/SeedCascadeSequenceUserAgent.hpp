#ifndef __SEED_CASCADE_SEQUENCE_USER_AGENT__
#define __SEED_CASCADE_SEQUENCE_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/SeedCascadeSequenceModel.hpp"
#include "common/Event.hpp"

class SeedCascadeSequenceUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

public:
    SeedCascadeSequenceUserAgent(const std::string& t_infoId);

    virtual ~SeedCascadeSequenceUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif
