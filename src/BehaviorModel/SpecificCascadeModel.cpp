#include "SpecificCascadeModel.hpp"

using namespace std;

SpecificCascadeModel::SpecificCascadeModel() {
    return;
}

SpecificCascadeModel::~SpecificCascadeModel() {
    return;
}

vector<unique_ptr<Event>> SpecificCascadeModel::evaluate(const string t_id,
                                                      PostScale& t_postScale,
                                                      PostBreadthDistribution& t_postBreadthDistribution,
                                                      unordered_map<string, double> t_communityDistribution,
                                                      time_t t_startTime,
                                                      time_t t_endTime) {
    StatisticProxy& m_statProxy = StatisticProxy::getInstance();
    vector<unique_ptr<Event>> events;
    
    int startDay = SpecificCascadeModel::convertISOtoDay(t_startTime);
    int endDay = SpecificCascadeModel::convertISOtoDay(t_endTime);

    vector<pair<double, double>> scales = t_postScale.getScale();

    if (endDay - startDay > scales.size()) {
        TimeSpanExceedException h_e;
        throw h_e;
    }

    for (int i = 0; i <= endDay - startDay; i++) {
        time_t current_day_time = t_startTime + i * 24 * 60 * 60;

        int post_number = (int)scales[i].first;
        int post_scale = 1000;

        for (int j = 0; j < post_number; j++) {
            int breadth = generateBreadth(t_postBreadthDistribution);

            string root_node_id = generateNodeId();
            string root_user_id = t_id;

            int event_counter = 1;
            bool stop_flag = false;

            // Create post event
            unique_ptr <Event> event;
            event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "tweet", root_node_id, root_node_id, current_day_time));

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

            vector <pair<string, string>> current_layer =
                    {pair<string, string>(root_node_id, root_user_id)};
            vector <pair<string, string>> next_layer;

            vector <unique_ptr<Event>> post_comments;

            // Create response events
            // cout << "COMMENTS FOR USER: " << root_user_id << endl;
            if (breadth > 0) {
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
                                // cout << "Scanning user " << commenter_id << endl; 
                                PostLifespanDistribution lifespan_dist = m_statProxy.getPostLifespanDistribution(commenter_id);
                                int lifespan = generateLifespan(lifespan_dist);

                                // cout << "Lifespan " << lifespan << endl;

                                SpecificResponseDistribution response_dist = m_statProxy.getSpecificResponseDistribution(commenter_id);
                                string response_type = generateSpecificResponse(response_dist);

                                // cout << "Response type " << response_type << endl;

                                int hours = rand() % 24;
                                int minutes = rand() % 60;
                                int seconds = rand() % 60;
                                time_t eventTime = current_day_time + (lifespan * 86400) + (hours * 60 + minutes) * 60 + seconds;

                                string node_id = generateNodeId();
                                unique_ptr <Event> event;
                                event = unique_ptr<Event>(new Event(commenter_id, node_id, response_type, parent_node_id, root_node_id, eventTime));
                                event->setCommunityID(community_id);
                                post_comments.push_back(move(event));

                                next_layer.push_back(pair<string, string>(node_id, commenter_id));

                                if (++event_counter > breadth) {
                                    // cout << event_counter << " > " << breadth << endl;
                                    stop_flag = true;   
                                    break;
                                }
                            }                           
                        }
                        if (stop_flag) {
                            break;
                        }
                    }
                    if (next_layer.size() == 0) {
                        // cout << "next_layer.size() == 0" << endl;
                        break;
                    }
                    current_layer.clear();
                    copy(next_layer.begin(), next_layer.end(), back_inserter(current_layer));
                    next_layer.clear();
                }
            }
            int comment_num = post_comments.size();
            for (int k = 0; k < comment_num; k++) {
                events.push_back(move(post_comments[k]));
            }
        }
    }
    return events;
}

int SpecificCascadeModel::randomlyRoundDouble(double num) {
    double float_part = num - (int) num;
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    if (randnum <= float_part) {
        return (int) num + 1;
    } else {
        return (int) num;
    }
}

int SpecificCascadeModel::generateBreadth(PostBreadthDistribution& t_postBreadthDistribution) {
    vector<pair<int, double>> breadthDistribution = t_postBreadthDistribution.getBreadthDist();
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double accum_prob = 0;
    for (auto& iter : breadthDistribution) {
        accum_prob += iter.second;
        if (accum_prob >= randnum) {
            return iter.first;
        }
    }
    return breadthDistribution.back().first;
}

