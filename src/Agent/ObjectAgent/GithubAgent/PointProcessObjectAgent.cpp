#include "SimpleGithubObjectAgent.hpp"

using namespace std;

SimpleGithubObjectAgent::SimpleGithubObjectAgent(const string& t_id) : ObjectAgent(t_id), 
    m_statProxy(StatisticProxy::getInstance())
{
    return;
}

vector<unique_ptr<Event>> SimpleGithubObjectAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    vector<unique_ptr<Event>> events;
    return events;
}
