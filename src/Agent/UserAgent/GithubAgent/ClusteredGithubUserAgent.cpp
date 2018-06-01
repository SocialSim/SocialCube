#include "ClusteredGithubUserAgent.hpp"

using namespace std;

ClusteredGithubUserAgent::ClusteredGithubUserAgent(const string& t_id, const string& t_cc, const int& t_al) : SimpleGithubUserAgent(t_id, t_cc, t_al), 
    m_communityTag(m_statProxy.getUserCommunityTag(m_id))
{
    return;
}

uint64_t ClusteredGithubUserAgent::getCommunityTag() const {
    return m_communityTag;
}
