#include "CascadeUserAgent.hpp"

using namespace std;

CascadeUserAgent::CascadeUserAgent(const string& t_id) : UserAgent(t_id),
                                                         m_statProxy(StatisticProxy::getInstance()),
                                                         m_postScale(m_statProxy.getPostScale(m_id)),
                                                         m_commentProbability(m_statProxy.getCommentProbability(m_id)),
                                                         m_postLifespanDistribution(m_statProxy.getPostLifespanDistribution(m_id))
{
    assert(&m_postScale != 0);
    assert(&m_commentProbability != 0);
    assert(&m_postLifespanDistribution != 0);
    return;
}

CascadeUserAgent::~CascadeUserAgent() {
    return;
}

vector<unique_ptr<Event>> CascadeUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> CascadeUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    cout << "CascadeUserAgent simulate" << endl;
    vector<unique_ptr<Event>> events;

    return events;
}

