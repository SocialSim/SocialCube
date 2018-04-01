#ifndef __CACHE_AWARE_SIMULATOR__
#define __CACHE_AWARE_SIMULATOR__

#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>

#include "Simulator.hpp"
#include "common/Event.hpp"
#include "Agent/UserAgent/UserAgent.hpp"
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "DependentEventLogger/DependentEventLogger.hpp"

using namespace std;

class CacheAwareSimulator : public Simulator {

public:
    virtual void simulateImpl();
};

#endif
