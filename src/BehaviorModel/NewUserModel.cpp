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

    // Use embeddingParams ratio_root
    unordered_map<string, double> embeddingParams = m_statProxy.getEmbeddingParams();

    cout << "root_ratio: " << embeddingParams["ratio_root"] << endl;

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

        vector<pair<string, unique_ptr<Event>>> user_comments;

        vector<string> previous_users;
        previous_users.push_back(root_user_id);

        // Generate each comment/reply
        for (pair<string, time_t> c : comments) {
            // Generate user_id
            unique_ptr <Event> event;
            string user_id;
            string node_id = generateNodeId();
            string action_type = c.first;
            time_t timestamp = c.second;
            string parent_node_id;

            if (timestamp <= t_startTime || timestamp >= t_endTime) {
                continue;
            }

            if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < embeddingParams["ratio_root"]) {
                user_id = m_statProxy.getUserByInfoID(t_infoId);
                event = unique_ptr<Event>(new Event(user_id, node_id, action_type, root_node_id, root_node_id));
                event->setTime(timestamp);
            } else {
                string last_user = previous_users.back();
                user_id = m_statProxy.getUserByTopology(last_user);
                event = unique_ptr<Event>(new Event(user_id, node_id, action_type, last_user, root_node_id));
                event->setTime(timestamp);
            }

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

            event->setCommunityID(community_id);
            event->setInfoID(t_infoId);

            events.push_back(move(event));
            previous_users.push_back(user_id);

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
