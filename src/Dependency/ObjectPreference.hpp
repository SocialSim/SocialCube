#ifndef __OBJECT_PREFERENCE__
#define __OBJECT_PREFERENCE__

#include <unordered_map>
#include <string>
#include <vector>

class ObjectPreference {

    private:

        // ObjectID -> preference
        std::unordered_map<std::string, double> m_preference;

        std::string m_userID;

    public:
        ObjectPreference(const std::string& t_userID);

        ~ObjectPreference();

        void set(const std::string &t_objectID, double t_preference);

        double get(const std::string &t_objectID);

        void increment(const std::string &t_objectID, double t_delta);

        bool exist(const std::string &t_objectID);

        std::vector<std::string> getPreferedObjectIDs();
};

#endif
