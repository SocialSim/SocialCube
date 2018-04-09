#include "SimulatorWorkerManager.hpp"

using namespace std;

void SimulatorWorkerManager::createWorkerThread() {
    unsigned wid = m_workerPool.size() + 1;
    m_cvPool[wid] = make_shared<condition_variable>();
    unique_ptr<SimulatorWorker> worker(new SimulatorWorker(wid, m_cvPool[wid]));
    m_workerPool.push_back(move(worker));
    m_freeWorkers.push(wid);
}


SimulatorWorkerManager& SimulatorWorkerManager::getInstance() {
    static SimulatorWorkerManager s;
    return s;
}

Workload SimulatorWorkerManager::fetchWorkload(unsigned wid) {
    lock_guard<mutex> lock(m_mutex);
    assert(m_workloadQueue.find(wid) != m_workloadQueue.end());
    Workload w = move(m_workloadQueue[wid]);
    m_workloadQueue.erase(wid);
    return move(w);
}

bool SimulatorWorkerManager::workloadAvailable(unsigned wid) {
    lock_guard<mutex> lock(m_mutex);
    return m_workloadQueue.find(wid) != m_workloadQueue.end();
}

void SimulatorWorkerManager::scheduleWorkload(Workload& t_workload) {
    lock_guard<mutex> lock(m_mutex);
    unsigned wid = chooseWorker(); // May consider load balancing
    if(wid == NO_WORKER_AVAILABLE) {
        m_workloadBuffer.push(move(t_workload));
    } else {
        m_workloadQueue[wid] = move(t_workload);
        m_cvPool[wid]->notify_one();
    }
}

unsigned SimulatorWorkerManager::chooseWorker() {
    if(m_freeWorkers.empty())
        return NO_WORKER_AVAILABLE;
    auto wid = m_freeWorkers.front();
    m_freeWorkers.pop();
    assert(wid != NO_WORKER_AVAILABLE);
    return wid;
}

void SimulatorWorkerManager::notifyWorkerManager(unsigned wid) {
    lock_guard<mutex> lock(m_mutex);
    if(m_workloadBuffer.empty()) {
        if(m_finishScheduling) {
            m_finishSimulation = true;
        }
        m_freeWorkers.push(wid); 
    } else {
        m_workloadQueue[wid] = move(m_workloadBuffer.front());
        m_workloadBuffer.pop();
    }
    return;
}

void SimulatorWorkerManager::spawnWorkers(size_t t_workerNum) {
    for(auto wid = 0; wid < t_workerNum; ++wid)
        createWorkerThread();
}

void SimulatorWorkerManager::finishSchedule() {
    lock_guard<mutex> lock(m_mutex);
    m_finishScheduling = true;
}

bool SimulatorWorkerManager::finishSimulation() {
    return m_finishSimulation;
}
