#include "Community.hpp"

using namespace std;

Community::Community(uint64_t t_communityTag) : m_communityTag(t_communityTag) {
    return;
}

size_t Community::size() {
    return m_community.size();
}

uint64_t Community::getCommunityTag() {
    return m_communityTag;
}

void Community::add(Agent const * t_agent) {
    m_community.push_back(move(t_agent));
}

vector<unique_ptr<Event>> Community::step(vector<string> cc_list, vector<float> temp_pref_data, time_t t_currentTime, time_t t_unitTime) {
    vector<unique_ptr<Event>> events;

    EventManager& em = EventManager::getInstance();

    for(auto& agent : m_community) {
        // Uses Temporal Preferences of Users
        string user_cc = agent->getCC();
        ptrdiff_t pos = distance(cc_list.begin(), find(cc_list.begin(), cc_list.end(), user_cc));
        if (pos < cc_list.size()) {
            if (agent->getAL() > temp_pref_data[pos]) {
                continue;
            }
        }

        vector<unique_ptr<Event>> agent_events = agent->step(t_currentTime, t_unitTime);

        em.storeEvent(agent_events);

        // events.insert(
        //     events.end(),
        //     std::make_move_iterator(agent_events.begin()),
        //     std::make_move_iterator(agent_events.end())
        // );
    }
    return events;
}


std::vector<std::unique_ptr<Event>> Community::simulate(vector<string> cc_list, vector<vector<float>> temp_pref_data, time_t t_startTime, time_t t_endTime) {
	time_t currentTime = t_startTime;
	time_t endTime = t_endTime;

    EventManager& em = EventManager::getInstance();

    vector<unique_ptr<Event>> events;

    for(auto& agent : m_community) {
        string user_cc = agent->getCC();
        ptrdiff_t pos = distance(cc_list.begin(), find(cc_list.begin(), cc_list.end(), user_cc));

        vector<float> agent_temp_pref;
        for (int i = 0; i < temp_pref_data.size(); i++) {
            agent_temp_pref.push_back(temp_pref_data[i][pos]);
        }

		vector<unique_ptr<Event>> agent_events = agent->simulate(agent_temp_pref, currentTime, endTime);

        em.storeEvent(agent_events);

		// events.insert(
		// 	events.end(),
		// 	std::make_move_iterator(agent_events.begin()),
		// 	std::make_move_iterator(agent_events.end())
		// );
    }
    return events;
}
