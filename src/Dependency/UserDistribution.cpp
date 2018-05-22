#include "UserDistribution.hpp"

using namespace std;

UserDistribution::UserDistribution(std::string t_repoID) : m_repoID(t_repoID) {
    return;
}

UserDistribution::~UserDistribution() {
    return;
}

void UserDistribution::insertUserCount(time_t date, std::string userID, int count) {
    m_userCount[date][userID] = count;
    totalCount[date] += count;
}

std::unordered_map<time_t, std::unordered_map<std::string, int>> UserDistribution::getUserDistribution() {
    return move(m_userCount);
}

std::vector<std::string> UserDistribution::getShuffledUserIDs(time_t date) {
    vector<string> userIDs;
    for (auto& iter : m_userCount) {
        if (iter.first >= date && difftime(iter.first, date) < 7*24*60*60) {
            for (auto& u : iter.second) {
                vector<string> tmp(u.second, u.first);
                move(tmp.begin(), tmp.end(), back_inserter(userIDs));
            }
        }
    }
    random_shuffle(userIDs.begin(), userIDs.end());
    cout << "userIDs: " << endl;
    for (auto& iter : userIDs) {
        cout << iter << ", ";
    }
    cout << endl;
    return userIDs;
}

void UserDistribution::show() {
    cout << "-----------repoID: " << m_repoID << "------------" << endl;
    for(auto& i : m_userCount) {
        cout << "Date: " << ctime(&i.first) << ", totalCount = " << totalCount[i.first] << endl;
        for (auto& j : i.second) {
            cout << j.first << ": " << j.second << endl;
        }
    }
}

int UserDistribution::getTotalCount(time_t date) {
    // Find out the latest
    for (auto& iter : totalCount) {
        if (iter.first >= date && difftime(iter.first, date) < 7*24*60*60) {
            cout << "difftime(date, iter.first) = " << difftime(iter.first, date) << ", 7*24*60*60 = " << 7*24*60*60 << endl;
            return totalCount[iter.first];
        }
    }
    return 0;
}
