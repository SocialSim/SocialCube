#ifndef __CASCADE_USER_AGENT__
#define __CASCADE_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/DailySimpleBehaviorModel.hpp"
#include "common/Event.hpp"

class CascadeUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

    PostScale& m_postScale;

    CommentProbability& m_commentProbability;

    PostLifespanDistribution& m_postLifespanDistribution;

public:
    CascadeUserAgent(const std::string& t_id);

    virtual ~CascadeUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

};

#endif
