#include "ParrotGithubUserAgent.hpp"

using namespace std;

ParrotGithubUserAgent::ParrotGithubUserAgent(const string& t_id, const string& t_cc, const int& t_al) : UserAgent(t_id, t_cc, t_al),
    m_statProxy(StatisticProxy::getInstance()),
    m_dailyActivityLevel(m_statProxy.getDailyActivityLevel(m_id)),
    m_objectPreference(m_statProxy.getUserObjectPreference(m_id)),
    m_typeDistribution(m_statProxy.getUserTypeDistribution(m_id)),
    m_weeklyEventCount(m_statProxy.getWeeklyEventCount(m_id))
{
    // cout << "user id: " << t_id << endl;
    assert(&m_dailyActivityLevel != 0);
    assert(&m_objectPreference != 0);
    assert(&m_typeDistribution != 0);
    return;
}

ParrotGithubUserAgent::~ParrotGithubUserAgent() {
    return;
}

vector<unique_ptr<Event>> ParrotGithubUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> ParrotGithubUserAgent::simulate(vector<float> temp_pref_data, time_t t_currentTime, time_t t_endTime) const {

    vector<unique_ptr<Event>> events = WeeklyEventCountBehaviorModel::evaluate(m_id, m_cc, m_al, temp_pref_data, m_dailyActivityLevel,
                                                                          m_weeklyEventCount, m_objectPreference, m_typeDistribution,
                                                                          t_currentTime, t_endTime);

    return events;
}

uint64_t ParrotGithubUserAgent::getCommunityTag() const {
}

