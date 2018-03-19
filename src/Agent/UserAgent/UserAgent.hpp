#ifndef __USER_AGENT__
#define __USER_AGENT__

#include <string>
#include "common/Event.hpp"
#include "Agent/Agent.hpp"

class UserAgent : public Agent {
    protected:

        UserAgent(const std::string& t_id) : Agent(t_id) {};

    public:

        virtual ~UserAgent() {};
};

#endif
