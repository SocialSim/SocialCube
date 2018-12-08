#include "EmbeddingCascadeModel.hpp"

using namespace std;

EmbeddingCascadeModel::EmbeddingCascadeModel() {
    return;
}

EmbeddingCascadeModel::~EmbeddingCascadeModel() {
    return;
}

vector<unique_ptr<Event>> EmbeddingCascadeModel::evaluate(const string t_id,
                                                 PostScale& t_postScale,
                                                 PostLifespanDistribution& t_postLifespanDistribution,
                                                 unordered_map<string, double> t_communityDistribution,
                                                 ScoreMatrix& t_scoreMatrix,
                                                 time_t t_startTime,
                                                 time_t t_endTime) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();
    vector<unique_ptr<Event>> events;

    int startDay = EmbeddingCascadeModel::convertISOtoDay(t_startTime);
    int endDay = EmbeddingCascadeModel::convertISOtoDay(t_endTime);

    vector<pair<double, double>> scales = t_postScale.getScale();

    if (endDay - startDay > scales.size()) {
        TimeSpanExceedException h_e;
        throw h_e;
    }

    double* quartiles = m_statProxy.getQuartile();
    double q1 = quartiles[0];
    double q2 = quartiles[1];
    double q3 = quartiles[2];

    unordered_map<string, double> actionTypeDistribution = m_statProxy.getActionTypeDistribution();

    unordered_map<string, double> embeddingParams = m_statProxy.getEmbeddingParams();

    bool is_twitter = false;
    if (actionTypeDistribution.size() == 3) {
        is_twitter = true;
    }

    for (int i = 0; i <= endDay - startDay; i++) {
        time_t current_day_time = t_startTime + i * 24 * 60 * 60;

        int post_number = randomlyRoundDouble(scales[i].first);
        int post_scale = randomlyRoundDouble(scales[i].second);

        for (int j = 0; j < post_number; j++) {
            int lifespan = generateLifespan(t_postLifespanDistribution);
            time_t time_interval = lifespan * 24 * 60 * 60 - 1;
            time_t q1_end_time = time_interval * q1;
            time_t q2_end_time = time_interval * q2;
            time_t q3_end_time = time_interval * q3;

            string root_node_id = generateNodeId();
            string root_user_id = t_id;

            int event_counter = 1;
            bool stop_flag = false;

            // Create post event
            unique_ptr <Event> event;

            vector<double> postHourDistribution = m_statProxy.getPostHourDistribution();
            time_t post_time = current_day_time;

            double randnum_postHour = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double sum_postHour = 0;
            for (int i = 0; i < postHourDistribution.size(); i++) {
                sum_postHour += postHourDistribution[i];
                if (randnum_postHour <= sum_postHour) {
                    post_time = post_time + i * 60 * 60;
                }
            }

            if (!is_twitter) {
                event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "post",
                                                    root_node_id, root_node_id, post_time));
            } else {
                event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "tweet",
                                                    root_node_id, root_node_id, post_time));
            }
            string community_id;
            // Set community ID
            double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double sum = 0;
            for (auto &iter : t_communityDistribution) {
                sum += iter.second;
                if (randnum <= sum) {
                    community_id = iter.first;
                    break;
                }
            }
            event->setCommunityID(community_id);
            events.push_back(move(event));

            vector<pair<string, unique_ptr<Event>>> user_comments;

            for (int k = 0; k < post_scale; k++) {
                string node_id = generateNodeId();

                string user_id;
                double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                if (randnum < embeddingParams["ratio_del"]) {
                    user_id = "[Deleted]";
                } else if (randnum < embeddingParams["ratio_del"] + embeddingParams["ratio_unk"]) {
                    // Based on commentProb
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

                if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < embeddingParams["ratio_root"]) {
                    unique_ptr <Event> event;
                    string actionType = "reply";
                    if (is_twitter) {
                        double randnum_actionType = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                        double sum_actionType = 0;
                        for (auto &iter : actionTypeDistribution) {
                            sum_actionType += iter.second;
                            if (randnum_actionType <= sum_actionType) {
                                actionType = iter.first;
                                break;
                            }
                        }
                        event = unique_ptr<Event>(new Event(user_id, node_id, actionType, root_node_id, root_node_id));
                    } else {
                        event = unique_ptr<Event>(new Event(user_id, node_id, "comment", root_node_id, root_node_id));
                    }

                    event->setCommunityID(community_id);
                    user_comments.push_back(std::make_pair(user_id, move(event)));
                } else {
                    CommentProbability comment_prob = m_statProxy.getCommentProbability(user_id);
                    vector <std::pair<string, double>> commentProbability = comment_prob.getCommentProb();
                    string parent_node_id;

                    if (user_comments.size() == 0) {
                        parent_node_id = root_node_id;
                    }

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
                        } else {
                            int randnum = rand() % user_comments.size();
                            parent_node_id = user_comments[randnum].second->getObjectID();
                        }
                    } else if (parent_candidates.count("[root]")) {
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
                                parent_node_id = iter.first;
                            }
                        }
                    }

                    unique_ptr <Event> event;
                    string actionType = "reply";
                    if (is_twitter) {
                        double randnum_actionType = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                        double sum_actionType = 0;
                        for (auto &iter : actionTypeDistribution) {
                            sum_actionType += iter.second;
                            if (randnum_actionType <= sum_actionType) {
                                actionType = iter.first;
                                break;
                            }
                        }
                        event = unique_ptr<Event>(new Event(user_id, node_id, actionType, parent_node_id, root_node_id));
                    } else {
                        event = unique_ptr<Event>(new Event(user_id, node_id, "comment", parent_node_id, root_node_id));
                    }
                    event->setCommunityID(community_id);
                    user_comments.push_back(std::make_pair(user_id, move(event)));
                }
            }

            // Reassign event time for each comment event
            int comment_num = user_comments.size();
            for (int k = 0; k < comment_num; k++) {
                time_t event_time;
                if (k < comment_num * 0.25) {
                    event_time = post_time + (int) (q1_end_time / (comment_num * 0.25) * k);
                } else if (k < comment_num * 0.5) {
                    event_time = post_time + q1_end_time +
                                 (int) ((q2_end_time - q1_end_time) / (comment_num * 0.25) * (k - comment_num * 0.25));
                } else if (k < comment_num * 0.75) {
                    event_time = post_time + q2_end_time +
                                 (int) ((q3_end_time - q2_end_time) / (comment_num * 0.25) * (k - comment_num * 0.5));
                } else {
                    event_time = post_time + q3_end_time +
                                 (int) ((time_interval - q3_end_time) / (comment_num * 0.25) *
                                        (k - comment_num * 0.75));
                }
                event_time += generateGaussianRandom();
                if (event_time > t_endTime) {
                    break;
                }
                user_comments[k].second->setTime(event_time);
                events.push_back(move(user_comments[k].second));
            }
        }
    }
    return events;
}

int EmbeddingCascadeModel::randomlyRoundDouble(double num) {
    double float_part = num - (int) num;
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    if (randnum <= float_part) {
        return (int) num + 1;
    } else {
        return (int) num;
    }
}

int EmbeddingCascadeModel::generateLifespan(PostLifespanDistribution& t_postLifespanDistribution) {
    vector<pair<int, double>> lifespanDistribution = t_postLifespanDistribution.getLifespanDist();
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double accum_prob = 0;
    for (auto& iter : lifespanDistribution) {
        accum_prob += iter.second;
        if (accum_prob >= randnum) {
            return iter.first;
        }
    }
    return lifespanDistribution.back().first;
}

string EmbeddingCascadeModel::generateNodeId() {
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

int EmbeddingCascadeModel::convertISOtoDay(time_t t_currentTime) {
    return int(t_currentTime / (24 * 60 * 60));
}

double EmbeddingCascadeModel::generateGaussianRandom() {
    // gaussian random number generator
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, 10.0);
    return distribution(generator);
}

