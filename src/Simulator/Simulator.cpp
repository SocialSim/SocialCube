#include "Simulator.hpp"

DBG(static const string tag="Simulator";)

Simulator::Simulator() : m_currentTime (0), m_startTime (0), m_endTime (0),
    m_unitTime (1), m_dependentEventLogger(nullptr) {

    srand(time(NULL));

    DBG(LOGD(TAG, "Simulation Start Time "+stringfy(m_startTime));)
    DBG(LOGD(TAG, "Simulation End Time "+stringfy(m_endTime));)
    DBG(LOGD(TAG, "Simulation Unit Time"+stringfy(m_unitTime));)
    DBG(LOGD(TAG, "Simulation Current Time "+stringfy(m_currentTime));)
    return;
}

Simulator::~Simulator() {
    return;
}

void Simulator::setCurrentTime(uint64_t t_currentTime) {
    m_currentTime = t_currentTime;
}

void Simulator::setStartTime(uint64_t t_currentTime) {
    m_startTime = t_currentTime;
}

void Simulator::setEndTime(uint64_t t_endTime) {
    m_endTime = t_endTime;
}

void Simulator::setUnitTime(uint64_t t_unitTime) {
    m_unitTime = t_unitTime;
}

void Simulator::setDependentEventLogger(unique_ptr<DependentEventLogger>& t_dependentEventLogger) {
    m_dependentEventLogger = move(t_dependentEventLogger);
}

void Simulator::addUserAgent(unique_ptr<UserAgent> t_agent) {
    m_userAgents.push_back(move(t_agent));
}

void Simulator::addObjectAgent(unique_ptr<ObjectAgent> t_agent) {
    m_objectAgents.push_back(move(t_agent));
}

void Simulator::transferUserAgent(vector<unique_ptr<UserAgent>>& t_agentList) {
    m_userAgents = (move(t_agentList));
}

void Simulator::simulate() {
    simulationCheck();

    for(; m_currentTime < m_endTime; m_currentTime += m_unitTime) {
        DBG(LOGD(TAG, "Simulate "+stringfy(m_currentTime)+"/"+stringfy(m_endTime));)
        step();
    }
}

void Simulator::step() {
    if(m_dependentEventLogger)
        m_dependentEventLogger->step();

    for(auto& agent : m_userAgents) {
        vector<unique_ptr<Event>> events = agent->step(m_currentTime, m_unitTime);
        logEventInDependentEventLogger(events);
        appendEventInEventHistory(events);
    }
}

void Simulator::logEventInDependentEventLogger(const vector<unique_ptr<Event>>& events) {
    for(auto& event : events) {
        string userId = event->getUserID();
        string eventType = event->getEventType();
        uint64_t timeStamp = event->getTimestamp();
        m_dependentEventLogger->logUserEventAtTime(userId, eventType, timeStamp);
    }
}

void Simulator::appendEventInEventHistory(vector<unique_ptr<Event>>& events) {
    for(auto& event : events) {
        m_eventHistory.push_back(move(event));
    }
}

void Simulator::showEvent(){
    for(auto& event : m_eventHistory) {
        event->show();
    }
}

uint64_t Simulator::getCurrentTime() {
    return m_currentTime;
}

// NOTE: return vector<string> here to leverage "named return value optimization"
vector<string> Simulator::getAllUserIDs() {
    vector<string> userIDs;
    for(auto& agent : m_userAgents) {
        userIDs.push_back(agent->getID()); 
    }
    return userIDs;
}


void Simulator::simulationCheck() {
    // assert(m_currentTime >= 0);
    // assert(m_startTime >= 0);
    // assert(m_endTime>= 0);
    // assert(m_endTime >= m_startTime);
}
