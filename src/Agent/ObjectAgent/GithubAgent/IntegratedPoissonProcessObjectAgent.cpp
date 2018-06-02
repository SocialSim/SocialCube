#include "IntegratedPoissonProcessObjectAgent.hpp"

using namespace std;

IntegratedPoissonProcessObjectAgent::IntegratedPoissonProcessObjectAgent(const string& t_id, const string& t_cc, const int& t_al) : ObjectAgent(t_id, t_cc, t_al),
                                                                                           m_statProxy(StatisticProxy::getInstance()),
                                                                                           m_stat(m_statProxy.getPoissonProcessStats(t_id))
{
    static uint64_t id = 0;
    m_communityTag = id++;
    assert(&m_statProxy != 0);
    assert(&m_stat != 0);
    return;
}

vector<unique_ptr<Event>> IntegratedPoissonProcessObjectAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> IntegratedPoissonProcessObjectAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    auto k = m_stat.getK();
    auto mu = m_stat.getMu();
    auto typeList = m_stat.getTypeList();

    vector<unique_ptr<Event>> events = IntegratedPoissonProcessModel::evaluate(m_id, mu, typeList, k,
                                                                               t_currentTime, t_endTime);

    return events;
}

uint64_t IntegratedPoissonProcessObjectAgent::getCommunityTag() const {
}
