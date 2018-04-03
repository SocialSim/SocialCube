#include "CommunityManager.hpp"

DBG(static const string tag="CommunityManager";)

using namespace std;

void CommunityManager::addAgent(Agent const * t_agent) {
    uint64_t communityTag = t_agent->getCommunityTag();
    if(!communityExist(communityTag))
        m_community[communityTag] = make_unique<Community>(communityTag);
    m_community.at(communityTag)->add(t_agent);
}

void CommunityManager::simulate(time_t t_startTime, time_t t_endTime, time_t t_unitTime) {
    DBG(LOGD(TAG, "Total " + stringfy(m_community.size()) + " detected");)

    m_startTime = t_startTime;
    m_endTime = t_endTime;
    m_unitTime = t_unitTime;

    EventManager& em = EventManager::getInstance();

    vector<unique_ptr<Event>> events;

    #ifdef DEBUG
    static size_t finishedCommunityCount = 0;
    static uint64_t communityCnt = m_community.size();
    #endif

    for(auto& community: m_community) {
        #ifdef DEBUG
        uint64_t communityTag = community.first;
        #endif

        DBG(LOGD(TAG, "Simulating community " + stringfy(communityTag) + " (" + stringfy(finishedCommunityCount++) + "/" + stringfy(communityCnt) + ")");)
        for(size_t currentTime = m_startTime; currentTime < m_endTime; currentTime += m_unitTime) {
            vector<unique_ptr<Event>> community_events = community.second->step(currentTime, m_unitTime);
            em.storeEvent(community_events);
        }
    }
}

bool CommunityManager::communityExist(uint64_t t_tag) {
    return m_community.find(t_tag) != m_community.end();
}

