#ifndef __EVENT_BASED_SIMULATOR__
#define __EVENT_BASED_SIMULATOR__

#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>
#include <fstream>
#include "Simulator.hpp"

class EventBasedSimulator : public Simulator {

protected:

    virtual void simulateImpl() override;

    virtual void printConfig() override;

public:

    EventBasedSimulator() = default;

    virtual ~EventBasedSimulator() = default;

    virtual void addObjectAgent(Agent const * t_agent) override;
};

#endif
