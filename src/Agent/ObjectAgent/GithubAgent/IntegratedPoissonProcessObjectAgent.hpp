#ifndef __INTEGRATED_POISSON_PROCESS_OBJECT_AGENT__
#define __INTEGRATED_POISSON_PROCESS_OBJECT_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PoissonProcessStat.hpp"
#include "BehaviorModel/IntegratedPoissonProcessModel.hpp"
#include "common/Event.hpp"

class IntegratedPoissonProcessObjectAgent: public ObjectAgent {
private:
    const StatisticProxy& m_statProxy;

    PoissonProcessStat& m_stat;

public:
    IntegratedPoissonProcessObjectAgent(const std::string& t_id, const std::string& t_cc, const int& t_al);

    ~IntegratedPoissonProcessObjectAgent() = default;

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif

