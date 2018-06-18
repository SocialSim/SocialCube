#include "Simulator.hpp"

using namespace std;

DBG(static const string tag="Simulator";)

Simulator::Simulator() : m_communityManager(new CommunityManager),
    m_startTime(0), m_endTime(0), m_unitTime(1), m_statProxy(StatisticProxy::getInstance()) {

    srand(time(NULL));

    return;
}

Simulator::~Simulator() {
    return;
}

void Simulator::setStartTime(time_t t_currentTime) {
    m_startTime = t_currentTime;
}

void Simulator::setEndTime(time_t t_endTime) {
    m_endTime = t_endTime;
}

void Simulator::setUnitTime(time_t t_unitTime) {
    m_unitTime = t_unitTime;
}

void Simulator::addUserAgent(Agent const * t_agent) {
    m_communityManager->addAgent(t_agent);
}

void Simulator::addObjectAgent(Agent const * t_agent) {
    throw;
}

void Simulator::simulate() {
    preSimulationConfig();

    simulateImpl();

    postSimulationConfig();
}

void Simulator::simulateImpl() {
    m_communityManager->simulate(cc_list, temp_pref_data, m_startTime, m_endTime, m_unitTime);
}

// ./socialcube --show_profile --show_event -s 2018-04-02T00:00:00Z -e 2018-10-28T23:59:59Z --proxy_config_file /Users/Flamino/Virtualenvs/simulator_core/SocialCube/ProxyFilePaths.config
// ./socialcube --show_profile --show_event -s 2018-04-02T00:00:00Z -e 2018-04-29T23:59:59Z --proxy_config_file /Users/Flamino/Virtualenvs/simulator_core/SocialCube/ProxyFilePaths.config
void Simulator::preSimulationConfig() {
    DIR *dir;
    struct dirent *ent;
    vector<vector<float>> ccData;
    vector<int> ccCount;
    vector<string> ccRef;
    string statPath = m_statProxy.getStatProxyPath("ccStatsProxyFile");
    cout << "Simulator has retrieved cc stats from " << statPath << endl;
    int count = 0;
    if ((dir = opendir(statPath.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            string fileName = ent->d_name;
            if (fileName.size() > 3) {
                string ccName = getCc(fileName);

                ccRef.push_back(ccName);
                ccCount.push_back(0);

                vector<float> ph;
                ccData.push_back(ph);

                ifstream infile(statPath + fileName);
                string line;
                while (getline(infile, line)) {
                    if (line.length() > 1) {
                        ccData[count].push_back(stof(line));
                    }
                }
                count++;
            }
            
        }
        closedir(dir);
    } else {
        perror("");
    }

    string ccStatPath = m_statProxy.getStatProxyPath("countryCodesProxyFile");
    ifstream infile(ccStatPath);
    string line;
    while (getline(infile, line)) {
        if (line.length() < 3) {
            ptrdiff_t pos = distance(ccRef.begin(), find(ccRef.begin(), ccRef.end(), line));
            if (pos >= ccRef.size()) {
                continue;
            } else {
                ccCount[pos]++;
            }
        }
    }

    vector<float> subdata;
    for (int i = 0; i < ccData[ccRef.size() - 1].size(); i++) {
        for (int j = 0; j < ccRef.size(); j++) {
            if (ccCount[j] > 0) {
                if (cc_list.size() > 0) {
                    ptrdiff_t pos = distance(cc_list.begin(), find(cc_list.begin(), cc_list.end(), ccRef[j]));
                    if (pos >= cc_list.size()) {
                        cc_list.push_back(ccRef[j]);
                    }
                } else {
                    cc_list.push_back(ccRef[j]);
                }
                subdata.push_back(ceil(ccData[j][i] * ccCount[j]));
            }
        }
        temp_pref_data.push_back(subdata);
        subdata.clear();
    }

    printConfig();

    if(m_endTime < m_startTime) {
        EndTimeLessThanStartTime e_e;
        throw e_e;
    }

    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    EventManager& em = EventManager::getInstance();

    em.start();
    sp.timeStart();
}

void Simulator::postSimulationConfig() {
    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    EventManager& em = EventManager::getInstance();

    sp.timeEnd();
    em.end();
}

void Simulator::printConfig() {
    DBG(LOGP(TAG, "\n\n*************************** Simulator Configuration ***************************", false);)
    DBG(LOGP(TAG, "Simulation Start Time: "+stringfy(m_startTime));)
    DBG(LOGP(TAG, "Simulation End Time: "+stringfy(m_endTime));)
    DBG(LOGP(TAG, "Simulation Unit Time: "+stringfy(m_unitTime));)
    DBG(LOGP(TAG, "*************************** Simulator Configuration ***************************\n\n", false);)
}

string Simulator::getCc(const string& s) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, '.')) {
      tokens.push_back(token);
   }
   return tokens[0];
}

void Simulator::testSetup() {
    return;
}