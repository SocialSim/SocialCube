#ifndef __STATISTIC_PROXY__
#define __STATISTIC_PROXY__

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <memory>
#include "Dependency/HourlyActionRate.hpp"
#include "Dependency/ObjectPreference.hpp"
#include "Dependency/PointProcessStat.hpp"
#include "Dependency/DailyActivityLevel.hpp"
#include "Dependency/PoissonProcessStat.hpp"
#include "StatisticProxy/UserIDProxy/UserIDProxy.hpp"
#include "StatisticProxy/UserIDProxy/ClusteredUserIDProxy.hpp"
#include "StatisticProxy/ObjectIDProxy/ObjectIDProxy.hpp"
#include "StatisticProxy/ObjectPreferenceProxy/ObjectPreferenceProxy.hpp"
#include "StatisticProxy/HourlyActionRateProxy/HourlyActionRateProxy.hpp"
#include "StatisticProxy/DailyActivityLevelProxy/DailyActivityLevelProxy.hpp"
#include "StatisticProxy/TypeDistributionProxy/TypeDistributionProxy.hpp"
#include "StatisticProxy/PointProcessProxy/PointProcessProxy.hpp"
#include "StatisticProxy/PoissonProcessProxy/PoissonProcessProxy.hpp"
#include "StatisticProxy/UserDistributionProxy/UserDistributionProxy.hpp"

class StatisticProxy {
    private:
        static const std::unordered_map<std::string, std::string> m_event_types;

        std::string m_defaultUserIDProxyFile;
        std::string m_defaultObjectIDProxyFile;
        std::string m_defaultObjectPreferenceProxyFile;
        std::string m_defaultHourlyActionRateProxyFile;
        std::string m_defaultDailyActivityLevelProxyFile;
        std::string m_defaultTypeDistributionProxyFile;
        std::string m_defaultUserDistributionProxyFile;
        std::string m_defaultPointProcessStatsProxyFile;
        std::string m_defaultPoissonProcessStatsProxyFile;
        std::unordered_map<std::string, std::string> m_defaultClassifiedUserDistributionProxyFiles;

    private:
        std::unique_ptr<UserIDProxy> m_userIDProxy;
        std::unique_ptr<ObjectIDProxy> m_objectIDProxy;
        std::unique_ptr<ObjectPreferenceProxy> m_objectPreferenceProxy;
        std::unique_ptr<HourlyActionRateProxy> m_hourlyActionRateProxy;
        std::unique_ptr<DailyActivityLevelProxy> m_dailyActivityLevelProxy;
        std::unique_ptr<TypeDistributionProxy> m_typeDistributionProxy;
        std::unique_ptr<UserDistributionProxy> m_userDistributionProxy;
        std::unique_ptr<PointProcessProxy> m_pointProcessProxy;
        std::unique_ptr<PoissonProcessProxy> m_poissonProcessProxy;
        std::unordered_map<std::string, std::unique_ptr<UserDistributionProxy>> m_classifiedUserDistributionProxies;

        // Private member functions
        StatisticProxy();

    public:

        ~StatisticProxy();
        
        static StatisticProxy& getInstance();

        void initProxySourceFile();

        void parseUserID();
        void parseObjectID();
        void parseObjectPreference();
        void parseHourlyActionRate();
        void parseDailyActivityLevel();
        void parseTypeDistribution();
        void parseUserDistribution();
        void parsePointProcessStats();
        void parsePoissonProcessStats();
        void parseClassifiedUserDistributionStats();

        void setUserIDProxyFilePath(std::string userIDProxyFilePath);
        void setObjectIDProxyFilePath(std::string objectIDProxyFilePath);
        void setHourlyActionRateProxyFilePath(std::string hourlyActionRateProxyFilePath);
        void setDailyActivityLevelProxyFilePath(std::string activityLevelProxyFilePath);
        void setObjectPreferenceProxyFilePath(std::string objectPreferenceProxyFilePath);
        void setTypeDistributionProxyFilePath(std::string typeDistributionProxyFilePath);
        void setUserDistributionProxyFilePath(std::string userDistributionProxyFilePath);
        void setPointProcessStatsProxyFilePath(std::string pointProcessProxyFilePath);
        void setPoissonProcessStatsProxyFilePath(std::string poissonProcessProxyFilePath);
        void setClassifiedUserDistributionProxyFiles(std::string eventType, std::string path);

        void setCommitCommentEventUserDistributionProxyFilePath(std::string path);
        void setDeleteEventUserDistributionProxyFilePath(std::string path);
        void setIssueCommentEventUserDistributionProxyFilePath(std::string path);
        void setPullRequestEventUserDistributionProxyFilePath(std::string path);
        void setPushEventUserDistributionProxyFilePath(std::string path);
        void setCreateEventUserDistributionProxyFilePath(std::string path);
        void setForkEventUserDistributionProxyFilePath(std::string path);
        void setIssueEventUserDistributionProxyFilePath(std::string path);
        void setPullRequestReviewCommentEventUserDistributionProxyFile(std::string path);
        void setWatchEventUserDistributionProxyFile(std::string path);

        void retrieveStatistics();

        std::vector<std::string>& getUserIDs() const;

        std::vector<std::string>& getObjectIDs() const; 

        HourlyActionRate& getUserHourlyActionRate(const std::string &userID) const;

        DailyActivityLevel& getDailyActivityLevel(const string &userID) const;

        ObjectPreference& getUserObjectPreference(const std::string &userID) const; 

        TypeDistribution& getUserTypeDistribution(const std::string &userID) const; 

        UserDistribution& getRepoUserDistribution(const std::string &repoID) const;

        PointProcessStat& getPointProcessStats(const std::string &repoID) const;

        PoissonProcessStat& getPoissonProcessStats(const std::string &repoID) const;

        UserDistribution& getClassifiedUserTypeDistribution(const std::string &event_type, const std::string &repoID);

        std::vector<std::string> getEventTypes() const;

    uint64_t getUserCommunityTag(const std::string &userID) const;
};

#endif
