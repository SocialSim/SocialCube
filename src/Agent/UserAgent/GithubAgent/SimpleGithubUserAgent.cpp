#include "SimpleGithubUserAgent.hpp"

using namespace std;

SimpleGithubUserAgent::SimpleGithubUserAgent(const string& t_id) : UserAgent(t_id), 
    m_statProxy(StatisticProxy::getInstance()),
    m_hourlyActionRate(m_statProxy.getUserHourlyActionRate(m_id)), 
    m_objectPreference(m_statProxy.getUserObjectPreference(m_id))
{
    assert(&m_hourlyActionRate != 0);
    assert(&m_objectPreference != 0);
    assert(&m_hourlyActionRate != 0);
    return;
}

SimpleGithubUserAgent::~SimpleGithubUserAgent() {
    return;
}

vector<unique_ptr<Event>> SimpleGithubUserAgent::step(uint64_t t_currentTime, uint64_t t_unitTime) {
    vector<unique_ptr<Event>> events = SimpleBehaviorModel::evaluate(m_hourlyActionRate,
                                          m_objectPreference,
                                          t_currentTime, t_unitTime);

    return events;
}
