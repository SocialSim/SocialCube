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

        std::string m_cc;

        int m_al;

        uint64_t m_communityTag;

    public:
        Agent(const std::string& t_id, const std::string& t_cc, const int& t_al) : m_id(t_id), m_cc(t_cc), m_al(t_al) {};

        virtual ~Agent() = default;

        virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const = 0;

        virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const = 0;

        int getAL() const { return m_al; }

        std::string getCC() const { return m_cc; }

        std::string getID() const { return m_id; }

        virtual uint64_t getCommunityTag() const {throw;}
};

#endif
