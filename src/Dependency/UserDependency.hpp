#ifndef __USER_DEPENDENCY__
#define __USER_DEPENDENCY__

#include <unordered_map>

class UserDependency {

    private:

        std::unordered_map<std::string, double> m_dependency;

        uint64_t m_userID;

    public:

        UserDependency(uint64_t t_userID);

        ~UserDependency();

        void set(const std::string& t_dependentID, double t_dependency);

        double get(const std::string& t_dependentID);
};

#endif
