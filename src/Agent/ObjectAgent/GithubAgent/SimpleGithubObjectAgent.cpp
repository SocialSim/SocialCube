#include "SimpleGithubObjectAgent.hpp"

using namespace std;

SimpleGithubObjectAgent::SimpleGithubObjectAgent(const string& t_id) : ObjectAgent(t_id), 
    m_statProxy(StatisticProxy::getInstance())
{
    return;
}

SimpleGithubObjectAgent::~SimpleGithubObjectAgent() {
    return;
}

vector<Event> SimpleGithubObjectAgent::step(uint64_t t_currentTime, uint64_t t_unitTime) {
    vector<Event> events;
    return events;
}
