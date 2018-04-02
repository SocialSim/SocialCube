#ifndef __COMMUNITY__
#define __COMMUNITY__

#include <vector>
#include <memory>
#include <cstdlib>
#include "Agent/UserAgent/UserAgent.hpp"
#include "common/Event.hpp"

class Community {
    private:

        std::vector<std::unique_ptr<UserAgent>> m_community;

        uint64_t m_communityTag;

    public:
        Community(uint64_t t_communityTag);

        ~Community() = default;

        size_t size();

        uint64_t getCommunityTag();

        void add(std::unique_ptr<UserAgent>& t_agent);

        std::vector<std::unique_ptr<Event>> step(uint64_t t_currentTime, uint64_t t_unitTime);
};

#endif
