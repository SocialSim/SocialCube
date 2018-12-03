#include "SpecificResponseDistribution.hpp"

using namespace std;

SpecificResponseDistribution::SpecificResponseDistribution(std::string t_userID) : m_userID(t_userID) {
    return;
}

SpecificResponseDistribution::~SpecificResponseDistribution() {
    return;
}

void SpecificResponseDistribution::pushResponseDist(string response, double prob) {
    m_response_dists.push_back(std::pair<string, double>(response, prob));
}

vector<pair<string, double>> SpecificResponseDistribution::getResponseDist() {
    return m_response_dists;
};

void SpecificResponseDistribution::show() {
    cout << "userID: " << m_userID << endl;
    for(auto& iter : m_response_dists) {
        cout << iter.first << ", " << iter.second << endl;
    }
    cout << endl;
}
