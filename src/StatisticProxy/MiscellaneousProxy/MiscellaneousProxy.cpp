#include "MiscellaneousProxy.hpp"

DBG(static const string tag="MiscellaneousProxy";)

using namespace std;

MiscellaneousProxy::MiscellaneousProxy(const string& file) throw() {
    try {
        m_miscellaneousStatisticFile.open (file);
    } catch (exception &e) {
        MiscellaneousProxyException h_e;
        throw h_e;
    }
    assert(m_miscellaneousStatisticFile.is_open());

    return;
}

MiscellaneousProxy::~MiscellaneousProxy() {
    m_miscellaneousStatisticFile.close();
    return;
}

void MiscellaneousProxy::parse() {
    string line;
    string name;
    string delimiter = " ";
    while (std::getline(m_miscellaneousStatisticFile, line)) {
        if (line.length() > 0 && line.at(0) == '#') {
            name = line.substr(line.find('#') + 1, line.length());
        } else if (line.length() > 0) {
            int pos = line.find(delimiter);
            if (pos != std::string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + delimiter.length(), line.length());
                if (name == "Quartile") {
                    if (key == "first") {
                        m_quartile[0] = stod(value);
                    } else if (key == "second") {
                        m_quartile[1] = stod(value);
                    } else if (key == "third") {
                        m_quartile[2] = stod(value);
                    }
                } else if (name == "ActionTypeDistribution") {
                    m_actionTypeDistribution[key] = stof(value);
                }
            } else {
                cout << "Format Error!" << endl;
            }
        }
    }
}

void MiscellaneousProxy::show() {
}

unordered_map<string, double> MiscellaneousProxy::getActionTypeDistribution() {
    return m_actionTypeDistribution;
};

double* MiscellaneousProxy::getQuartile() {
    return m_quartile;
}