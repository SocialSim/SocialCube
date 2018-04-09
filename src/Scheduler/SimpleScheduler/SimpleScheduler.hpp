#ifndef __SIMPLE_SCHEDULER__
#define __SIMPLE_SCHEDULER__

#include "Scheduler/Scheduler.hpp"

class SimpleScheduler : public Scheduler {

    private:

        // private member variables
        
        size_t m_batchSize;

        // private member functions

        bool batchFull(size_t t_batchSize);

        SimpleScheduler();

    public:

        static SimpleScheduler& getInstance();

        ~SimpleScheduler() = default;

        virtual std::vector<uint64_t> schedule(const std::unordered_map<uint64_t, size_t>& t_communityPendingSimulation) override;

};

#endif
