#include "CommunityManager.hpp"

DBG(static const string tag="CommunityManager";)

using namespace std;

void CommunityManager::addAgent(Agent const * t_agent) {
    uint64_t communityTag = t_agent->getCommunityTag();
    if(!communityExist(communityTag)) {
        m_community[communityTag] = make_unique<Community>(communityTag);
        m_communityPendingSimulation[communityTag] = 0;
    }
    m_community.at(communityTag)->add(t_agent);
    m_communityPendingSimulation[communityTag] += 1;
}


vector<uint64_t> CommunityManager::schedule() {

    auto& scheduler = SimpleScheduler::getInstance();
    auto communityToSimulate = scheduler.schedule(m_communityPendingSimulation);
    return communityToSimulate;
}

void CommunityManager::simulate(time_t t_startTime, time_t t_endTime, time_t t_unitTime) {
    DBG(LOGD(TAG, "Total " + stringfy(m_community.size()) + " detected");)

    m_startTime = t_startTime;
    m_endTime = t_endTime;
    m_unitTime = t_unitTime;

    SimulatorWorkerManager& sm = SimulatorWorkerManager::getInstance();

    while(!m_communityPendingSimulation.empty()) {
        auto communityToSimulate = schedule(); 
        Workload workload(m_startTime, m_endTime, m_unitTime);
        for(auto communityID : communityToSimulate) {
            workload.addCommunity(move(m_community[communityID]));
            m_community.erase(communityID);
            m_communityPendingSimulation.erase(communityID);
        }
        sm.scheduleWorkload(workload);
    }
    sm.finishSchedule();
    waitSimulatorWorkerManager();
}

bool CommunityManager::communityExist(uint64_t t_tag) {
    return m_community.find(t_tag) != m_community.end();
}

void CommunityManager::waitSimulatorWorkerManager() {
    SimulatorWorkerManager& sm = SimulatorWorkerManager::getInstance();
    if(!sm.finishSimulation())
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
