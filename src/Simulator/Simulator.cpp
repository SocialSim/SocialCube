#include "Simulator.hpp"

using namespace std;

DBG(static const string tag="Simulator";)

Simulator::Simulator() : m_communityManager(new CommunityManager),
    m_startTime(0), m_endTime(0), m_unitTime(1) {

    srand(time(NULL));

    return;
}

Simulator::~Simulator() {
    return;
}

void Simulator::setStartTime(time_t t_currentTime) {
    m_startTime = t_currentTime;
}

void Simulator::setEndTime(time_t t_endTime) {
    m_endTime = t_endTime;
}

void Simulator::setUnitTime(time_t t_unitTime) {
    m_unitTime = t_unitTime;
}

void Simulator::addUserAgent(Agent const * t_agent) {
    m_communityManager->addAgent(t_agent);
}

void Simulator::addObjectAgent(Agent const * t_agent) {
    throw;
}

void Simulator::simulate() {
    preSimulationConfig();

    simulateImpl();

    postSimulationConfig();
}

void Simulator::simulateImpl() {
    m_communityManager->simulate(m_startTime, m_endTime, m_unitTime);
}

void Simulator::preSimulationConfig() {
	printConfig();

    if(m_endTime < m_startTime) {
        EndTimeLessThanStartTime e_e;
        throw e_e;
    }

    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    EventManager& em = EventManager::getInstance();

    em.start();
    sp.timeStart();
}

void Simulator::postSimulationConfig() {
    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    EventManager& em = EventManager::getInstance();

    sp.timeEnd();
    em.end();
}

void Simulator::printConfig() {
    DBG(LOGP(TAG, "\n\n*************************** Simulator Configuration ***************************", false);)
    DBG(LOGP(TAG, "Simulation Start Time: "+stringfy(m_startTime));)
    DBG(LOGP(TAG, "Simulation End Time: "+stringfy(m_endTime));)
    DBG(LOGP(TAG, "Simulation Unit Time: "+stringfy(m_unitTime));)
    DBG(LOGP(TAG, "*************************** Simulator Configuration ***************************\n\n", false);)
}
