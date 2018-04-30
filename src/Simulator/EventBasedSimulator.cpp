#include "EventBasedSimulator.hpp"

using namespace std;

DBG(static const string tag="EventBasedSimulator";)

void EventBasedSimulator::addObjectAgent(Agent const * t_agent) {
    throw;
}

void EventBasedSimulator::simulateImpl() {
    m_communityManager->eventBasedSimulate(m_startTime, m_endTime);
}

void EventBasedSimulator::printConfig() {
    DBG(LOGP(TAG, "\n\n*************************** Event Based Simulator Configuration ***************************", false);)
    DBG(LOGP(TAG, "Simulation Start Time: "+stringfy(m_startTime));)
    DBG(LOGP(TAG, "Simulation End Time: "+stringfy(m_endTime));)
    DBG(LOGP(TAG, "Simulation Unit Time: "+stringfy(m_unitTime));)
    DBG(LOGP(TAG, "*************************** Event Based Simulator Configuration ***************************\n\n", false);)
}
