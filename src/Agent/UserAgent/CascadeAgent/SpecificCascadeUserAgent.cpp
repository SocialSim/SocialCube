#include "SpecificCascadeUserAgent.hpp"

using namespace std;

SpecificCascadeUserAgent::SpecificCascadeUserAgent(const string& t_id) : UserAgent(t_id),
                                                         m_statProxy(StatisticProxy::getInstance()),
                                                         m_postScale(m_statProxy.getPostScale(m_id)),
                                                         m_postBreadthDistribution(m_statProxy.getPostBreadthDistribution(m_id)),
                                                         m_communityDistribution(m_statProxy.getCommunityDistribution(m_id))
{
    assert(&m_postScale != 0);
    return;
}

SpecificCascadeUserAgent::~SpecificCascadeUserAgent() {
    return;
}

vector<unique_ptr<Event>> SpecificCascadeUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> SpecificCascadeUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {

    vector<unique_ptr<Event>> events = SpecificCascadeModel::evaluate(m_id, m_postScale, m_postBreadthDistribution,
                                                              m_communityDistribution, t_currentTime, t_endTime);
    return events;
}

uint64_t SpecificCascadeUserAgent::getCommunityTag() const {
}
