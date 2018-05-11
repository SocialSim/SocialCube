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
	int simulationCount = 0;

	vector<double> upperIntensity = mu;

	while(currentMinute < endMinute) {
		auto interval = matops::mul(matops::ones(k), 10000);

		// Avoid infinite simulation, restart the simulation.
		if(events.size() > 100000) {
			currentMinute = t_startTime / 60;
			upperIntensity = mu;
			events.clear();
			simulationCount++;
		}

		// Stop the simulation after 5 failed tries.
		if(simulationCount >= 5){
			return events;
		}

		for(int i = 0; i < k; ++i) {
			double temInterval = 0.0;
			while(1) {
				double intensity = mu[i] + ((upperIntensity[i] - mu[i]) * exp(-beta[i] * temInterval));
				double u = (double)rand() / RAND_MAX;
				double theoretical_delta = -log(u) / (intensity + 1e-7);
				double delta = theoretical_delta <= (double)0.0167 ? 0.0167 : theoretical_delta;
				temInterval += delta;
				double s = (double)rand() / RAND_MAX;
				double temIntensity = mu[i] + (intensity - mu[i]) * exp(-beta[i] * delta);
				if(s <= (temIntensity + 1e-7) / (intensity + 1e-7)) {
					interval[i] = temInterval;
					break;
				}
			}
		}
		int j = matops::minargs(interval);
		string actionType = typeList[j];
		double minInterval = interval[j];
		currentMinute += minInterval;
		if(currentMinute >= endMinute){
			return events;
		}

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
