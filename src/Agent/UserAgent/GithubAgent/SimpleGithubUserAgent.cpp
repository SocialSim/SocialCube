#include "SimpleGithubUserAgent.hpp"

SimpleGithubUserAgent::SimpleGithubUserAgent(string t_id) : m_id(t_id) {
    build();
}

SimpleGithubUserAgent::~SimpleGithubUserAgent() {
    return;
}

void SimpleGithubUserAgent::setStatisticProxy(shared_ptr<StatisticProxy> t_statProxy) {
    m_statProxy = t_statProxy;
}

void SimpleGithubUserAgent::build() {
    m_hourlyActionRate = m_statProxy->getUserHourlyActionRate(m_id);
    m_objectPreference = m_statProxy->getUserObjectPreference(m_id);
}

vector<Event> SimpleGithubUserAgent::step(uint64_t t_currentTime, uint64_t t_unitTime);
    vector<Event> events = SimpleBehaviorModel::evaluate(m_hourlyActionRate,
                                          m_objectPreference,
                                          m_currentTime, m_unitTime);

    return events;
}
