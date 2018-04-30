#include "PointProcessModel.hpp"

using namespace std;

std::vector<unique_ptr<Event>> PointProcessModel::evaluate(
		const string objectID,
		const vector<double>& mu,
		const vector<vector<double>>& alpha,
		const vector<double>& beta,
		const vector<string>& typeList,
		int k,
        time_t t_startTime,
        time_t t_endTime
        ) {

    vector<unique_ptr<Event>> events;
    double currentMinute = t_startTime / 60;
    double startMinute = t_startTime / 60;
    double endMinute = t_endTime / 60;

	vector<double> upperIntensity = mu;

	while(currentMinute < endMinute) {
		auto interval = matops::mul(matops::ones(k), 10000);

		for(int i = 0; i < k; ++i) {
			double temInterval = 0.0;
			while(1) {
				double intensity = mu[i] + ((upperIntensity[i] - mu[i]) * exp(-beta[i] * temInterval));
				double u = (double)rand() / RAND_MAX;
				double delta = -log(u) / intensity;
				if(delta > 10000.0)
					break;
				temInterval += delta;
				double s = (double)rand() / RAND_MAX;
				double temIntensity = mu[i] + (intensity - mu[i]) * exp(-beta[i] * delta);
				if(s <= temIntensity / intensity) {
					interval[i] = temInterval;
					break;
				}
			}
		}
		int j = matops::minargs(interval);
		string actionType = typeList[j];
		double minInterval = interval[j];
		currentMinute += minInterval;

		string userID = generateUserID();
		time_t eventTime = currentMinute * 60;
		unique_ptr<Event> event(new Event(userID, objectID, actionType, eventTime));
		events.push_back(move(event));

		upperIntensity = matops::add(mu, matops::mul(matops::minus(upperIntensity, mu), matops::exp(matops::mul(matops::inv(beta), minInterval))));
		upperIntensity = matops::add(upperIntensity, matops::mul(alpha[j], beta));
	}

    return events;
}

string PointProcessModel::generateUserID() {
	string id(22, 'x');
	for(int i = 0; i < id.size(); ++i)
		id[i] = 'a' + rand()%26;
	return id;
}
