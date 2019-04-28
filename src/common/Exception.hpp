#ifndef _SOCIAL_CUBE_EXCEPTION__
#define _SOCIAL_CUBE_EXCEPTION__
#include <exception>

class HourlyActionRateProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for HourlyActionRate";
    }
};

class DailyActivityLevelProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for DailyActivityLevel";
    }
};

class TimeSpanExceedException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "The given time span exceeds the one in DailyActivityLevel proxy file";
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

class PostScaleProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for PostScaleProxy";
    }
};

class ScoreMatrixProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for ScoreMatrixProxy";
    }
};

class CommentProbabilityProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for CommentProbabilityProxy";
    }
};

class CommunityDistributionProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for CommunityDistributionProxy";
    }
};

class MiscellaneousProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for MiscellaneousProxy";
    }
};

class SeedEventsProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for SeedEventsProxy";
    }
};

class SeedInfoIDProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for SeedInfoIDProxy";
    }
};

class PostLifespanDistributionProxyException: public std::exception {
    virtual const char * what () const throw ()
    {
        return "Error in opening statistic file for PostLifespanDistributionProxy";
    }
};

class EndTimeLessThanStartTime: public std::exception {
    virtual const char * what () const throw ()
    {
        return "End time is less than start time. Quit simulation";
    }
};

#endif
