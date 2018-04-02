#ifndef __OBJECT_PREFERENCE__
#define __OBJECT_PREFERENCE__

#include <unordered_map>
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

class ObjectPreference {
    private:
        class PreferenceNode {
            public:
            std::string objID;
            double preference;
            static struct _Comparator
            {
                bool operator() (const PreferenceNode& left, const PreferenceNode& right) {
                    return left.preference < right.preference;
                }

                bool operator() (double left, const PreferenceNode& right) {
                    return left < right.preference;
                }

                bool operator() (const PreferenceNode& left, double right) {
                    return left.preference < right;
                }

                bool operator() (const std::unique_ptr<PreferenceNode>& left, const std::unique_ptr<PreferenceNode>& right) {
                    return left->preference < right->preference;
                }

                bool operator() (double left, const std::unique_ptr<PreferenceNode>& right) {
                    return left < right->preference;
                }

                bool operator() (const std::unique_ptr<PreferenceNode>& left, double right) {
                    return left->preference < right;
                }
            } Comparator;
            PreferenceNode(const std::string& s, double p) : objID(s), preference(p) {}
        };

    private:
        void test();

        std::vector<std::unique_ptr<PreferenceNode>> m_preference;

        std::string m_userID;

    public:
        ObjectPreference(const std::string& t_userID);

        ~ObjectPreference();

        void set(const std::string &t_objectID, double t_preference);

        void show() const;

        std::string randomChooseTarget(bool seed = false, double _d = 0.0) const;

        std::string getUserID() const;
};

#endif
