#include "SimpleGithubObjectAgent.hpp"

SimpleGithubObjectAgent::SimpleGithubObjectAgent(string t_id) : m_id(t_id) {
    build();
}

SimpleGithubObjectAgent::~SimpleGithubObjectAgent() {
    return;
}

void SimpleGithubObjectAgent::setStatisticProxy(shared_ptr<StatisticProxy> t_statProxy) {
    m_statProxy = t_statProxy;
}

void SimpleGithubObjectAgent::build() {
    return;
}

vector<Event> SimpleGithubObjectAgent::step(uint64_t t_currentTime, uint64_t t_unitTime);
    vector<Event> events;
    return events;
}
