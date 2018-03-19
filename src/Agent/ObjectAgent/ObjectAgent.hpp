#ifndef __OBJECT_AGENT__
#define __OBJECT_AGENT__

#include <string>
#include "common/Event.hpp"
#include "Agent/Agent.hpp"

class ObjectAgent : public Agent {
    protected:
        ObjectAgent(const std::string& t_id) : Agent(t_id) {};

    public:

        virtual ~ObjectAgent() {};
};

#endif
