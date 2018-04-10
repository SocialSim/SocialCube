#ifndef __SIMULATOR_WORKER_MANAGER__
#define __SIMULATOR_WORKER_MANAGER__

#include <thread>
#include <unordered_map>
#include <cassert>
#include <mutex>
#include <memory>
#include <queue>
#include <condition_variable>

#include "Simulator/Community.hpp"
#include "SimulatorWorker/SimulatorWorker.hpp"
#include "common/Workload.hpp"

class SimulatorWorker;

class SimulatorWorkerManager {
    private:
        #define NO_WORKER_AVAILABLE 0

    private:
        // private member variables
        std::vector<std::unique_ptr<SimulatorWorker>> m_workerPool;

        std::unordered_map<unsigned, std::shared_ptr<std::condition_variable>> m_cvPool;

        std::mutex m_mutex;

        std::queue<unsigned> m_freeWorkers; // Worker will only be in m_freeWorkers when it is not assigned to a workload

        std::unordered_map<unsigned, std::unique_ptr<Workload>> m_workloadQueue;

        std::queue<std::unique_ptr<Workload>> m_workloadBuffer;

        bool m_finishSimulation {false};

        bool m_finishScheduling {false};

        // private member functions
        SimulatorWorkerManager() = default;

        void createWorkerThread();

        unsigned chooseWorker();

    public:
        static SimulatorWorkerManager& getInstance();

        std::unique_ptr<Workload> fetchWorkload(unsigned wid);

        bool workloadAvailable(unsigned wid);

        void scheduleWorkload(std::unique_ptr<Workload> t_workload);

        void notifyWorkerManager(unsigned wid);

        void spawnWorkers(size_t t_workerNum = 1);

        void finishSchedule();

        bool finishSimulation();
};


#endif
