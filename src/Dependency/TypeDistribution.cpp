#include "TypeDistribution.hpp"

using namespace std;

const std::unordered_map<std::string, int> TypeDistribution::m_actions{{"CreateEvent", 0}, 
          {"DeleteEvent", 1},
          {"ForkEvent", 2}, 
          {"IssuesEvent", 3}, 
          {"PullRequestEvent", 4}, 
          {"PushEvent", 5}, 
          {"WatchEvent", 6}};

TypeDistribution::TypeDistribution(std::string t_userID) : m_userID(t_userID) {
    return;
}

TypeDistribution::~TypeDistribution() {
    return;
}

void TypeDistribution::pushDist(double t_dist) {
    m_dist.push_back(t_dist);
}

double TypeDistribution::getDist(int t_actionIndex) {
    return m_dist[t_actionIndex];
}


void TypeDistribution::show() {
    cout << "userID" << m_userID << endl;
    for(auto iterm : m_dist)
        cout << iterm << " ";
    cout << endl;
}

size_t TypeDistribution::getActionCount() {
    return m_actions.size();
}
