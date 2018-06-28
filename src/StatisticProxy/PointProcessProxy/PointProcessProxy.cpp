#include "PointProcessProxy.hpp"

DBG(static const string tag="PointProcessProxy";)

using namespace std;

PointProcessProxy::PointProcessProxy(const string& file) throw() {
	try {
        m_pointProcessStatisticsFile.open (file);
    } catch (exception &e) {
        PointProcessProxyException p_e;
        throw p_e;
    }
    assert(m_pointProcessStatisticsFile.is_open());
    return;
}

PointProcessProxy::~PointProcessProxy() {
    m_pointProcessStatisticsFile.close();
    return;
}

void PointProcessProxy::parse() {

    string tmp;
    while (getline(m_pointProcessStatisticsFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        int k = stoi(tmp.substr(tmp.find(" ") + 1));
        unique_ptr<PointProcessStat> pointProcessStat(new PointProcessStat(userID));
		pointProcessStat->setK(k);

		// parse typeList
		getline(m_pointProcessStatisticsFile, tmp);
		istringstream in(tmp);
		string type;
		vector<string> typeList;
		while(in >> type) {
			typeList.push_back(type);
		}
		pointProcessStat->setTypeList(typeList);
		// parse mu
		getline(m_pointProcessStatisticsFile, tmp);
		istringstream mu_in(tmp);
		string mu_ele;
		vector<double> mu;
        for(int i = 0; i < k; ++i) {
			mu_in >> mu_ele;
			mu.push_back(stod(mu_ele));
		}
		pointProcessStat->setMu(mu);
		// parse alpha
		getline(m_pointProcessStatisticsFile, tmp);

		istringstream ss(tmp);
/*
 *                istream_iterator<std::string> begin(ss);
 *                istream_iterator<std::string> end({});
 *                vector<std::string> segments(begin, end);
 *
 */
		vector<string> segments;
		copy(std::istream_iterator<string>(ss),
			std::istream_iterator<string>(),
			std::back_inserter(segments));
		vector<vector<double>> alpha;
		string alpha_ele;

		if (segments.size() == mu.size()) {
			for(int i = 0; i < k; ++i) {
				vector<double> alpha_row;
				alpha_row.push_back(stod(segments[i]));
				alpha.push_back(alpha_row);
			}
		} else {
			/*istringstream alpha_in(tmp);
			for(int i = 0; i < k; ++i) {
				vector<double> alpha_row;
				for(int j = 0; j < k; ++j) {
					alpha_in >> alpha_ele;
					alpha_row.push_back(stod(alpha_ele));
				}
				alpha.push_back(alpha_row);
			}*/
			for(int i = 0; i < k; ++i) {
				vector<double> alpha_row;
				for(int j = 0; j < k; ++j) {
					alpha_ele = segments[i*k + j];
					alpha_row.push_back(stod(alpha_ele));
				}
				alpha.push_back(alpha_row);
			}
		}
		pointProcessStat->setAlpha(alpha);

		// parse beta
		getline(m_pointProcessStatisticsFile, tmp);
		istringstream beta_in(tmp);
		string beta_ele;
		vector<double> beta;
        for(int i = 0; i < k; ++i) {
			beta_in >> beta_ele;
			beta.push_back(stod(beta_ele));
		}
		pointProcessStat->setBeta(beta);

        m_stats[userID] = move(pointProcessStat);
    }
    DBG(LOGD(TAG, "Point Process Stat has "+stringfy(m_stats.size()));)
}

void PointProcessProxy::show() {
    cout << m_stats.size() << endl; 
    for(auto& iter : m_stats) {
        iter.second->show();
    }
}

PointProcessStat& PointProcessProxy::get(const std::string& userID) {
    if(m_stats.find(userID) == m_stats.end()) {
		throw;
    } else {
        assert(m_stats.find(userID) != m_stats.end());
        return *(m_stats[userID]);
    }
}
