#include "CacheAwareSimulator.hpp"

void CacheAwareSimulator::simulateImpl() {
    m_communityManager->simulate(temp_pref_data, m_startTime, m_endTime, m_unitTime);
}

