#ifndef __USER_AGENT__
#define __USER_AGENT__

#include <string>
#include "common/Event.hpp"
#include "Agent/Agent.hpp"

class UserAgent : public Agent {
    protected:

        UserAgent(const std::string& t_id, const std::string& t_cc, const int& t_al) : Agent(t_id, t_cc, t_al) {};

    public:

        virtual ~UserAgent() = default;
};

#endif
