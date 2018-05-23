#include "IntegratedPointProcessObjectAgent.hpp"

using namespace std;

IntegratedPointProcessObjectAgent::IntegratedPointProcessObjectAgent(const string& t_id) : ObjectAgent(t_id),
                                                                       m_statProxy(StatisticProxy::getInstance()),
                                                                       m_stat(m_statProxy.getPointProcessStats(t_id))
{
    static uint64_t id = 0;
    m_communityTag = id++;
    assert(&m_statProxy != 0);
    assert(&m_stat != 0);
    return;
}

vector<unique_ptr<Event>> IntegratedPointProcessObjectAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> IntegratedPointProcessObjectAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    auto k = m_stat.getK();
    auto mu = m_stat.getMu();
    auto alpha = m_stat.getAlpha();
    auto beta = m_stat.getBeta();
    auto typeList = m_stat.getTypeList();

    vector<unique_ptr<Event>> events = IntegratedPointProcessModel::evaluate(m_id, mu, alpha, beta, typeList, k,
                                                                   t_currentTime, t_endTime);

    return events;
}

uint64_t IntegratedPointProcessObjectAgent::getCommunityTag() const {
}
