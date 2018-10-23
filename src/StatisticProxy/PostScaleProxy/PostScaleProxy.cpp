#include "PostScaleProxy.hpp"

using namespace std;

DBG(static const string tag="PostScaleProxy";)

PostScaleProxy::PostScaleProxy(const string& file) throw() {
    try {
        m_postScaleFile.open(file);
    } catch (exception &e) {
        PostScaleProxyException t_e;
        throw t_e;
    }
    assert(m_postScaleFile.is_open());
    return;
}

PostScaleProxy::~PostScaleProxy() {
    m_postScaleFile.close();
    return;
}

void PostScaleProxy::parse() {
    string tmp;
    while (getline(m_postScaleFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string scales = tmp.substr(tmp.find(" ") + 1);
        unique_ptr<PostScale> postScale(new PostScale(userID));
        double number;
        double scale;
        istringstream in(scales);
        while (in >> number) {
            in >> scale;
            postScale->pushScale(number, scale);
        }
        m_postScale[userID] = move(postScale);
    }
    DBG(LOGD(TAG, "Post Scale has "+stringfy(m_postScale.size()));)
}

void PostScaleProxy::show() {
    cout << m_postScale.size() << endl;
    for(auto& iter : m_postScale) {
        iter.second->show();
    }
}

PostScale& PostScaleProxy::get(const std::string& userID) {
    if(m_postScale.find(userID) == m_postScale.end()) {
        throw;
    } else {
        assert(m_postScale.find(userID) != m_postScale.end());
        return *(m_postScale[userID]);
    }
}
