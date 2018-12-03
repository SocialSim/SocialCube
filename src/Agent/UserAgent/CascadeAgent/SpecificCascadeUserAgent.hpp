#ifndef __SPECIFIC_CASCADE_USER_AGENT__
#define __SPECIFIC_CASCADE_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/SpecificCascadeModel.hpp"
#include "common/Event.hpp"

class SpecificCascadeUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

    PostScale& m_postScale;

    PostBreadthDistribution& m_postBreadthDistribution;

    std::unordered_map<std::string, double> m_communityDistribution;

public:
    SpecificCascadeUserAgent(const std::string& t_id);

    virtual ~SpecificCascadeUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;

};

#endif
