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


void LOGD(const string& tag, const string& log, bool preamble)
{
    const char* color=GREEN;
    LOGIMPL(tag, log, color, preamble);
}

void LOGP(const string& tag, const string& log, bool preamble)
{
    const char* color=BLUE;
    LOGIMPL(tag, log, color, preamble);
}

void LOGE(const string& tag, const string& log, bool preamble)
{
    const char* color=RED;
    LOGIMPL(tag, log, color, preamble);
}

void LOGW(const string& tag, const string& log, bool preamble)
{
    const char* color=YELLOW;
    LOGIMPL(tag, log, color, preamble);
}

void LOGIMPL(const string& tag, const string& log, const char* color, bool preamble) {
    string offset(50-tag.size(),' ');
    log_lock.lock();
    if(preamble)
        cout<<color<<tag<<": "<<offset<<log<<RESET<<"\n";
    else
        cout<<color<<log<<RESET<<"\n";
    cout.flush();
    log_lock.unlock();
}

#endif
