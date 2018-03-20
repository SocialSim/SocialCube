#ifndef _SOCIAL_CUBE_EXCEPTION__
#define _SOCIAL_CUBE_EXCEPTION__
#include <exception>

class HourlyActionRateProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for HourlyActionRate";
    }
};

class ObjectPreferenceProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for ObjectPreference";
    }
};

class UserIDProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for UserID";
    }
};

class ObjectIDProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for Object ID";
    }
};

#endif
