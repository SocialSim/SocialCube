#include "SeedEmbeddingCascadeUserAgent.hpp"

using namespace std;

SeedEmbeddingCascadeUserAgent::SeedEmbeddingCascadeUserAgent(const string& t_id) : UserAgent(t_id),
                                                         m_statProxy(StatisticProxy::getInstance()),
                                                         m_postScale(m_statProxy.getPostScale(m_id)),
                                                         m_postLifespanDistribution(m_statProxy.getPostLifespanDistribution(m_id)),
                                                         m_communityDistribution(m_statProxy.getCommunityDistribution(m_id))
{
    assert(&m_postScale != 0);
    assert(&m_postLifespanDistribution != 0);
    return;
}

SeedEmbeddingCascadeUserAgent::~SeedEmbeddingCascadeUserAgent() {
    return;
}

vector<unique_ptr<Event>> SeedEmbeddingCascadeUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> SeedEmbeddingCascadeUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {

    vector<unique_ptr<Event>> events = SeedEmbeddingCascadeModel::evaluate(m_id, m_postScale, m_postLifespanDistribution,
                                                                  m_communityDistribution,
                                                                  m_statProxy.getScoreMatrix(),
                                                                  t_currentTime, t_endTime);
    return events;
}

uint64_t SeedEmbeddingCascadeUserAgent::getCommunityTag() const {
}
