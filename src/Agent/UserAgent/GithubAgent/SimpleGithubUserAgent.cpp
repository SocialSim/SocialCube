#include "SimpleGithubUserAgent.hpp"

using namespace std;

SimpleGithubUserAgent::SimpleGithubUserAgent(string t_id) : UserAgent(t_id), 
    m_statProxy(StatisticProxy::getInstance()), 
    m_hourlyActionRate(m_statProxy.getUserHourlyActionRate(m_id)), 
    m_objectPreference(m_statProxy.getUserObjectPreference(m_id))
{
    build();
}

SimpleGithubUserAgent::~SimpleGithubUserAgent() {
    return;
}

vector<Event> SimpleGithubUserAgent::step(uint64_t t_currentTime, uint64_t t_unitTime);
    vector<Event> events = SimpleBehaviorModel::evaluate(m_hourlyActionRate,
                                          m_objectPreference,
                                          m_currentTime, m_unitTime);

    return events;
}
