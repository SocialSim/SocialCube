#include "NewUserModel.hpp"

using namespace std;

NewUserModel::NewUserModel() {
    return;
}

NewUserModel::~NewUserModel() {
    return;
}

vector<unique_ptr<Event>> NewUserModel::evaluate(const std::string t_infoId,
                                                             time_t t_startTime,
                                                             time_t t_endTime) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();
        
    cout << "t_infoId = " << t_infoId << endl;

    // Use embeddingParams ratio_root
    unordered_map<string, double> embeddingParams = m_statProxy.getEmbeddingParams();

    vector<unique_ptr<Event>> events;

    // Use seed posts instead
    CascadeSequence cascade_sequence = m_statProxy.getCascadeSequence(t_infoId);
    vector<PostInfo> posts = m_statProxy.getCascadeSequence(t_infoId).getPosts();

    // Get community distribution
    unordered_map<string, double> communityDistribution = m_statProxy.getCommunityDistribution(t_infoId);

    //vector<PostInfo> posts;

    // Create post/tweet event
    for (PostInfo p : posts) {
        string root_node_id = p.getPostId();
        //// root_user_id is determined by infoIDtoUserProxyFile.txt
        string root_user_id = m_statProxy.getUserByInfoID(t_infoId);
        time_t root_timestamp = p.getPostTimestamp();

        if (root_timestamp >= t_startTime && root_timestamp <= t_endTime) {
            unique_ptr<Event> post_event;
            // post in Twitter is called "tweet". EventManager will do the conversion
            post_event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "post",
                                                     root_node_id, root_node_id, root_timestamp));

            // Select community id
            string community_id;

            double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double sum = 0;
            for (auto &iter : communityDistribution) {
                sum += iter.second;
                if (randnum <= sum) {
                    community_id = iter.first;
                    break;
                }
            }

            post_event->setCommunityID(community_id);
            post_event->setInfoID(t_infoId);

            events.push_back(move(post_event));
        }

        vector<pair<string, time_t>> comments = p.getCommentSequence();

        unordered_map<string, string> user_comments;

        // Generate each comment/reply
        for (pair<string, time_t> c : comments) {
            // Generate user_id
            unique_ptr <Event> event;
            string user_id;
            string node_id = generateNodeId();
            string action_type = c.first;
            time_t timestamp = c.second;
            string parent_node_id;
            string parent_user_id;

            if (timestamp <= t_startTime || timestamp >= t_endTime) {
                continue;
            }

            //// Determine parent_id
            if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < embeddingParams["ratio_root"] ||
                    user_comments.size() == 0) {
                parent_node_id = root_node_id;
                parent_user_id = root_user_id;
            } else {
                int sum_of_followers = 0;
                for (const auto &comment : user_comments) {
                    sum_of_followers += m_statProxy.getNumberOfFollowersByTopology(comment.first);
                }
                int roll = rand() % sum_of_followers;
                int sum = 0;
                for (const auto &comment : user_comments) {
                    sum += m_statProxy.getNumberOfFollowersByTopology(comment.first);
                    if (sum >= roll) {
                        parent_node_id = comment.second;
                        parent_user_id = comment.first;
                        break;
                    }
                }
            }

            //// Determine user_id
//            if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < embeddingParams["ratio_infoIDToUser"]) {
//                user_id = m_statProxy.getUserByInfoID(t_infoId);
//                cout << "m_statProxy.getUserByInfoID: " << user_id << endl;
//            } else {
//                user_id = m_statProxy.getUserByTopology(parent_user_id);
//                cout << "m_statProxy.getUserByTopology: " << user_id << ", parent_user_id: " << parent_user_id << endl;
//            }
            user_id = m_statProxy.getUserByTopology(parent_user_id, t_infoId);

            // Select community id
            string community_id;

            double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double sum = 0;
            for (auto &iter : communityDistribution) {
                sum += iter.second;
                if (randnum <= sum) {
                    community_id = iter.first;
                    break;
                }
            }

            // Generate this comment event
            event = unique_ptr<Event>(new Event(user_id, node_id, action_type, parent_node_id, root_node_id));
            cout << user_id << ", " << node_id << ", " << action_type << ", " << parent_node_id << ", " << root_node_id << endl;
            event->setTime(timestamp);
            event->setCommunityID(community_id);
            event->setInfoID(t_infoId);

            events.push_back(move(event));
            user_comments[user_id] = node_id;
        }
    }

    return events;
}

string NewUserModel::generateNodeId() {
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    int len = 25;
    string nodeId = "";

    for (int i = 0; i < len; ++i) {
        nodeId += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return nodeId;
}
