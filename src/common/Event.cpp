#include "Event.hpp"

using namespace std;

Event::Event(const string& t_userID, const string& t_objectID, const string& t_eventType, time_t t_timestamp) :
    m_userID(t_userID), m_objectID(t_objectID), m_eventType(t_eventType), 
    m_timestamp(t_timestamp) {
    if (m_eventType == "IssuesEvent" || m_eventType == "PullRequestEvent") {
        StatisticProxy& statisticProxy = StatisticProxy::getInstance();
        unordered_map<std::string, double> subEventTypeProbability = statisticProxy.getSubEventTypeProbability();
        if (m_eventType == "IssuesEvent") {
            setAction(subEventTypeProbability["IssuesEventOpened"], subEventTypeProbability["IssuesEventClosed"],
            subEventTypeProbability["IssuesEventReopened"]);
        } else {
            setAction(subEventTypeProbability["PullRequestEventOpened"], subEventTypeProbability["PullRequestEventClosed"],
            subEventTypeProbability["PullRequestEventReopened"]);
            setMerged(subEventTypeProbability["PullRequestEventMerged"]);
        }
    }
    return;
}

Event::~Event() {
    return;
}

string Event::getUserID() const {
    return m_userID;
}

string Event::getObjectID() const {
    return m_objectID;
}

string Event::getEventType() const {
    return m_eventType;
}

string Event::getTimestampStr() const {
    char buf[sizeof "1970-00-00 00:00:00"];
    strftime(buf, sizeof buf, "%F %T", gmtime(&m_timestamp));
    return buf;
}

string Event::getAction() const {
    return m_action;
}

string Event::getMerged() const {
	if (m_merged) {
 	    return "True";
	} else {
	    return "False";
	}
}

time_t Event::getTimestamp() const {
    return m_timestamp;
}

void Event::setAction(double p_opened, double p_closed, double p_reopened) {
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    if (randnum <= p_opened) {
        m_action = "opened";
    } else if (randnum <= p_closed) {
        m_action = "closed";
    } else {
        m_action = "reopened";
    }
}

void Event::setMerged(double p) {
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    if (randnum < p) {
        m_merged = true;
    } else {
        m_merged = false;
    }
}

void Event::warpTimestamp(time_t startTime, double ratio) {
    // cout << "startTime = " << ctime(&startTime) << ", ratio = " << ratio << ", m_timestamp = " << ctime(&m_timestamp);
    m_timestamp = (m_timestamp - startTime) * ratio + startTime;
    // cout << ", new m_timestamp = " << ctime(&m_timestamp) << endl;
}

void Event::show() const {
    cout << getTimestampStr() << " " << getObjectID() << " " << getUserID() << " " << getEventType() << "\n";
}

ostream& operator<<(ostream& os, const Event& e)
{  
    os << e.getTimestampStr() << "," << e.getEventType() << "," << e.getUserID() << "," << e.getObjectID() << "\n";
    // os << e.getTimestampStr() << "," << e.getEventType() << "," << e.getObjectID() << "," << e.getUserID() << "\n";
    return os;  
}

//bool Event::operator< (const Event &other) const {
//    std::cout << "operator <" << std::endl;
//    return m_timestamp < other.getTimestamp();
//}
