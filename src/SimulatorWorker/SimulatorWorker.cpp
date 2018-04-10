#include "SimulatorWorker.hpp"

DBG(static const string tag="SimulatorWorker";)

using namespace std;

void SimulatorWorker::SimulatorWorkerImpl(SimulatorWorker const * ptr) {
    SimulatorWorker const * worker = ptr;
    const unsigned wid = worker->getWorkerID();
    mutex m; // a mutex to protect the channel

    while(true) {
        {
            unique_lock<mutex> lock(m);
            worker->m_cv->wait(lock, [&wid]() { return SimulatorWorker::workloadAvailable(wid);});
            auto workload = worker->fetchWorkload(wid);
            SimulatorWorker::simulate(workload);
            worker->notifyWorkerManager();
        }
    }
}

SimulatorWorker::SimulatorWorker(unsigned t_workerID, shared_ptr<condition_variable> t_cv) :
    manager(SimulatorWorkerManager::getInstance()),
    m_workerID(t_workerID),
    m_cv(t_cv) {
    m_thread = new thread(SimulatorWorker::SimulatorWorkerImpl, this);
    return;
}

SimulatorWorker::~SimulatorWorker() {
    // delete m_thread;
}

Workload SimulatorWorker::fetchWorkload(unsigned wid) const {
    return move(manager.fetchWorkload(wid));
}

bool SimulatorWorker::workloadAvailable(unsigned wid) {
    SimulatorWorkerManager& sm = SimulatorWorkerManager::getInstance();
    return sm.workloadAvailable(wid);
}

void SimulatorWorker::simulate(Workload& t_workload) {
    time_t startTime = t_workload.getStartTime();
    time_t endTime = t_workload.getEndTime();
    time_t unitTime = t_workload.getUnitTime();
    auto community = t_workload.transferWorkload();

    EventManager& em = EventManager::getInstance();

    vector<unique_ptr<Event>> events;

    for(auto& iter : community) {
        DBG(LOGD(TAG, "Simulating " + stringfy(iter->getCommunityTag()) + " Community");)
        vector<unique_ptr<Event>> community_events = iter->step(startTime, unitTime);
        em.storeEvent(community_events);
    }
}

void SimulatorWorker::notifyWorkerManager() const {
    manager.notifyWorkerManager(m_workerID);
}

unsigned SimulatorWorker::getWorkerID() const {
    return m_workerID;
}
