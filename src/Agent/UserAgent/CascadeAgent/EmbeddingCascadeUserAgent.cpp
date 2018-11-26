#include "EmbeddingCascadeUserAgent.hpp"

using namespace std;

EmbeddingCascadeUserAgent::EmbeddingCascadeUserAgent(const string& t_id) : UserAgent(t_id),
                                                         m_statProxy(StatisticProxy::getInstance()),
                                                         m_postScale(m_statProxy.getPostScale(m_id)),
                                                         m_postLifespanDistribution(m_statProxy.getPostLifespanDistribution(m_id)),
                                                         m_communityDistribution(m_statProxy.getCommunityDistribution(m_id))
{
    assert(&m_postScale != 0);
    assert(&m_postLifespanDistribution != 0);
//    assert(&m_scoreMatrix != 0);
    return;
}

EmbeddingCascadeUserAgent::~EmbeddingCascadeUserAgent() {
    return;
}

vector<unique_ptr<Event>> EmbeddingCascadeUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> EmbeddingCascadeUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {

    vector<unique_ptr<Event>> events = EmbeddingCascadeModel::evaluate(m_id, m_postScale, m_postLifespanDistribution,
                                                                       m_communityDistribution,
                                                                       m_statProxy.getScoreMatrix(),
                                                                       t_currentTime, t_endTime);
    return events;
}

uint64_t EmbeddingCascadeUserAgent::getCommunityTag() const {
}
