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

// temp_pref_data = {us_frac, cn_frac, in_frac}
vector<unique_ptr<Event>> Community::step(vector<float> temp_pref_data, time_t t_currentTime, time_t t_unitTime) {
    vector<unique_ptr<Event>> events;
        
    for(auto& agent : m_community) {
        // Uses Temporal Preferences of Users
        if (agent->getCC() == "us") {
            if (agent->getAL() > temp_pref_data[0]) {
                continue;
            }
        } else if (agent->getCC() == "cn") {
            if (agent->getAL() > temp_pref_data[1]) {
                continue;
            }
        } else {
            if (agent->getAL() > temp_pref_data[2]) {
                continue;
            }
        }

        vector<unique_ptr<Event>> agent_events = agent->step(t_currentTime, t_unitTime);
        events.insert(
            events.end(),
            std::make_move_iterator(agent_events.begin()),
            std::make_move_iterator(agent_events.end())
        );
    }
    return events;
}


std::vector<std::unique_ptr<Event>> Community::simulate(time_t t_startTime, time_t t_endTime) {
	time_t currentTime = t_startTime;
	time_t endTime = t_endTime;

    vector<unique_ptr<Event>> events;

    for(auto& agent : m_community) {
		vector<unique_ptr<Event>> agent_events = agent->simulate(currentTime, endTime);
		// cout << "Finish simulating " << agent->getID() << endl;
		events.insert(
			events.end(),
			std::make_move_iterator(agent_events.begin()),
			std::make_move_iterator(agent_events.end())
		);
    }
    return events;
}
