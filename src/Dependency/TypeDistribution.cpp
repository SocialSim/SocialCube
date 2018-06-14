#include "TypeDistribution.hpp"

using namespace std;

const std::unordered_map<int, std::string> TypeDistribution::m_actions{
    {0, "IssuesEvent"},
    {1, "PullRequestReviewCommentEvent"},
    {2, "PushEvent"},
    {3, "PullRequestEvent"},
    {4, "IssueCommentEvent"},
    {5, "CreateEvent"},
    {6, "WatchEvent"},
    {7, "ForkEvent"},
    {8, "DeleteEvent"},
    {9, "CommitCommentEvent"}};

/*
const std::unordered_map<int, std::string> TypeDistribution::m_actions{
    {0, "CreateEvent"}, 
    {1, "DeleteEvent"},
    {2, "ForkEvent", }, 
    {3, "IssuesEvent"}, 
    {4, "PullRequestE"}, 
    {5, "PushEvent", }, 
    {6, "WatchEvent",}};
*/

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

string TypeDistribution::randomChooseAction() const {
    double d = ((double)rand()) / RAND_MAX;
    double sum = 0.0;
    string action;
    for(size_t action_index = 0; action_index < m_dist.size(); ++action_index){
        sum += m_dist[action_index];
        if(sum > d) {
            action = TypeDistribution::m_actions.find(action_index)->second;
            break;
        }
    }
    return action;
}