#ifndef __STATISTIC_PROXY__
#define __STATISTIC_PROXY__

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "Dependency/HourlyActionRate.hpp"
#include "Dependency/ObjectPreference.hpp"
#include "StatisticProxy/UserIDProxy/UserIDProxy.hpp"
#include "StatisticProxy/ObjectIDProxy/ObjectIDProxy.hpp"
#include "StatisticProxy/ObjectPreferenceProxy/ObjectPreferenceProxy.hpp"
#include "StatisticProxy/HourlyActionRateProxy/HourlyActionRateProxy.hpp"

class StatisticProxy {

    private:
        std::unique_ptr<UserIDProxy> m_userIDProxy;
        std::unique_ptr<ObjectIDProxy> m_objectIDProxy;
        std::unique_ptr<ObjectPreferenceProxy> m_objectPreferenceProxy;
        std::unique_ptr<HourlyActionRateProxy> m_hourlyActionRateProxy;

        // Private member functions
        StatisticProxy();

    public:

        ~StatisticProxy();
        
        static StatisticProxy& getInstance();

        void retrieveStatistics();

        std::vector<std::string>& getUserIds();

        std::vector<std::string>& getObjectIds(); 

        HourlyActionRate& getUserHourlyActionRate(const std::string &userID);

        ObjectPreference& getUserObjectPreference(const std::string &userID); 
};

#endif
