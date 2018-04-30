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

vector<unique_ptr<Event>> Community::step(time_t t_currentTime, time_t t_unitTime) {
    vector<unique_ptr<Event>> events;
    for(auto& agent : m_community) {
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
		events.insert(
			events.end(),
			std::make_move_iterator(agent_events.begin()),
			std::make_move_iterator(agent_events.end())
		);
    }
    return events;
}
