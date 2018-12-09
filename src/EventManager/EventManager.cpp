#include "EventManager.hpp"

using namespace std;

DBG(static const string tag="EventManager";)

EventManager::EventManager() : m_eventCount(0), m_bufferSize(1<<24),
    m_eventFile(""), m_eventOn(false) {
    return;    
}

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

void EventManager::emitEventOnBufferFull() {

    if(m_events.size() > m_bufferSize) {
        DBG(LOGD(TAG, "Emit " + stringfy(m_events.size()) + " Events");)
        emitEvent();
        m_events.clear();
    }
}

void EventManager::emitEvent() {
    if (m_platform == "github") {
        if (m_eventOn) {
            if (m_center == "user-centric") {
                _emitGithubUserCentricEvent();
            } else if (m_center == "repo-centric") {
                _emitGithubRepoCentricEvent();
            }
        }
    } else if (m_platform == "reddit") {
        if (m_eventOn) {
            if (m_center == "user-centric") {
                _emitRedditUserCentricEvent();
            } else if (m_center == "repo-centric") {
                _emitRedditRepoCentricEvent();
            }
        }
    } else if (m_platform == "twitter") {
        if (m_eventOn) {
            if (m_center == "user-centric") {
                _emitTwitterUserCentricEvent();
            } else if (m_center == "repo-centric") {
                _emitTwitterRepoCentricEvent();
            }
        }
    }
}

void EventManager::_emitGithubUserCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    int count = 0;
    for(auto& event : m_events) {
//        m_eventFile << event->getTimestampStr() << "," << event->getEventType() << "," << event->getUserID() << "," <<
//                  event->getObjectID() << "," << event->getAction() << "," << event->getMerged() << "\n";
        if (count != 0) {
            m_eventFile << ", ";
        } else {
            count++;
        }

        m_eventFile << "{\"status\": \"" << event->getMerged() << "\", " <<
                "\"actionType\": \"" << event->getEventType() << "\", " <<
                "\"nodeTime\": \"" << event->getTimestampStr() << "\", " <<
                "\"nodeUserID\": \"" << event->getUserID() << "\", " <<
                "\"actionSubType\": \"" << event->getAction() << "\", " <<
                "\"nodeID\": \"" << event->getObjectID() << "\"}";
    }
}

void EventManager::_emitGithubRepoCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    int count = 0;
    for(auto& event : m_events) {
        if (count != 0) {
            m_eventFile << ", ";
        } else {
            count++;
        }

        m_eventFile << "{\"status\": \"" << event->getMerged() << "\", " <<
                    "\"actionType\": \"" << event->getEventType() << "\", " <<
                    "\"nodeTime\": \"" << event->getTimestampStr() << "\", " <<
                    "\"nodeUserID\": \"" << event->getObjectID() << "\", " <<
                    "\"actionSubType\": \"" << event->getAction() << "\", " <<
                    "\"nodeID\": \"" << event->getUserID() << "\"}";
    }
}

void EventManager::_emitRedditUserCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    string communityIDs[6] = {
            "t5_2s3qj",
            "t5_2zf9m",
            "t5_2zwl2",
            "t5_31hbr",
            "t5_3bqj4",
            "t5_3i6d8"};

    int count = 0;
    for(auto& event : m_events) {
        if (count != 0) {
            m_eventFile << ", ";
        } else {
            count++;
        }

        string communityID;
        if (event->getCommunityID() != "") {
            communityID = event->getCommunityID();
        } else {
            communityID = communityIDs[rand() % (int)(sizeof(communityIDs)/sizeof(communityIDs[0]) - 1)];
        }

        m_eventFile << "{\"rootID\": \"" << event->getRootID() << "\", " <<
                    "\"communityID\": \"" << communityID << "\", " <<
                    "\"actionType\": \"" << event->getEventType() << "\", " <<
                    "\"parentID\": \"" << event->getParentID() << "\", " <<
                    "\"keywords\": [], " <<
                    "\"nodeTime\": \"" << event->getTimestampStrInSeconds() << "\", " <<
                    "\"nodeUserID\": \"" << event->getUserID() << "\", " <<
                    "\"nodeID\": \"" << event->getObjectID() << "\"}";
    }
//
//    for(auto& event : m_events) {
//        string communityID;
//        if (event->getCommunityID() != "") {
//            communityID = event->getCommunityID();
//        } else {
//            communityID = communityIDs[rand() % (int)(sizeof(communityIDs)/sizeof(communityIDs[0]) - 1)];
//        }
//
//        m_eventFile << event->getObjectID() << "," << event->getUserID() << "," << event->getParentID() << "," << event->getRootID()
//                << "," << event->getEventType() << "," << event->getTimestampStrInSeconds() << "," << "\"{'keywords':[], 'communityID': '" + communityID + "'}\"\n";
//
//    }
}

