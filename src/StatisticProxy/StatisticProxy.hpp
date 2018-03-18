#ifndef __STATISTIC_PROXY__
#define __STATISTIC_PROXY__

#include <vector>
#include <string>
#include <unordered_map>

class StatisticProxy {

    private:

        // Private member variables
        std::vector<std::string> m_userIDs;

        std::vector<std::string> m_objectIDs;

        std::unordered_map<std::string, HourlyActionRate> m_allUserActionRate;

        std::unordered_map<std::string, ObjectPreference> m_allObjectPreference;

        std::unordered_map<std::string, UserDependency> m_allUserDependency;

        // Private member functions
        StatisticProxy();

        void retrieveUserIDs();

        void retrieveObjIDs();

        void retrieveUserActionRate();

        void retrieveObjectPreference(); 

        void retrieveUserDependency();

    public:

        ~StatisticProxy();
        
        static StatisticProxy& getInstance();

        void retrieveStatistics();

        std::vector<std::string>& getUserIds();

        std::vector<std::string>& getObjectIds(); 

        UserActionRate& getUserHourlyActionRate(const std::string &userID);

        ObjectPreference& getUserObjectPreference(const std::string &userID); 

        UserDependency& getUserDependency(const std::string &userID);
};

#endif
