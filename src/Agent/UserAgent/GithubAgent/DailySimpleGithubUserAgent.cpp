#include "DailySimpleGithubUserAgent.hpp"

using namespace std;

DailySimpleGithubUserAgent::DailySimpleGithubUserAgent(const string& t_id) : UserAgent(t_id),
    m_statProxy(StatisticProxy::getInstance()),
    m_dailyActivityLevel(m_statProxy.getDailyActivityLevel(m_id)),
    m_objectPreference(m_statProxy.getUserObjectPreference(m_id)),
    m_typeDistribution(m_statProxy.getUserTypeDistribution(m_id))
{
    assert(&m_dailyActivityLevel != 0);
    assert(&m_objectPreference != 0);
    assert(&m_typeDistribution != 0);
    return;
}

DailySimpleGithubUserAgent::~DailySimpleGithubUserAgent() {
    return;
}

vector<unique_ptr<Event>> DailySimpleGithubUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> DailySimpleGithubUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {

    vector<unique_ptr<Event>> events = DailySimpleBehaviorModel::evaluate(m_id, m_dailyActivityLevel,
                                                                          m_objectPreference, m_typeDistribution,
                                                                          t_currentTime, t_endTime);

    return events;
}

uint64_t DailySimpleGithubUserAgent::getCommunityTag() const {
}

