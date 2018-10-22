#include "CascadeModel.hpp"

using namespace std;

CascadeModel::CascadeModel() {
    return;
}

CascadeModel::~CascadeModel() {
    return;
}

std::vector<unique_ptr<Event>> CascadeModel::evaluate(const std::string t_id,
                                                      PostScale& t_postScale,
                                                      PostLifespanDistribution& t_postLifespanDistribution,
                                                      CommentProbabilityProxy& t_commentProbabilityProxy,

                                                      time_t t_startTime,
                                                      time_t t_endTime) {
    vector<unique_ptr<Event>> events;

    int startDay = DailySimpleBehaviorModel::convertISOtoDay(t_startTime);
    int endDay = DailySimpleBehaviorModel::convertISOtoDay(t_endTime);

    vector<pair<int, int>> scales = t_postScale.getScale();

    if (endDay - startDay > scales.size()) {
        TimeSpanExceedException h_e;
        throw h_e;
    }


    for (int i = 0; i <= endDay - startDay; i++) {
        time_t current_day_time = t_startTime + i * 24 * 60 * 60;

        pair<int, int> pair = scales[i];
        int post_number = pair.first;
        int post_scale = pair.second;

        for (int j = 0; j < post_number; j++) {
            int lifespan = generateLifespan(t_postLifespanDistribution);

            string node_id = generateNodeId();
            string root_node_id = node_id;
            string parent_node_id = root_node_id;
            string current_user_id = t_id;
            string last_user_id = t_id;

            time_t time_interval = current_day_time - t_startTime;
            for (int k = 0; k < post_scale + 1; k++) {
                time_t eventTime = current_day_time + (time_interval / (post_scale - 1)) * k;

                if (eventTime > t_endTime) {
                    break;
                }

                // Post
                if (k == 0) {
                    unique_ptr<Event> event(new Event(t_id, node_id, "post", parent_node_id, root_node_id, eventTime));
                    events.push_back(move(event));
                } else {
                    CommentProbability comment_prob = t_commentProbabilityProxy.get(last_user_id);
                    current_user_id = generateCommentUser(comment_prob);

                    node_id = generateNodeId();

                    unique_ptr<Event> event(new Event(current_user_id, node_id, "comment", parent_node_id, root_node_id, eventTime));
                    events.push_back(move(event));
                }

                last_user_id = current_user_id;
                parent_node_id = node_id;
            }
        }
    }

    return events;
}

int CascadeModel::generateLifespan(const PostLifespanDistribution& t_postLifespanDistribution) {
    vector<pair<int, double>> lifespanDistribution = t_postLifespanDistribution.getLifespanDist();

    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double accum_prob = 0;
    for (auto& iter : lifespanDistribution) {
        accum_prob += iter.second;
        if (accum_prob <= randnum) {
            return iter.first;
        }
    }
    return lifespanDistribution.back();
}

string CascadeModel::generateCommentUser(const CommentProbability& t_commentProbability) {
    vector<std::pair<std::string, double>> commentProbability = t_commentProbability.getCommentProb();
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double accum_prob = 0;
    for (auto& iter : commentProbability) {
        accum_prob += iter.second;
        if (accum_prob <= randnum) {
            return iter.first;
        }
    }
    return commentProbability.back();
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

