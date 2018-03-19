#ifndef __DEPENDENT_EVENT_LOGGER_
#define __DEPENDENT_EVENT_LOGGER_

#include <vector>
#include <string>

class DependentEventLogger {
    public:
        DependentEventLogger();
        ~DependentEventLogger();
        void step();
        void logUserEventAtTime(const std::string& userID, const std::string& eventType, const std::string& timestamp);
};

#endif
