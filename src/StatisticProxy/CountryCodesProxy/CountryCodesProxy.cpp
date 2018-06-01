#include "CountryCodesProxy.hpp"

using namespace std;

DBG(static const string tag="CountryCodesProxy";)

CountryCodesProxy::CountryCodesProxy(const string& file) throw() {
    try{
        m_countryCodesStatisticsFile.open(file.c_str());
    } catch(exception& e) {
        CountryCodesProxyException u_e;
        throw u_e;
    }
    assert(m_countryCodesStatisticsFile.is_open());
    return;
}

CountryCodesProxy::~CountryCodesProxy() {
    m_countryCodesStatisticsFile.close();
    return;
}

void CountryCodesProxy::parse() {
    string countryCode;
    while (m_countryCodesStatisticsFile >> countryCode)
        m_countryCodes.push_back(countryCode);
    DBG(LOGD(TAG, "Country Code has "+stringfy(m_countryCodes.size()));)
}

vector<string>& CountryCodesProxy::get() {
    return m_countryCodes;
}

void CountryCodesProxy::show() {
    for(auto cc : m_countryCodes)
        cout << cc << "\n";
    cout << m_countryCodes.size() << endl;
}

uint64_t CountryCodesProxy::getCommunityTag(const string& t_userID) {
    UserIDProxyNoMethodException u_e;
    throw u_e;
}