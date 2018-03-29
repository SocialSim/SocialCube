#include "HourlyActionRate.hpp"

using namespace std;

HourlyActionRate::HourlyActionRate(const std::string &t_userID) :
    m_rate(nullptr),
    m_userID(t_userID) {
    return;
}

HourlyActionRate::~HourlyActionRate() {
    return;
}

double HourlyActionRate::getHourlyActionRate(int t_hour) {
    return m_rate->getProb(t_hour);
}

void HourlyActionRate::setHourlyActionRate(int t_hour, double t_rate, double t_activityLevel) {
    if(m_rate.get() == nullptr)
        m_rate = unique_ptr<EventHourlyActionRate>(new EventHourlyActionRate(t_activityLevel));
    m_rate->setProb(t_hour, t_rate);
}

double HourlyActionRate::getActionActivityLevel() {
    return m_rate->getActivityLevel();
}

void HourlyActionRate::show() const {
    cout << "User " << m_userID << endl;
    m_rate->show();
}

unique_ptr<EventHourlyActionRate>&
HourlyActionRate::getRate() {
    return m_rate;
}

string HourlyActionRate::getUserID() const {
    string result = m_userID;
    return result;
}
