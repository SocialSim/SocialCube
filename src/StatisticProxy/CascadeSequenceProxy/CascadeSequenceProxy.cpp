#include "CascadeSequenceProxy.hpp"

using namespace std;

DBG(static const string tag="CascadeSequenceProxy";)

CascadeSequenceProxy::CascadeSequenceProxy(const string& file) throw() {
    try {
        m_cascadeSequenceFile.open(file);
    } catch (exception &e) {
        CascadeSequenceProxyException t_e;
        throw t_e;
    }
    assert(m_cascadeSequenceFile.is_open());
    return;
}

CascadeSequenceProxy::~CascadeSequenceProxy() {
    m_cascadeSequenceFile.close();
    return;
}

void CascadeSequenceProxy::parse() {
    string tmp;
    set<string> infoIds;
    while (getline(m_cascadeSequenceFile, tmp)) {
        istringstream in(tmp);

        string postId;
        getline(in, postId, ',');

        string infoId;
        getline(in, infoId, ',');

        string userId;
        getline(in, userId, ',');

        string str_timestamp;
        getline(in, str_timestamp, ',');

        if (infoIds.find(infoId) == infoIds.end()) {
            m_cascadeSequences.insert(make_pair(infoId, CascadeSequence(infoId)));
        }

        CascadeSequence& cs = m_cascadeSequences.find(infoId)->second;
        cs.pushPost(postId, userId, parseTime(str_timestamp));

        string action_type;

        while (in.good()) {
            getline(in, action_type, ',');
            getline(in, str_timestamp, ',');
            cs.pushCommentAfterPost(postId, action_type, parseTime(str_timestamp));
        }
    }

    DBG(LOGD(TAG, "CascadeSequence has "+stringfy(m_cascadeSequences.size()));)
}

void CascadeSequenceProxy::show() {
    cout << m_cascadeSequences.size() << endl;
    for(auto& iter : m_cascadeSequences) {
        iter.second.show();
    }
}

bool CascadeSequenceProxy::checkInfoID(std::string info_id) {
    if (m_cascadeSequences.find(info_id) != m_cascadeSequences.end()) {
        return true;
    } else {
        return false;
    }
}

CascadeSequence& CascadeSequenceProxy::getCascadeSequence(std::string infoId) {
    return m_cascadeSequences.find(infoId)->second;
}

time_t CascadeSequenceProxy::parseTime(string& str_time) {
    tm t = {};
    istringstream ss(str_time);

    if (ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
    {
        return std::mktime(&t);
    } else {
        throw;
    }
}
