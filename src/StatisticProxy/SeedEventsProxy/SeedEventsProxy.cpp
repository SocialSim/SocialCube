#include "SeedEventsProxy.hpp"

DBG(static const string tag="SeedEventsProxy";)

using namespace std;

SeedEventsProxy::SeedEventsProxy(const string& file) throw() {
    try {
        m_seedEventsStatisticFile.open (file);
    } catch (exception &e) {
        SeedEventsProxyException h_e;
        throw h_e;
    }
    assert(m_seedEventsStatisticFile.is_open());

    return;
}

SeedEventsProxy::~SeedEventsProxy() {
    m_seedEventsStatisticFile.close();
    return;
}

void SeedEventsProxy::parse() {
    string tmp;
    while (getline(m_seedEventsStatisticFile, tmp)) {
        // userID postID communityID postTime
        string userID = tmp.substr(0, tmp.find(" "));
        string probabilities = tmp.substr(tmp.find(" ") + 1);
        unordered_map<string, double> userCommunityDistribution;

        istringstream in(tmp);

        string user_id;
        string node_id;
        string community_id;
        time_t post_time;

        in >> user_id;
        in >> node_id;
        in >> community_id;
        in >> post_time;
	    cout << "user_id= " << user_id << ", community_id = " << community_id << ", post_time = " << post_time << endl;
        Event event(user_id, node_id, "post", node_id, node_id, post_time);
        if (!seed_events.count(user_id)) {
            seed_events.insert(std::make_pair(user_id, vector<Event>()));
        }
	    event.setCommunityID(community_id);
        seed_events[user_id].push_back(event);
    }
}

void SeedEventsProxy::show() {
    cout << seed_events.size() << endl;
}

vector<Event> SeedEventsProxy::get(string t_user_id) {
    return seed_events[t_user_id];
}
