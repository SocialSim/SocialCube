#include "HourlyActionRate.hpp"

using namespace std;

HourlyActionRate::HourlyActionRate(const std::string &t_userID) :
    m_userID(t_userID) {
    return;
}

HourlyActionRate::~HourlyActionRate() {
    return;
}

double HourlyActionRate::getHourlyActionRate(const std::string &t_eventType, int t_hour) {
    if(m_rate.find(t_eventType) == m_rate.end())
        throw;

    return m_rate[t_eventType]->getProb(t_hour);
}

void HourlyActionRate::setHourlyActionRate(const std::string &t_eventType, 
        int t_hour, double t_rate, uint64_t t_activityLevel) {
    if(m_rate.find(t_eventType) == m_rate.end())
        m_rate[t_eventType] = unique_ptr<EventHourlyActionRate>(new EventHourlyActionRate(t_activityLevel));
    m_rate[t_eventType]->setProb(t_hour, t_rate);
}

uint64_t HourlyActionRate::getActionActivityLevel(const std::string &t_eventType) {
    return m_rate[t_eventType]->getActivityLevel();
}

void HourlyActionRate::show() const {
    assert(m_rate.size() == 14);
    cout << "User " << m_userID << endl;
    cout << "Event Count" << m_rate.size() << endl;
    for(auto& iter : m_rate) {
        cout << "Event Type " << iter.first << endl;
        iter.second->show();
    }
}

unordered_map<string, unique_ptr<EventHourlyActionRate>>&
HourlyActionRate::getRate() {
    return m_rate;
}

string HourlyActionRate::getUserID() const {
    string result = m_userID;
    return result;
}
