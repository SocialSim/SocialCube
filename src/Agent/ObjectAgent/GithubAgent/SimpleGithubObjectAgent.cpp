#include "SimpleGithubObjectAgent.hpp"

using namespace std;

SimpleGithubObjectAgent::SimpleGithubObjectAgent(const string& t_id, const string& t_cc, const int& t_al) : ObjectAgent(t_id, t_cc, t_al), 
    m_statProxy(StatisticProxy::getInstance())
{
    return;
}

SimpleGithubObjectAgent::~SimpleGithubObjectAgent() {
    return;
}

vector<unique_ptr<Event>> SimpleGithubObjectAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    vector<unique_ptr<Event>> events;
    return events;
}

vector<unique_ptr<Event>> SimpleGithubObjectAgent::simulate(vector<float> temp_pref_data, time_t t_currentTime, time_t t_endTime) const {
	throw;
}
