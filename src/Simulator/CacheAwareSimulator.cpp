#include "CacheAwareSimulator.hpp"

void CacheAwareSimulator::simulateImpl() {
    m_communityManager->simulate(m_startTime, m_endTime, m_unitTime);
}

