#include "ClassifiedPointProcessObjectAgent.hpp"

using namespace std;

ClassifiedPointProcessObjectAgent::ClassifiedPointProcessObjectAgent(const string& t_id) : ObjectAgent(t_id),
                                                                       m_statProxy(StatisticProxy::getInstance()),
                                                                       m_stat(m_statProxy.getPointProcessStats(t_id))
{
    static uint64_t id = 0;
    m_communityTag = id++;
    assert(&m_statProxy != 0);
    assert(&m_stat != 0);
    return;
}

vector<unique_ptr<Event>> ClassifiedPointProcessObjectAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> ClassifiedPointProcessObjectAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    auto k = m_stat.getK();
    auto mu = m_stat.getMu();
    auto alpha = m_stat.getAlpha();
    auto beta = m_stat.getBeta();
    auto typeList = m_stat.getTypeList();

    vector<unique_ptr<Event>> events;

    for (int i = 0; i < k; ++i) {
        vector<double> tmp_mu({mu[i]});
        vector<vector<double>> tmp_alpha({alpha[i]});

        vector<double> tmp_beta({beta[i]});
        vector<string> tmp_typeList({typeList[i]});
        int tmp_k = 1;
        UserDistribution userDistribution = m_statProxy.getClassifiedUserTypeDistribution(typeList[i], m_id);
        vector<unique_ptr<Event>> tmp_events = IntegratedPointProcessModel::evaluate(m_id, tmp_mu, tmp_alpha, tmp_beta, tmp_typeList, tmp_k, userDistribution,
                                              t_currentTime, t_endTime);

        events.insert(events.end(), make_move_iterator(tmp_events.begin()), make_move_iterator(tmp_events.end()));
    }
    return events;
}

uint64_t ClassifiedPointProcessObjectAgent::getCommunityTag() const {
}
