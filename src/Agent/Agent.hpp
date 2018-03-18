#ifndef __AGENT__
#define __AGENT__

#include "common/Event.hpp"

class Agent {
    public:
        Agent();

        virtual ~Agent();

        virtual vector<Event> step() = 0;
};

#endif
