#include "SeedCascadeSequenceModel.hpp"

using namespace std;

SeedCascadeSequenceModel::SeedCascadeSequenceModel() {
    return;
}

SeedCascadeSequenceModel::~SeedCascadeSequenceModel() {
    return;
}

vector<unique_ptr<Event>> SeedCascadeSequenceModel::evaluate(const std::string t_infoId,
                                                             ScoreMatrix& t_scoreMatrix,
                                                             time_t t_startTime,
                                                             time_t t_endTime) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();

    unordered_map<string, double> embeddingParams = m_statProxy.getEmbeddingParams();
    vector<unique_ptr<Event>> events;

    // Dumb is_twitter
    bool is_twitter = false;

    // Use seed posts instead
    CascadeSequence cascade_sequence = m_statProxy.getCascadeSequence(t_infoId);
    vector<PostInfo> posts = m_statProxy.getCascadeSequence(t_infoId).getPosts();

    cout << "start creating posts, post number = " << posts.size() << endl;

    //vector<PostInfo> posts;

    // Create post/tweet event
    for (PostInfo p : posts) {
        cout << "in the posts loop" << endl;
        string root_node_id = p.getPostId();
        string root_user_id = p.getUserId();
        time_t root_timestamp = p.getPostTimestamp();
        vector<pair<string, time_t>> comments = p.getCommentSequence();

        cout << "post_id: " << root_node_id << ", user_id: " << root_user_id << ", comment number: " << comments.size() << endl;

        unique_ptr<Event> post_event;
        if (!is_twitter) {
            post_event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "post",
                                                                       root_node_id, root_node_id, root_timestamp));
        } else {
            post_event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "tweet",
                                                                       root_node_id, root_node_id, root_timestamp));
        }

        // Randomly generate community
        post_event->setCommunityID("random_community");
        post_event->setInfoID(t_infoId);

        events.push_back(move(post_event));

        vector<pair<string, unique_ptr<Event>>> user_comments;

        // Generate each comment/reply
        for (pair<string, time_t> c : comments) {
            cout << "in the comments loop" << endl;
            // Generate user_id
            string user_id;
            // Current comment number
            int k = user_comments.size();

            double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

            if (randnum < embeddingParams["ratio_del"]) {
                user_id = "[Deleted]";
            } else if (randnum < embeddingParams["ratio_del"] + embeddingParams["ratio_unk"]) {
                user_id = t_scoreMatrix.randomlyGetInactiveUser();
            } else {
                vector<string> pre_user_list{root_user_id};
                for (int l = k - LOOK_BACK; l < k; l++) {
                    if (l < 0) {
                        pre_user_list.push_back("userID-none");
                    } else {
                        pre_user_list.push_back(user_comments[l].first);
                    }
                }
                user_id = t_scoreMatrix.getOutUser(pre_user_list);
            }

            cout << "Finish generating user_id" << endl;

            // Generate parent_id
            unique_ptr <Event> event;
            string node_id = generateNodeId();
            string action_type = c.first;
            time_t timestamp = c.second;
            string parent_node_id;

            if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < embeddingParams["ratio_root"]) {
                // parent_id = root_node_id
                cout << "randnum < ratio_root" << endl;
                event = unique_ptr<Event>(new Event(user_id, node_id, action_type, root_node_id, root_node_id));

                event->setCommunityID("random_community");
                event->setTime(timestamp);
                event->setInfoID(t_infoId);
                user_comments.push_back(std::make_pair(user_id, move(event)));
            } else {
                // parent_id != root_node_id
                cout << "user_id: " << user_id << endl;
                CommentProbability comment_prob = m_statProxy.getCommentProbability(user_id);
                vector <std::pair<string, double>> commentProbability = comment_prob.getCommentProb();
                cout << "commentProbability size = " << commentProbability.size() << endl;
//
//                if (user_comments.size() == 0) {
//                    parent_node_id = root_node_id;
//                }

                // NodeId : score
                unordered_map<string, double> parent_candidates;

                // Get the intersection between former commenters and predictable parent users
                for (auto &c_p : commentProbability) {
                    for (auto &u_c : user_comments) {
                        if (c_p.first == u_c.first) {
                            parent_candidates.insert(std::make_pair(u_c.second->getObjectID(), c_p.second));
                        }
                    }
                }

                if (parent_candidates.size() == 0) {
                    if (user_comments.size() == 0) {
                        parent_node_id = root_node_id;
                        cout << "parent_node_id = root_node_id, user_comments.size() == 0" << endl;
                    } else {
                        int randnum = rand() % user_comments.size();
                        parent_node_id = user_comments[randnum].second->getObjectID();
                        cout << "parent_node_id = user_comments[randnum].second->getObjectID();" << endl;
                    }
                } else if (parent_candidates.count("[root]")) {
                    cout << "parent_candidates.count(\"[root]\")" << endl;
                    parent_node_id = root_node_id;
                } else {
                    double sum = 0;
                    for (auto &iter : parent_candidates) {
                        sum += iter.second;
                    }
                    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                    double randnum_sum = 0;
                    for (auto &iter : parent_candidates) {
                        randnum_sum += iter.second / sum;
                        if (randnum <= randnum_sum) {
                            cout << "choose one from parent_candidates" << endl;
                            parent_node_id = iter.first;
                        }
                    }
                }

                event = unique_ptr<Event>(new Event(user_id, node_id, action_type, parent_node_id, root_node_id));
                event->setCommunityID("random_community");
                event->setInfoID(t_infoId);
                event->setTime(timestamp);
                user_comments.push_back(std::make_pair(user_id, move(event)));
            }
            cout << "Finish generating parent_id, user_id: " << user_id << ", node_id: " << node_id <<
                 ", action_type: " << action_type << ", parent_id: " << parent_node_id << ", root_id: " << root_node_id << endl;
        }


        // Push the events in "user_comments" into "events"
        for (int i = 0; i < user_comments.size(); i++) {
            events.push_back(move(user_comments[i].second));
        }
        cout << "Push comments back to events" << endl;
    }

    return events;
}

int SeedCascadeSequenceModel::randomlyRoundDouble(double num) {
    double float_part = num - (int) num;
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    if (randnum <= float_part) {
        return (int) num + 1;
    } else {
        return (int) num;
    }
}

string SeedCascadeSequenceModel::generateNodeId() {
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

int SeedCascadeSequenceModel::convertISOtoDay(time_t t_currentTime) {
    return int(t_currentTime / (24 * 60 * 60));
}

double SeedCascadeSequenceModel::generateGaussianRandom() {
    // gaussian random number generator
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, 10.0);
    return distribution(generator);
}
