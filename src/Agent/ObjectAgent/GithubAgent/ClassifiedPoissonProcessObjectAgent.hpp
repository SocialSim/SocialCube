#ifndef __CLASSIFIED_POISSON_PROCESS_OBJECT_AGENT__
#define __CLASSIFIED_POISSON_PROCESS_OBJECT_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PoissonProcessStat.hpp"
#include "BehaviorModel/IntegratedPoissonProcessModel.hpp"
#include "common/Event.hpp"

class ClassifiedPoissonProcessObjectAgent: public ObjectAgent {
private:
    StatisticProxy& m_statProxy;

    PoissonProcessStat& m_stat;

public:
    ClassifiedPoissonProcessObjectAgent(const std::string& t_id);

    ~ClassifiedPoissonProcessObjectAgent() = default;

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif

