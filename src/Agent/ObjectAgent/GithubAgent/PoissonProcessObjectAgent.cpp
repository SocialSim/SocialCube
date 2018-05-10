#include "PoissonProcessObjectAgent.hpp"

using namespace std;

PoissonProcessObjectAgent::PoissonProcessObjectAgent(const string& t_id) : ObjectAgent(t_id),
                                                                       m_statProxy(StatisticProxy::getInstance()),
                                                                       m_stat(m_statProxy.getPoissonProcessStat(t_id))
{
    static uint64_t id = 0;
    m_communityTag = id++;
    assert(&m_statProxy != 0);
    assert(&m_stat != 0);
    return;
}

vector<unique_ptr<Event>> PoissonProcessObjectAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> PoissonProcessObjectAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    auto mu = m_stat.getMu();
    auto type = m_stat.getType();

    vector<unique_ptr<Event>> events = PoissonProcessModel::evaluate(m_id, mu, type, t_currentTime, t_endTime);

    return events;
}

uint64_t PoissonProcessObjectAgent::getCommunityTag() const {
}
