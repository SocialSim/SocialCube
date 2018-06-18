#include "DailyActivityLevel.hpp"

using namespace std;

DailyActivityLevel::DailyActivityLevel(const std::string &t_userID) :
        m_activityLevels(),
        m_userID(t_userID) {
    return;
}

DailyActivityLevel::~DailyActivityLevel() {
    return;
}

double DailyActivityLevel::getActivityLevel(int t_day) {
    return m_activityLevels[t_day];
}

int DailyActivityLevel::getActivityLevelSize() {
    return m_activityLevels.size();
}


void DailyActivityLevel::addActivityLevel(double t_activityLevel) {
    m_activityLevels.push_back(t_activityLevel);
}

void DailyActivityLevel::show() const {
    cout << "User " << m_userID << endl;
    for (int i = 0; i < m_activityLevels.size(); i++) {
        cout << "day: " << i << ", " << m_activityLevels[i] << endl;
    }
}

string DailyActivityLevel::getUserID() const {
    string result = m_userID;
    return result;
}
