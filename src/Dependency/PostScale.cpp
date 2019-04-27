#include "PostScale.hpp"

using namespace std;

PostScale::PostScale(std::string t_userID) : m_userID(t_userID) {
    return;
}

PostScale::~PostScale() {
    return;
}

void PostScale::pushScale(double t_number, double t_scale) {
    m_scales.push_back(std::pair<double, double>(t_number, t_scale));
}

std::vector<std::pair<double, double>> PostScale::getScale() {
    return m_scales;
}

void PostScale::show() {
    cout << "userID: " << m_userID << endl;
    for(auto& iter : m_scales) {
        cout << iter.first << ", " << iter.second << endl;
    }
}