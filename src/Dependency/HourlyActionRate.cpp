#include "HourlyActionRate.hpp"

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

    return m_rate[t_eventType].getProb(t_hour);
}

void HourlyActionRate::setHourlyActionRate(const std::string &t_eventType, 
        int t_hour, double t_rate) {
    m_rate[t_eventType].setProb(t_hour, t_rate);
}

uint64_t HourlyActionRate::getActionActivityLevel(const std::string &t_eventType) {
    return m_rate[t_eventType].getActivityLevel();
}
