#include "SeedCascadeSequenceUserAgent.hpp"

using namespace std;

SeedCascadeSequenceUserAgent::SeedCascadeSequenceUserAgent(const string& t_infoId): UserAgent(t_infoId),
                                                                                    m_statProxy(StatisticProxy::getInstance())
{
    return;
}

SeedCascadeSequenceUserAgent::~SeedCascadeSequenceUserAgent() {
    return;
}

vector<unique_ptr<Event>> SeedCascadeSequenceUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> SeedCascadeSequenceUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    vector<unique_ptr<Event>> events = SeedCascadeSequenceModel::evaluate(m_id, m_statProxy.getScoreMatrix(),
                                                                          t_currentTime, t_endTime);

    return events;
}

uint64_t SeedCascadeSequenceUserAgent::getCommunityTag() const {
}