void EventManager::_emitRedditRepoCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    string communityIDs[6] = {
            "t5_2s3qj",
            "t5_2zf9m",
            "t5_2zwl2",
            "t5_31hbr",
            "t5_3bqj4",
            "t5_3i6d8"};

    int count = 0;
    for(auto& event : m_events) {
        if (count != 0) {
            m_eventFile << ", ";
        } else {
            count++;
        }

        string communityID;
        if (event->getCommunityID() != "") {
            communityID = event->getCommunityID();
        } else {
            communityID = communityIDs[rand() % (int)(sizeof(communityIDs)/sizeof(communityIDs[0]) - 1)];
        }

        m_eventFile << "{\"rootID\": \"" << event->getRootID() << "\", " <<
                    "\"communityID\": \"" << communityID << "\", " <<
                    "\"actionType\": \"" << event->getEventType() << "\", " <<
                    "\"parentID\": \"" << event->getParentID() << "\", " <<
                    "\"keywords\": [], " <<
                    "\"nodeTime\": \"" << event->getTimestampStrInSeconds() << "\", " <<
                    "\"nodeUserID\": \"" << event->getObjectID() << "\", " <<
                    "\"nodeID\": \"" << event->getUserID() << "\"}";
    }
}

void EventManager::_emitTwitterUserCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)

    int count = 0;
    for(auto& event : m_events) {
        if (count != 0) {
            m_eventFile << ", ";
        } else {
            count++;
        }

        m_eventFile << "{\"rootID\": \"" << event->getRootID() << "\", " <<
                    "\"actionType\": \"" << event->getEventType() << "\", " <<
                    "\"parentID\": \"" << event->getParentID() << "\", " <<
                    "\"nodeTime\": \"" << event->getTimestampStrInSeconds() << "\", " <<
                    "\"nodeUserID\": \"" << event->getUserID() << "\", " <<
                    "\"nodeID\": \"" << event->getObjectID() << "\"}";
    }
//    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
//
//    for(auto& event : m_events) {
//        m_eventFile << event->getObjectID() << "," << event->getUserID() << "," << event->getParentID() << "," << event->getRootID()
//                    << "," << event->getEventType() << "," << event->getTimestampStrInSeconds() << ",{}\n";
//    }
}

void EventManager::_emitTwitterRepoCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)

    int count = 0;
    for(auto& event : m_events) {
        if (count != 0) {
            m_eventFile << ", ";
        } else {
            count++;
        }

        m_eventFile << "{\"rootID\": \"" << event->getRootID() << "\", " <<
                    "\"actionType\": \"" << event->getEventType() << "\", " <<
                    "\"parentID\": \"" << event->getParentID() << "\", " <<
                    "\"nodeTime\": \"" << event->getTimestampStrInSeconds() << "\", " <<
                    "\"nodeUserID\": \"" << event->getObjectID() << "\", " <<
                    "\"nodeID\": \"" << event->getUserID() << "\"}";
    }
//    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
//
//    for(auto& event : m_events) {
//        m_eventFile << event->getUserID() << "," << event->getObjectID() << "," << event->getParentID() << "," << event->getRootID()
//                    << "," << event->getEventType() << "," << event->getTimestampStrInSeconds() << ",{}\n";
//    }
}

void EventManager::start() {
    DBG(LOGP(TAG, "\n\n*************************** Event Manager Configuration ***************************", false);)
    DBG(LOGP(TAG, "Event Buffer Size: "+stringfy(m_bufferSize));)
    DBG(LOGP(TAG, "Event Storage: "+m_eventFileName);)
    DBG(LOGP(TAG, "Event Show Status: "+stringfy(m_eventOn));)
    DBG(LOGP(TAG, "*************************** Simulator Configuration ***************************\n\n", false);)
    m_eventFile.open(m_eventFileName.c_str(), std::ofstream::app);
    cout << "Domain: " << m_domain << endl;

    m_eventFile << "{\"platform\": \"" << m_platform << "\", \"domain\": \"" << m_domain <<
                "\", \"scenario\": \"" << m_scenario << "\", \"team\": \"uiuc\", " <<
                "\"data\": [";

//    if (m_platform == "github") {
//        m_eventFile << "nodeTime,actionType,nodeUserID,nodeID,actionSubType,status" << endl;
//    } else if (m_platform == "reddit") {
//        m_eventFile << "nodeID,nodeUserID,parentID,rootID,actionType,nodeTime,nodeAttributes" << endl;
//    } else if (m_platform == "twitter") {
//        m_eventFile << "nodeID,nodeUserID,parentID,rootID,actionType,nodeTime,nodeAttributes" << endl;
//    }
}

void EventManager::end() {
    emitEvent();
    m_eventFile << "]}" << endl;
    m_eventFile.close(); 

    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    sp.setEventCount(m_eventCount);
}

uint64_t EventManager::getEventCount() {
    return m_eventCount;
}

void EventManager::storeEvent(std::vector<std::unique_ptr<Event>>& events) {
    m_eventCount += events.size();
    m_events.insert(
        m_events.end(),
        std::make_move_iterator(events.begin()),
        std::make_move_iterator(events.end())
    );
    events.clear();

    emitEventOnBufferFull();
}

void EventManager::setCenter(const std::string& center) {
    m_center = center;
}

void EventManager::setPlatform(const std::string& platform) {
    m_platform = platform;
}

void EventManager::setScenario(const std::string& scenario) {
    m_scenario = scenario;
}

void EventManager::setDomain(const std::string& domain) {
    m_domain = domain;
}

void EventManager::setEventShow(bool t_eventOn) {
    m_eventOn = t_eventOn;
}

void EventManager::setEventFileName(const std::string& t_file) {
    m_eventFileName = t_file;
}

void EventManager::setEventBufferSize(uint64_t t_bufferSize) {
    m_bufferSize = t_bufferSize;
}
