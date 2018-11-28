#include "SeedCascadeUserAgent.hpp"

using namespace std;

SeedCascadeUserAgent::SeedCascadeUserAgent(const string& t_id) : UserAgent(t_id),
                                                         m_statProxy(StatisticProxy::getInstance()),
                                                         m_postScale(m_statProxy.getPostScale(m_id)),
                                                         m_postLifespanDistribution(m_statProxy.getPostLifespanDistribution(m_id)),
                                                         m_communityDistribution(m_statProxy.getCommunityDistribution(m_id))
{
    assert(&m_postScale != 0);
    assert(&m_postLifespanDistribution != 0);
    return;
}

SeedCascadeUserAgent::~SeedCascadeUserAgent() {
    return;
}

vector<unique_ptr<Event>> SeedCascadeUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> SeedCascadeUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {

    vector<unique_ptr<Event>> events = SeedCascadeModel::evaluate(m_id, m_postScale, m_postLifespanDistribution,
                                                              m_communityDistribution, t_currentTime, t_endTime);
    return events;
}

uint64_t SeedCascadeUserAgent::getCommunityTag() const {
}
