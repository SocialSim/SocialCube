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

vector<unique_ptr<Event>> SimpleGithubObjectAgent::step(uint64_t t_currentTime, uint64_t t_unitTime) {
    vector<unique_ptr<Event>> events;
    return events;
}
