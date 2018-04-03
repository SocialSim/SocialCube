#ifndef __AGENT__
#define __AGENT__

#include <vector>
#include <string>
#include <cstdint>
#include <memory>
#include "common/Event.hpp"

class Agent {
    protected:
        std::string m_id;
    public:
        Agent(const std::string& t_id) : m_id(t_id) {};

        virtual ~Agent() = default;

        virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const = 0;

        std::string getID() { return m_id; }

        virtual uint64_t getCommunityTag() const {throw;}
};

#endif
