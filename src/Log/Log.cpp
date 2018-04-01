#include "Log.hpp"

#ifdef DEBUG

static const int session_to_pause=0;

void pause_session(int session)
{
#ifdef PAUSE
    if(session==session_to_pause)
        getchar();
#endif
}

mutex log_lock;
stringstream ss;

int event_num=0;


void LOGD(const string& tag, const string& log)
{
    const char* color=GREEN;
    string offset(50-tag.size(),' ');
    log_lock.lock();
    cout<<color<<tag<<": "<<offset<<log<<RESET<<"\n";
    cout.flush();
    log_lock.unlock();
}

void LOGE(const string& tag, const string& log)
{
    log_lock.lock();
    cout<<RED<<tag<<":"<<log<<RESET<<"\n";
    cout.flush();
    log_lock.unlock();
}

void LOGW(const string& tag, const string& log)
{
    log_lock.lock();
    cout<<YELLOW<<tag<<":"<<log<<RESET<<"\n";
    cout.flush();
    log_lock.unlock();
}

#endif
