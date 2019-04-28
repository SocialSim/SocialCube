#include "SeedInfoIDProxy.hpp"

DBG(static const string tag="SeedInfoIDProxy";)

using namespace std;

SeedInfoIDProxy::SeedInfoIDProxy(const string& file) throw() {
    try {
        m_seedInfoIDStatisticFile.open (file);
    } catch (exception &e) {
        SeedInfoIDProxyException h_e;
        throw h_e;
    }
    assert(m_seedInfoIDStatisticFile.is_open());

    return;
}

SeedInfoIDProxy::~SeedInfoIDProxy() {
    m_seedInfoIDStatisticFile.close();
    return;
}

void SeedInfoIDProxy::parse() {
    string tmp;
    while (getline(m_seedInfoIDStatisticFile, tmp)) {
        // information_id
        string information_id = tmp.substr(0, tmp.find(" "));
        seed_infoIDs.push_back(information_id);
    }
}

void SeedInfoIDProxy::show() {
    cout << seed_infoIDs.size() << endl;
}

vector<string> SeedInfoIDProxy::get() {
    return seed_infoIDs;
}
