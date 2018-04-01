#include "CacheAwareSimulator.hpp"

void CacheAwareSimulator::simulateImpl() {
    for(auto& agent : m_userAgents) {
        for(m_currentTime = m_startTime; m_currentTime < m_endTime; m_currentTime += m_unitTime) {
            vector<unique_ptr<Event>> events = agent->step(m_currentTime, m_unitTime);
            logEventInDependentEventLogger(events);
            appendEventInEventHistory(events);
        }
    }
}

