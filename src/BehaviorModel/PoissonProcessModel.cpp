#include "PoissonProcessModel.hpp"

using namespace std;

std::vector<unique_ptr<Event>> PoissonProcessModel::evaluate(
        const string objectID,
        const vector<double>& mu,
        const vector<string>& typeList,
        int k,
        time_t t_startTime,
        time_t t_endTime
) {

    vector<unique_ptr<Event>> events;
    double currentMinute = t_startTime / 60;
    double startMinute = t_startTime / 60;
    double endMinute = t_endTime / 60;

    for (int i = 0; i < k; i++){
        string actionType = typeList[i];
        currentMinute = t_startTime / 60;
        double typeMu = mu[i];
        while(currentMinute < endMinute) {

            double u = (double)rand() / RAND_MAX;
            currentMinute += -log(u) / (typeMu + 1e-7);

            if(currentMinute > endMinute){
                break;
            }

            string userID = generateUserID();
            time_t eventTime = currentMinute * 60;
            unique_ptr<Event> event(new Event(userID, objectID, actionType, eventTime));
            events.push_back(move(event));
        }
    }

    return events;
}

string PoissonProcessModel::generateUserID() {
    string id(22, 'x');
    for(int i = 0; i < id.size(); ++i)
        id[i] = 'a' + rand()%26;
    return id;
}
