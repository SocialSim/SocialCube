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

        pair<double, double> pair = scales[i];
        int post_number = randomlyRoundDouble(pair.first);
        int post_scale = randomlyRoundDouble(pair.second);

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
            unique_ptr<Event> event(new Event(root_user_id, root_node_id, "post",
                                              root_node_id, root_node_id, current_day_time));
            events.push_back(move(event));

            vector<tuple<string, string, time_t>> current_layer =
                    {tuple<string, string, time_t>(root_node_id, root_user_id, current_day_time)};
            vector<tuple<string, string, time_t>> next_layer;

            // Create comment events
            while (!stop_flag) {
                for (auto& iter : current_layer) {
                    string parent_node_id = get<0>(iter);
                    string parent_user_id = get<1>(iter);
                    time_t parent_event_time = get<2>(iter);

                    CommentProbability comment_prob = m_statProxy.getCommentProbability(parent_user_id);
                    vector<std::pair<string, double>> commentProbability = comment_prob.getCommentProb();

                    for (auto& iter : commentProbability) {
                        string commenter_id = iter.first;
                        double comment_prob = iter.second;

                        double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

                        if (randnum < comment_prob) {
                            string node_id = generateNodeId();
                            time_t event_time;

                            if (event_counter < post_scale * 0.25) {
                                event_time = current_day_time + (int)(q1_end_time / (post_scale * 0.25) * event_counter);
                            } else if (event_counter < post_scale * 0.5) {
                                event_time = current_day_time + q1_end_time + (int)((q2_end_time - q1_end_time) / (post_scale * 0.25) * (event_counter - post_scale * 0.25));
                            } else if (event_counter < post_scale * 0.75) {
                                event_time = current_day_time + q2_end_time + (int)((q3_end_time - q2_end_time) / (post_scale * 0.25) * (event_counter - post_scale * 0.5));
                            } else {
                                event_time = current_day_time + q3_end_time + (int)((time_interval - q3_end_time) / (post_scale * 0.25) * (event_counter - post_scale * 0.75));
                            }

                            // If time excess end time, skip the creation of this event
                            if (event_time > t_endTime) {
                                stop_flag = true;
                                cout << "event_time > t_endTime" << endl;
                                break;
                            }

                            unique_ptr<Event> event(new Event(commenter_id, node_id, "comment", parent_node_id, root_node_id, event_time));
                            events.push_back(move(event));

                            next_layer.push_back(tuple<string, string, time_t>(node_id, commenter_id, event_time));

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