int SpecificCascadeModel::generateLifespan(PostLifespanDistribution& t_postLifespanDistribution) {
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

string SpecificCascadeModel::generateSpecificResponse(SpecificResponseDistribution& t_specificResponseDistribution) {
    vector<pair<string, double>> responseDistribution = t_specificResponseDistribution.getResponseDist();
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double accum_prob = 0;
    for (auto& iter : responseDistribution) {
        accum_prob += iter.second;
        if (accum_prob >= randnum) {
            return iter.first;
        }
    }
    return responseDistribution.back().first;
}

string SpecificCascadeModel::chooseResponseType(vector <string> &responseTypes, vector <double> &responseProbabilities) {
    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double accum_prob = 0;
    int count = 0;
    for (auto& iter : responseProbabilities) {
        accum_prob += iter;
        if (accum_prob >= randnum) {
            return responseTypes[count];
        }
        count++;
    }
    return responseTypes[0];
}

string SpecificCascadeModel::generateNodeId() {
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

int SpecificCascadeModel::convertISOtoDay(time_t t_currentTime) {
    return int(t_currentTime / (24 * 60 * 60));
}

// NOTE: Below is the SpecificCascadeModel version that does not have any layers for parent-child simulations.
// NOTE: However, this version takes an extremely long time to load and may be stuck in some kind of loop. Requires further investiagation.
// #include "SpecificCascadeModel.hpp"

// using namespace std;

// SpecificCascadeModel::SpecificCascadeModel() {
//     return;
// }

// SpecificCascadeModel::~SpecificCascadeModel() {
//     return;
// }

// vector<unique_ptr<Event>> SpecificCascadeModel::evaluate(const string t_id,
//                                                       PostScale& t_postScale,
//                                                       PostBreadthDistribution& t_postBreadthDistribution,
//                                                       unordered_map<string, double> t_communityDistribution,
//                                                       time_t t_startTime,
//                                                       time_t t_endTime) {
//     StatisticProxy& m_statProxy = StatisticProxy::getInstance();
//     vector<unique_ptr<Event>> events;
    
//     int startDay = SpecificCascadeModel::convertISOtoDay(t_startTime);
//     int endDay = SpecificCascadeModel::convertISOtoDay(t_endTime);

//     vector<pair<double, double>> scales = t_postScale.getScale();

//     if (endDay - startDay > scales.size()) {
//         TimeSpanExceedException h_e;
//         throw h_e;
//     }

//     for (int i = 0; i <= endDay - startDay; i++) {
//         time_t current_day_time = t_startTime + i * 24 * 60 * 60;

//         int post_number = (int)scales[i].second;
//         int post_scale = 1000;

//         for (int j = 0; j < post_number; j++) {
//             int breadth = generateBreadth(t_postBreadthDistribution);

//             string root_node_id = generateNodeId();
//             string root_user_id = t_id;

//             int event_counter = 1;
//             int iterator = 0;
//             bool stop_flag = false;

//             // Create post event
//             unique_ptr <Event> event;
//             event = unique_ptr<Event>(new Event(root_user_id, root_node_id, "tweet", root_node_id, root_node_id, current_day_time));

//             string community_id;
//             // Set community ID
//             double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//             double sum = 0;
//             for (auto &iter : t_communityDistribution) {
//                 sum += iter.second;
//                 if (randnum <= sum) {
//                     community_id = iter.first;
//                     break;
//                 }
//             }
//             event->setCommunityID(community_id);
//             events.push_back(move(event));

//             vector <unique_ptr<Event>> post_comments;

//             // Create response events
//             // cout << "COMMENTS FOR USER: " << root_user_id << endl;
//             if (breadth > 0) {
//                 while (!stop_flag) {
//                     string parent_node_id = root_node_id;
//                     string parent_user_id = root_user_id;

//                     ResponseTypeProbability response_type_prob_collective = m_statProxy.getResponseTypeProbability(parent_user_id);
//                     vector <string> responseTypeProbabilityCollective = response_type_prob_collective.getResponseTypeProb();

//                     vector <string> responseIDs;
//                     vector <vector <string> > responseTypes;
//                     vector <vector <double> > responseProbabilities;
//                     int user_count = -1;
//                     int prob_count = 0;
//                     int type_count = 0;
//                     for (auto & element : responseTypeProbabilityCollective) {
//                         if (element[0] == '#') {
//                             responseIDs.push_back(element);
//                             responseProbabilities.push_back({0.0, 0.0, 0.0});
//                             responseTypes.push_back({"retweet", "reply", "quote"});
//                             user_count++;
//                             prob_count = 0;
//                             type_count = 0;
//                         } else if (element == "retweet" || element == "reply" || element == "quote") {
//                             responseTypes[user_count][type_count] = element;
//                             type_count++;
//                         } else {
//                             double prob = stod(element);
//                             responseProbabilities[user_count][prob_count] = prob;
//                             prob_count++;
//                         }
//                     }

//                     vector <int> indexes;
//                     indexes.reserve(responseIDs.size());
//                     for (int i = 0; i < responseIDs.size(); ++i) {
//                         indexes.push_back(i);
//                     }
//                     random_shuffle(indexes.begin(), indexes.end());

//                     for (int i = 0; i < indexes.size(); i++) {
//                         iterator++;
//                         string commenter_id = responseIDs[indexes[i]];
//                         commenter_id.replace(0,1,"");

//                         // cout << commenter_id << ": ~" << responseTypes[indexes[i]][0] << "~ " << responseProbabilities[indexes[i]][0] << " ~" << responseTypes[indexes[i]][1] << "~ " << responseProbabilities[indexes[i]][1] << " ~" << responseTypes[indexes[i]][2] << "~ " << responseProbabilities[indexes[i]][2] << endl;
//                         for (int j = 0; j < responseProbabilities[indexes[i]].size(); j++) {
//                             double comment_prob = responseProbabilities[indexes[i]][j];
//                             string response_type = responseTypes[indexes[i]][j];

//                             double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//                             if (randnum < comment_prob) {                                
//                                 PostLifespanDistribution lifespan_dist = m_statProxy.getPostLifespanDistribution(commenter_id);
//                                 int lifespan = generateLifespan(lifespan_dist);

//                                 int hours = rand() % 24;
//                                 int minutes = rand() % 60;
//                                 int seconds = rand() % 60;
//                                 time_t eventTime = current_day_time + lifespan + (hours * 60 + minutes) * 60 + seconds;

//                                 string node_id = generateNodeId();
//                                 unique_ptr <Event> event;
//                                 event = unique_ptr<Event>(new Event(commenter_id, node_id, response_type, parent_node_id, root_node_id, eventTime));
//                                 event->setCommunityID(community_id);
//                                 post_comments.push_back(move(event));

//                                 if (++event_counter > breadth || iterator > 5000) {
//                                     cout << event_counter << " or " << iterator << " MORE THAN MAX " << breadth << endl;
//                                     stop_flag = true;   
//                                 }
//                                 break;
//                             }
//                         }
//                         if (stop_flag) {
//                             break;
//                         }
//                     }
//                     if (stop_flag) {
//                         break;
//                     }
//                 }
//             }
//             int comment_num = post_comments.size();
//             for (int k = 0; k < comment_num; k++) {
//                 events.push_back(move(post_comments[k]));
//             }
//         }
//     }
//     return events;
// }

// int SpecificCascadeModel::randomlyRoundDouble(double num) {
//     double float_part = num - (int) num;
//     double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//     if (randnum <= float_part) {
//         return (int) num + 1;
//     } else {
//         return (int) num;
//     }
// }

// int SpecificCascadeModel::generateBreadth(PostBreadthDistribution& t_postBreadthDistribution) {
//     vector<pair<int, double>> breadthDistribution = t_postBreadthDistribution.getBreadthDist();
//     double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//     double accum_prob = 0;
//     for (auto& iter : breadthDistribution) {
//         accum_prob += iter.second;
//         if (accum_prob >= randnum) {
//             return iter.first;
//         }
//     }
//     return breadthDistribution.back().first;
// }

// int SpecificCascadeModel::generateLifespan(PostLifespanDistribution& t_postLifespanDistribution) {
//     vector<pair<int, double>> lifespanDistribution = t_postLifespanDistribution.getLifespanDist();
//     double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//     double accum_prob = 0;
//     for (auto& iter : lifespanDistribution) {
//         accum_prob += iter.second;
//         if (accum_prob >= randnum) {
//             return iter.first;
//         }
//     }
//     return lifespanDistribution.back().first;
// }

// string SpecificCascadeModel::chooseResponseType(vector <string> &responseTypes, vector <double> &responseProbabilities) {
//     double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//     double accum_prob = 0;
//     int count = 0;
//     for (auto& iter : responseProbabilities) {
//         accum_prob += iter;
//         if (accum_prob >= randnum) {
//             return responseTypes[count];
//         }
//         count++;
//     }
//     return responseTypes[0];
// }

// string SpecificCascadeModel::generateNodeId() {
//     static const char alphanum[] =
//             "0123456789"
//                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//                     "abcdefghijklmnopqrstuvwxyz";

//     int len = 25;
//     string nodeId = "";

//     for (int i = 0; i < len; ++i) {
//         nodeId += alphanum[rand() % (sizeof(alphanum) - 1)];
//     }

//     return nodeId;
// }

// int SpecificCascadeModel::convertISOtoDay(time_t t_currentTime) {
//     return int(t_currentTime / (24 * 60 * 60));
// }

