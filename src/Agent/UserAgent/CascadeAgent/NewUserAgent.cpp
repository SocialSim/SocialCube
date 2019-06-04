#include "NewUserAgent.hpp"

using namespace std;

NewUserAgent::NewUserAgent(const string& t_id) : UserAgent(t_id),
                                                                 m_statProxy(StatisticProxy::getInstance())
{
    return;
}

NewUserAgent::~NewUserAgent() {
    return;
}

vector<unique_ptr<Event>> NewUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> NewUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    vector<unique_ptr<Event>> events = NewUserModel::evaluate(m_id, t_currentTime, t_endTime);
    return events;
}

uint64_t NewUserAgent::getCommunityTag() const {
}
