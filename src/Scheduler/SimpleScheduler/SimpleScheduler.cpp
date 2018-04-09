#include "SimpleScheduler.hpp"

using namespace std;

SimpleScheduler& SimpleScheduler::getInstance() {
    static SimpleScheduler s;
    return s;
}

SimpleScheduler::SimpleScheduler() : m_batchSize(1000) {
    return;
}

vector<uint64_t> SimpleScheduler::schedule(const unordered_map<uint64_t, size_t>& t_communityPendingSimulation) {
    vector<uint64_t> batch;
    size_t batch_size = 0;

    for(auto& iter : t_communityPendingSimulation) {
        batch.push_back(iter.first);
        batch_size += iter.second;
        if(batchFull(batch_size))
            break;
    }

    return batch;
}

bool SimpleScheduler::batchFull(size_t t_batchSize) {
    return t_batchSize >= m_batchSize;
}
