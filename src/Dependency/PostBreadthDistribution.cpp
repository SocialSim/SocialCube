#include "PostBreadthDistribution.hpp"

using namespace std;

PostBreadthDistribution::PostBreadthDistribution(std::string t_userID) : m_userID(t_userID) {
    return;
}

PostBreadthDistribution::~PostBreadthDistribution() {
    return;
}

void PostBreadthDistribution::pushBreadthDist(int breadth, double prob) {
    m_breadth_dists.push_back(std::pair<int, double>(breadth, prob));
}

std::vector<std::pair<int, double>> PostBreadthDistribution::getBreadthDist() {
    return m_breadth_dists;
};

void PostBreadthDistribution::show() {
    cout << "userID: " << m_userID << endl;
    for(auto& iter : m_breadth_dists) {
        cout << iter.first << ", " << iter.second << endl;
    }
    cout << endl;
}
