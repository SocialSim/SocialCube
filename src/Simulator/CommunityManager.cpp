#include "CommunityManager.hpp"

DBG(static const string tag="CommunityManager";)

using namespace std;

void CommunityManager::addAgent(Agent const * t_agent) {
    uint64_t communityTag = t_agent->getCommunityTag();
    if(!communityExist(communityTag))
        m_community[communityTag] = make_unique<Community>(communityTag);
    m_community.at(communityTag)->add(t_agent);
}

void CommunityManager::simulate(vector<vector<float>> temp_pref_data, time_t t_startTime, time_t t_endTime, time_t t_unitTime) {
    DBG(LOGD(TAG, "Total " + stringfy(m_community.size()) + " detected");)
    DBG(LOGD(TAG, "Temp Pref Data size: " + stringfy(temp_pref_data.size()));)

    m_startTime = t_startTime;
    m_endTime = t_endTime;
    m_unitTime = t_unitTime;

    EventManager& em = EventManager::getInstance();

    vector<unique_ptr<Event>> events;

    #ifdef DEBUG
    static size_t finishedCommunityCount = 0;
    static uint64_t communityCnt = m_community.size();
    #endif

    int count = 0;
    for(size_t currentTime = m_startTime; currentTime < m_endTime; currentTime += m_unitTime) {
        for(auto& community: m_community) {
            #ifdef DEBUG
            uint64_t communityTag = community.first;
            #endif

            // DBG(LOGD(TAG, "Simulating community " + stringfy(communityTag) + " (" + stringfy(finishedCommunityCount++) + "/" + stringfy(communityCnt) + ")");)

            vector<unique_ptr<Event>> community_events = community.second->step(temp_pref_data[count], currentTime, m_unitTime);
            em.storeEvent(community_events);
        }
        count++;
        if (count >= temp_pref_data.size()) {
            count = 0;
        }
    }
    // cout << count << endl;
}

void CommunityManager::eventBasedSimulate(time_t t_startTime, time_t t_endTime) {
    DBG(LOGD(TAG, "Total " + stringfy(m_community.size()) + " detected");)

    m_startTime = t_startTime;
    m_endTime = t_endTime;

    EventManager& em = EventManager::getInstance();

    vector<unique_ptr<Event>> events;

    for(auto& community: m_community) {
		vector<unique_ptr<Event>> community_events = community.second->simulate(m_startTime, m_endTime);
		em.storeEvent(community_events);
    }
}

bool CommunityManager::communityExist(uint64_t t_tag) {
    return m_community.find(t_tag) != m_community.end();
}

