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

class UserIDProxyNoMethodException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "This UserIDProxy does not have the method you wish to call";
    }
};

class ObjectIDProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for Object ID";
    }
};

class TypeDistributionProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for TypeDistribution";
    }
};

class UserDistributionProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for UserDistribution";
    }
};

class PointProcessProxyException : public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for PointProcessProxy";
    }
};

class PoissonProcessProxyException : public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for PoissonProcessProxy";
    }
};

class CountryCodesProxyException : public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for CountryCodesProxy";
    }
};

class EndTimeLessThanStartTime: public std::exception {
    virtual const char * what () const throw ()
    {
        return "End time is less than start time. Quit simulation";
    }
};
#endif
