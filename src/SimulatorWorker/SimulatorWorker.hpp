#ifndef __SIMULATOR_WORKER__
#define __SIMULATOR_WORKER__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>

#include "Simulator/Community.hpp"
#include "EventManager/EventManager.hpp"
#include "SimulatorWorkerManager/SimulatorWorkerManager.hpp"
#include "common/Workload.hpp"
#include "Log/Log.hpp"

class SimulatorWorkerManager;

class SimulatorWorker {
    private:
        // member variables 
        SimulatorWorkerManager& manager;

        std::thread* m_thread;

        const unsigned m_workerID;

        std::shared_ptr<std::condition_variable> m_cv;

        // member functions
        std::unique_ptr<Workload> fetchWorkload(unsigned wid) const;

        void notifyWorkerManager() const;

        // class functions
        static bool workloadAvailable(unsigned wid);

        static void SimulatorWorkerImpl(SimulatorWorker const * ptr);

        static void simulate(std::unique_ptr<Workload>& t_workload, unsigned t_workerID);
        
    public:
        SimulatorWorker(unsigned t_workerID, std::shared_ptr<std::condition_variable> t_cv);

        ~SimulatorWorker();

        unsigned getWorkerID() const;
};

#endif
