#include "ClusteredGithubUserAgent.hpp"

using namespace std;

ClusteredGithubUserAgent::ClusteredGithubUserAgent(const string& t_id) : SimpleGithubUserAgent(t_id), 
    m_communityTag(m_statProxy.getUserCommunityTag(m_id))
{
    return;
}

uint64_t ClusteredGithubUserAgent::getCommunityTag() const {
    return m_communityTag;
}
