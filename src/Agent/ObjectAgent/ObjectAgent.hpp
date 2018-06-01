#ifndef __OBJECT_AGENT__
#define __OBJECT_AGENT__

#include <string>
#include "common/Event.hpp"
#include "Agent/Agent.hpp"

class ObjectAgent : public Agent {
    protected:
        ObjectAgent(const std::string& t_id, const std::string& t_cc, const int& t_al) : Agent(t_id, t_cc, t_al) {};

    public:

        virtual ~ObjectAgent() {};
};

#endif
