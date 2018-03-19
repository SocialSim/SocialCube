#ifndef __AGENT__
#define __AGENT__

#include <vector>
#include <string>
#include <cstdint>
#include "common/Event.hpp"

class Agent {
    private:
        std::string m_id;
    public:
        Agent(const string& t_id) : m_id(t_id) {};

        virtual ~Agent();

        virtual std::vector<Event> step(uint64_t t_currentTime, uint64_t t_unitTime) = 0;

        std::string getID() { return m_id; }
};

#endif
