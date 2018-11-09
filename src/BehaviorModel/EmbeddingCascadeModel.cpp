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

    double q1 = 0.09178669;
    double q2 = 0.18522102;
    double q3 = 0.32377755;

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
            unique_ptr <Event> event(new Event(root_user_id, root_node_id, "post",
                                               root_node_id, root_node_id, current_day_time));
            events.push_back(move(event));

            vector<pair<string, unique_ptr<Event>>> user_comments;

            for (int k = 0; k < post_scale; k++) {
                string node_id = generateNodeId();

                string user_id;
                double rand = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                if (rand < DELETED_USER) {
                    user_id = "[Deleted]";
                } else if (rand < UNKNOWN_USER) {
                    user_id = "UNK_COMM";
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

                if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < COMMENT_ROOT_PROB) {
                    unique_ptr<Event> event(new Event(user_id, node_id, "comment", root_node_id, root_node_id));
                    user_comments.push_back(std::make_pair(user_id, move(event)));
                } else {
                    int randnum = rand() % user_comments.size();
                    string parent_node_id = user_comments[randnum].first;
                    unique_ptr<Event> event(new Event(user_id, node_id, "comment", parent_node_id, root_node_id));
                    user_comments.push_back(std::make_pair(user_id, move(event)));
                }
            }

            // Reassign event time for each comment event
            int comment_num = user_comments.size();
            cout << "comment_num = " << comment_num << endl;
            for (int k = 0; k < comment_num; k++) {
                time_t event_time;
                if (k < comment_num * 0.25) {
                    event_time = current_day_time + (int) (q1_end_time / (comment_num * 0.25) * k);
                } else if (k < comment_num * 0.5) {
                    event_time = current_day_time + q1_end_time +
                                 (int) ((q2_end_time - q1_end_time) / (comment_num * 0.25) * (k - comment_num * 0.25));
                } else if (k < comment_num * 0.75) {
                    event_time = current_day_time + q2_end_time +
                                 (int) ((q3_end_time - q2_end_time) / (comment_num * 0.25) * (k - comment_num * 0.5));
                } else {
                    event_time = current_day_time + q3_end_time +
                                 (int) ((time_interval - q3_end_time) / (comment_num * 0.25) *
                                        (k - comment_num * 0.75));
                }
                if (event_time > t_endTime) {
                    cout << "event_time > t_endTime" << endl;
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

