#ifndef __SOCIALCUBE_SCHEDULER__
#define __SOCIALCUBE_SCHEDULER__

#include <vector>
#include <unordered_map>

class Scheduler {
    private:

    public:
        Scheduler() = default;

        ~Scheduler() = default;

        virtual std::vector<uint64_t> schedule(const std::unordered_map<uint64_t, size_t>& t_communityPendingSimulation) = 0;
};

#endif
