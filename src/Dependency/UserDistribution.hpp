#ifndef __USER_DISTRIBUTION__
#define __USER_DISTRIBUTION__

#include <unordered_map>
#include <vector>
#include <map>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <cassert>
#include <string>

class UserDistribution {

private:
    std::string m_repoID;

    std::map<time_t, int> totalCount;

    std::unordered_map<time_t, std::unordered_map<std::string, int>> m_userCount;

public:

    UserDistribution(std::string t_repoID);

    ~UserDistribution();

    void insertUserCount(time_t date, std::string userID, int count);

    std::unordered_map<time_t, std::unordered_map<std::string, int>> getUserDistribution();

    std::vector<std::string> getShuffledUserIDs(time_t date);

    int getTotalCount(time_t date);

    void show();
};

#endif
