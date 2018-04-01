#include "SimulatorProfiler.hpp"

using namespace std;

DBG(static const string tag="SimulatorProfiler";)

void SimulatorProfiler::timeStart() {
    m_chronoStart = chrono::steady_clock::now();
}

void SimulatorProfiler::timeEnd() {
    m_chronoEnd = chrono::steady_clock::now();
    m_duration = m_chronoEnd - m_chronoStart;
}

void SimulatorProfiler::showProfile() {
    DBG(LOGP(TAG, "\n\n*************************** Simulation Profile ***************************", false);)
    DBG(LOGP(TAG, "     Simulation Total Time "+stringfy(m_duration.count())+" s");)
    DBG(LOGP(TAG, "*************************** Simulation Profile ***************************\n\n", false);)

}
