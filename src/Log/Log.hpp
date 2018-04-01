#ifndef __LOG_IMPL_HPP__
#define __LOG_IMPL_HPP__

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#ifdef DEBUG
#include<iostream>
#include<string>
#include<cassert>
#include<exception>
#include<sstream>
#include<vector>
#include<mutex>

using namespace std;

string pathy(const vector<string>& path);

void LOGD(const string& tag, const string& log, bool preamble = true);

void LOGP(const string& tag, const string& log, bool preamble = true);

void LOGE(const string& tag, const string& log, bool preamble = true);

void LOGW(const string& tag, const string& log, bool preamble = true);

void LOGIMPL(const string& tag, const string& log, const char* color, bool preamble = true);

extern stringstream ss;
template<typename  T>
string stringfy(T x)
{
    return to_string(x);
}

extern int event_num;

#endif

#ifdef DEBUG
#define DBG(arg) arg
#define TAG tag+'-'+stringfy(__LINE__)+'-'+__func__+"-event["+stringfy(event_num++)+"]"


#else
#define DBG(arg)
#define TAG
#endif

#endif
