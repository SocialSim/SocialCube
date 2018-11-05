#include "CascadeModel.hpp"

using namespace std;

CascadeModel::CascadeModel() {
    return;
}

CascadeModel::~CascadeModel() {
    return;
}

vector<unique_ptr<Event>> CascadeModel::evaluate(const string t_id,
                                                      PostScale& t_postScale,
                                                      PostLifespanDistribution& t_postLifespanDistribution,
                                                      time_t t_startTime,
                                                      time_t t_endTime) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();
    vector<unique_ptr<Event>> events;
    
    int startDay = CascadeModel::convertISOtoDay(t_startTime);
    int endDay = CascadeModel::convertISOtoDay(t_endTime);

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
        int post_scale = 1000;

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

            vector <pair<string, string>> current_layer =
                    {pair<string, string>(root_node_id, root_user_id)};
            vector <pair<string, string>> next_layer;

            vector <unique_ptr<Event>> post_comments;

            // Create comment events
            while (!stop_flag) {
                for (auto &iter : current_layer) {
                    string parent_node_id = iter.first;
                    string parent_user_id = iter.second;

                    CommentProbability comment_prob = m_statProxy.getCommentProbability(parent_user_id);
                    vector <std::pair<string, double>> commentProbability = comment_prob.getCommentProb();

                    for (auto &iter : commentProbability) {
                        string commenter_id = iter.first;
                        double comment_prob = iter.second;

                        double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

                        if (randnum < comment_prob) {
                            string node_id = generateNodeId();
                            unique_ptr <Event> event(
                                    new Event(commenter_id, node_id, "comment", parent_node_id, root_node_id));

                            post_comments.push_back(move(event));

                            next_layer.push_back(pair<string, string>(node_id, commenter_id));

                            if (++event_counter > post_scale) {
                                stop_flag = true;
                                cout << "++event_counter > post_scale" << endl;
                                break;
                            }
                        }
                    }
                    if (stop_flag) {
                        break;
                    }
                }
                if (next_layer.size() == 0) {
                    cout << "next_layer.size() == 0" << endl;
                    break;
                }
                current_layer.clear();
                copy(next_layer.begin(), next_layer.end(), back_inserter(current_layer));
                next_layer.clear();
            }
            // Reassign event time for each comment event
            int comment_num = post_comments.size();
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
                post_comments[k]->setTime(event_time);
                events.push_back(move(post_comments[k]));
            }
        }
    }
    return events;
}

int CascadeModel::randomlyRoundDouble(double num) {
    double float_part = num - (int) num;
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    if (randnum <= float_part) {
        return (int) num + 1;
    } else {
        return (int) num;
    }
}

int CascadeModel::generateLifespan(PostLifespanDistribution& t_postLifespanDistribution) {
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

string CascadeModel::generateNodeId() {
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

int CascadeModel::convertISOtoDay(time_t t_currentTime) {
    return int(t_currentTime / (24 * 60 * 60));
}

