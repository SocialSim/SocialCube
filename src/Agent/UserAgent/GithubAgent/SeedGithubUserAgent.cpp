#include "SeedGithubUserAgent.hpp"

using namespace std;

SeedGithubUserAgent::SeedGithubUserAgent(const string& t_id): UserAgent(t_id)
{
    return;
}

SeedGithubUserAgent::~SeedGithubUserAgent() {
    return;
}

vector<unique_ptr<Event>> SeedGithubUserAgent::step(time_t t_currentTime, time_t t_unitTime) const {
    throw;
}

vector<unique_ptr<Event>> SeedGithubUserAgent::simulate(time_t t_currentTime, time_t t_endTime) const {
    vector<unique_ptr<Event>> events = SeedHourlySimpleBehaviorModel::evaluate(m_id, t_currentTime, t_endTime);

    return events;
}

uint64_t SeedGithubUserAgent::getCommunityTag() const {
}

