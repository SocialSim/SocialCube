#include "SimulatorProfiler.hpp"

using namespace std;

DBG(static const string tag="SimulatorProfiler";)

SimulatorProfiler& SimulatorProfiler::getInstance() {
    static SimulatorProfiler instance;
    return instance;
}

SimulatorProfiler::SimulatorProfiler() : m_eventCount(0), m_profileOn(false) {
    return;
}

SimulatorProfiler::~SimulatorProfiler() {
    if(m_profileOn) {
        showProfile(); 
    }
}

void SimulatorProfiler::timeStart() {
    m_chronoStart = chrono::steady_clock::now();
}

void SimulatorProfiler::timeEnd() {
    m_chronoEnd = chrono::steady_clock::now();
    m_duration = m_chronoEnd - m_chronoStart;
}

void SimulatorProfiler::showProfile() {
    DBG(LOGP(TAG, "\n\n*************************** Simulation Profile ***************************", false);)
    DBG(LOGP(TAG, "Simulation Total Time "+stringfy(m_duration.count())+" s");)
    DBG(LOGP(TAG, "Simulation Total Events "+stringfy(m_eventCount));)
    DBG(LOGP(TAG, "*************************** Simulation Profile ***************************\n\n", false);)

    if(m_eventCount == 0) {
        DBG(LOGW(TAG, "     Simulation Total Events Count is 0!");)
    }
}

void SimulatorProfiler::setEventCount(uint64_t t_cnt) {
    DBG(LOGP(TAG, "Set Event Count " + stringfy(t_cnt));)
    m_eventCount = t_cnt;
}

void SimulatorProfiler::setProfileShow(bool t_profileOn) {
    m_profileOn = t_profileOn;
}
