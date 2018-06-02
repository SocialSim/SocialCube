#include "Simulator.hpp"

using namespace std;

DBG(static const string tag="Simulator";)

Simulator::Simulator() : m_communityManager(new CommunityManager),
    m_startTime(0), m_endTime(0), m_unitTime(1) {

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
    m_communityManager->simulate(temp_pref_data, m_startTime, m_endTime, m_unitTime);
}

void Simulator::preSimulationConfig() {
    int total_users = 22226;
    int us_users = 13373;
    int in_users = 1819;
    int cn_users = 7034;

    const string socialcubePath = (getenv("SOCIALCUBEPATH"));

    ifstream us_infile(socialcubePath + "/dist/us_action_distribution.txt");
    string us_line;
    vector<float> us_data;
    while (getline(us_infile, us_line)) {
        if (us_line.length() > 0) {
            // us_line.erase(std::remove(us_line.begin(), us_line.end(), '\n'), us_line.end());
            us_data.push_back(stof(us_line));
        }
    }

    ifstream cn_infile(socialcubePath + "/dist/cn_action_distribution.txt");
    string cn_line;
    vector<float> cn_data;
    while (getline(cn_infile, cn_line)) {
        if (cn_line.length() > 0) {
            // cn_line.erase(std::remove(cn_line.begin(), cn_line.end(), '\n'), cn_line.end());
            cn_data.push_back(stof(cn_line));
        }
    }
    
    ifstream in_infile(socialcubePath + "/dist/in_action_distribution.txt");
    string in_line;
    vector<float> in_data;
    while (getline(in_infile, in_line)) {
        if (in_line.length() > 0) {
            // in_line.erase(std::remove(in_line.begin(), in_line.end(), '\n'), in_line.end());
            in_data.push_back(stof(in_line));
        }
    }

    vector<float> subdata;
    for (int i = 0; i < us_data.size(); i++) {
        subdata.push_back(ceil(us_data[i] * us_users));
        subdata.push_back(ceil(cn_data[i] * cn_users));
        subdata.push_back(ceil(in_data[i] * in_users));
        cout << subdata[0] << " " << subdata[1] << " " << subdata[2] << endl;
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
