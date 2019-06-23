#include "UserEventNumberProxy.hpp"

using namespace std;

DBG(static const string tag="UserEventNumberProxy";)

UserEventNumberProxy::UserEventNumberProxy(const string& file) throw() {
    try {
        m_userEventNumberFile.open(file);
    } catch (exception &e) {
        UserEventNumberProxyException t_e;
        throw t_e;
    }
    assert(m_userEventNumberFile.is_open());
    return;
}

UserEventNumberProxy::~UserEventNumberProxy() {
    m_userEventNumberFile.close();
    return;
}

void UserEventNumberProxy::parse() {
    string tmp;

    while (getline(m_userEventNumberFile, tmp)) {
        stringstream ss(tmp);
        string user_id, str_event_num;
        getline(ss, user_id, ',');
        getline(ss, str_event_num);
        int event_num = stod(str_event_num);

        m_userEventNumber[user_id] = event_num;
    }
    DBG(LOGD(TAG, "Total user number = "+stringfy(m_userEventNumber.size()));)
}

int UserEventNumberProxy::getEventNumber(const std::string& userID) {
    return m_userEventNumber[userID];
}

bool UserEventNumberProxy::chooseThisUser(const std::string& userID) {
    if (m_userEventNumber[userID] > 0) {
        m_userEventNumber[userID]--;
        return true;
    } else {
        return false;
    }
}

void UserEventNumberProxy::show() {
    for(auto& iter : m_userEventNumber) {
        cout << iter.first << ": " << iter.second;
    }
}

std::string UserEventNumberProxy::randomlyChooseUser() {
    int randnum = rand() % m_userEventNumber.size();
    int counter = 0;
    for(auto& iter : m_userEventNumber) {
        if (counter == randnum) {
            return iter.first;
        } else {
            counter++;
        }
    }
}