#include "Simulator.hpp"

DBG(static const string tag="Simulator";)

Simulator::Simulator() : m_currentTime(0),
    m_startTime(0), m_endTime(0),
    m_unitTime(1), m_dependentEventLogger(nullptr), 
    m_profiler(new SimulatorProfiler), m_profileOn(false),
    m_eventThreashold(1<<20), m_eventFileName(""),
    m_eventCount(0) {

    srand(time(NULL));

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

void Simulator::setProfileShow(bool t_profileOn) {
    m_profileOn = t_profileOn;
}

void Simulator::setEventShow(bool t_eventOn) {
    m_eventOn = t_eventOn;
}

void Simulator::setEventThreashold(uint64_t t_threashold) {
    m_eventThreashold = t_threashold;
}

void Simulator::setEventFileName(const string& t_file) {
    m_eventFileName = t_file;
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
    preSimulationConfig();

    m_profiler->timeStart();

    simulateImpl();

    m_profiler->timeEnd();

    postSimulationConfig();

    showProfile();
}

void Simulator::simulateImpl() {
    for(; m_currentTime < m_endTime; m_currentTime += m_unitTime) {
        DBG(LOGD(TAG, "Simulate "+stringfy(m_currentTime)+"/"+stringfy(m_endTime));)
        step();
        emitEventOnExceedThreashold();
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
    m_eventCount += events.size();
    for(auto& event : events) {
        m_eventHistory.push_back(move(event));
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

void Simulator::preSimulationConfig() {
    DBG(LOGP(TAG, "\n\n*************************** Simulator Configuration ***************************", false);)
    DBG(LOGP(TAG, "     Simulation Start Time: "+stringfy(m_startTime));)
    DBG(LOGP(TAG, "     Simulation End Time: "+stringfy(m_endTime));)
    DBG(LOGP(TAG, "     Simulation Unit Time: "+stringfy(m_unitTime));)
    DBG(LOGP(TAG, "     Simulation Current Time: "+stringfy(m_currentTime));)
    DBG(LOGP(TAG, "     Simulation Profile Status: "+stringfy(m_profileOn));)
    DBG(LOGP(TAG, "     Simulation Event Threashold : "+stringfy(m_eventThreashold));)
    DBG(LOGP(TAG, "     Simulation Event Storage: "+stringfy(m_eventOn));)
    DBG(LOGP(TAG, "     Simulation Event Storage path: "+m_eventFileName);)
    DBG(LOGP(TAG, "*************************** Simulator Configuration ***************************\n\n", false);)
    // assert(m_currentTime >= 0);
    // assert(m_startTime >= 0);
    // assert(m_endTime>= 0);
    // assert(m_endTime >= m_startTime);
    m_eventFile.open(m_eventFileName.c_str()); 
}

void Simulator::postSimulationConfig() {
    storeEvent();
    m_eventFile.close(); 
    m_profiler->setEventCount(m_eventCount);
}

void Simulator::showProfile() {
    if(m_profileOn)
        m_profiler->showProfile();
}

void Simulator::emitEventOnExceedThreashold() {

    if(m_eventHistory.size() > m_eventThreashold) {
        DBG(LOGP(TAG, "Emit " + stringfy(m_eventHistory.size()) + " Events");)
        storeEvent();
        m_eventHistory.clear();
    }
}

void Simulator::storeEvent() {
    if(m_eventOn)
        _storeEvent();
}

void Simulator::_storeEvent(){
    DBG(LOGP(TAG, "Store " + stringfy(m_eventHistory.size()) + " Events");)
    for(auto& event : m_eventHistory) {
        m_eventFile << *event;
    }
}
