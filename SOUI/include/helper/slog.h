#pragma once
#include "SApp.h"
#include <intrin.h>
#include <trace.h>

namespace SOUI
{
    class Log4zBinary;
    class Log4zStream;
}

#ifndef E_RANGE
#define E_RANGE 9944
#endif

//! check VC VERSION. DO NOT TOUCH
//! format micro cannot support VC6 or VS2003, please use stream input log, like LOGI, LOGD, LOG_DEBUG, LOG_STREAM ...
#if _MSC_VER >= 1400 //MSVC >= VS2005
#define LOG4Z_FORMAT_INPUT_ENABLE
#endif

#if !defined(WIN32)  && !defined(_WIN64)
#define LOG4Z_FORMAT_INPUT_ENABLE
#endif

//! base micro.
#define LOG_STREAM(id_or_name, filter, level,  log)\
    do{\
    SOUI::ILog4zManager * pLogMgr = SOUI::SApplication::getSingleton().GetLogManager(); \
    char logBuf[LOG4Z_LOG_BUF_SIZE];\
    SOUI::Log4zStream ss(logBuf, LOG4Z_LOG_BUF_SIZE);\
    ss << log;\
    if (pLogMgr && pLogMgr->prePushLog(id_or_name,level)) \
    {\
    const void *pAddr = _ReturnAddress(); \
    pLogMgr->pushLog(id_or_name, level, filter, logBuf, __FILE__, __LINE__, __FUNCTION__, pAddr);\
    }else\
    {\
    STRACEA(logBuf);\
    }\
    } while (0)


//! fast micro
#define LOG_TRACE(id_or_name, filter, log) LOG_STREAM(id_or_name, filter, LOG_LEVEL_TRACE, log)
#define LOG_DEBUG(id_or_name, filter, log) LOG_STREAM(id_or_name, filter, LOG_LEVEL_DEBUG, log)
#define LOG_INFO(id_or_name, filter, log)  LOG_STREAM(id_or_name, filter, LOG_LEVEL_INFO, log)
#define LOG_WARN(id_or_name, filter, log)  LOG_STREAM(id_or_name, filter, LOG_LEVEL_WARN, log)
#define LOG_ERROR(id_or_name, filter, log) LOG_STREAM(id_or_name, filter, LOG_LEVEL_ERROR, log)
#define LOG_ALARM(id_or_name, filter, log) LOG_STREAM(id_or_name, filter, LOG_LEVEL_ALARM, log)
#define LOG_FATAL(id_or_name, filter, log) LOG_STREAM(id_or_name, filter, LOG_LEVEL_FATAL, log)

//! super micro.
#define LOGT(filter, log ) LOG_TRACE(LOG4Z_MAIN_LOGGER_ID,filter, log )
#define LOGD(filter, log ) LOG_DEBUG(LOG4Z_MAIN_LOGGER_ID, filter,log )
#define LOGI(filter, log ) LOG_INFO(LOG4Z_MAIN_LOGGER_ID,filter, log )
#define LOGW(filter, log ) LOG_WARN(LOG4Z_MAIN_LOGGER_ID, filter,log )
#define LOGE(filter, log ) LOG_ERROR(LOG4Z_MAIN_LOGGER_ID,filter, log )
#define LOGA(filter, log ) LOG_ALARM(LOG4Z_MAIN_LOGGER_ID,filter, log )
#define LOGF(filter, log ) LOG_FATAL(LOG4Z_MAIN_LOGGER_ID,filter, log )


//! format input log.
#ifdef LOG4Z_FORMAT_INPUT_ENABLE
#define LOG_FORMAT(id_or_name, level, filter, logformat, ...) \
    do{ \
    SOUI::ILog4zManager * pLogMgr = SOUI::SApplication::getSingleton().GetLogManager(); \
    char logbuf[LOG4Z_LOG_BUF_SIZE]; \
    if(sizeof(logformat[0]) == sizeof(char))\
        _snprintf_s(logbuf, LOG4Z_LOG_BUF_SIZE, _TRUNCATE, (const char*)logformat, ##__VA_ARGS__); \
    else \
    {\
        wchar_t logbufw[LOG4Z_LOG_BUF_SIZE]; \
        _snwprintf_s(logbufw, LOG4Z_LOG_BUF_SIZE, _TRUNCATE, (const wchar_t*)logformat, ##__VA_ARGS__); \
        DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, logbufw, -1, NULL, 0, NULL, NULL);\
        if (dwLen < LOG4Z_LOG_BUF_SIZE)\
        {\
            WideCharToMultiByte(CP_ACP, 0, logbufw, -1, logbuf, dwLen, NULL, NULL);\
        }\
    }\
    if (pLogMgr && pLogMgr->prePushLog(id_or_name,level)) \
    {\
    pLogMgr->pushLog(id_or_name, level,filter, logbuf, __FILE__, __LINE__, __FUNCTION__,_ReturnAddress()); \
    }else\
    {\
    STRACEA(logbuf);\
    }\
    } while (0)

//!format string
#define LOGFMT_TRACE(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_TRACE, filter, fmt, ##__VA_ARGS__)
#define LOGFMT_DEBUG(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_DEBUG, filter, fmt, ##__VA_ARGS__)
#define LOGFMT_INFO(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_INFO,  filter,fmt, ##__VA_ARGS__)
#define LOGFMT_WARN(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_WARN,  filter,fmt, ##__VA_ARGS__)
#define LOGFMT_ERROR(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_ERROR, filter, fmt, ##__VA_ARGS__)
#define LOGFMT_ALARM(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_ALARM, filter, fmt, ##__VA_ARGS__)
#define LOGFMT_FATAL(id_or_name, filter, fmt, ...)  LOG_FORMAT(id_or_name, LOG_LEVEL_FATAL, filter, fmt, ##__VA_ARGS__)
#define LOGFMTT( filter, fmt, ...) LOGFMT_TRACE(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#define LOGFMTD( filter, fmt, ...) LOGFMT_DEBUG(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#define LOGFMTI( filter, fmt, ...) LOGFMT_INFO(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#define LOGFMTW( filter, fmt, ...) LOGFMT_WARN(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#define LOGFMTE( filter, fmt, ...) LOGFMT_ERROR(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#define LOGFMTA( filter, fmt, ...) LOGFMT_ALARM(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#define LOGFMTF( filter, fmt, ...) LOGFMT_FATAL(LOG4Z_MAIN_LOGGER_ID, filter, fmt,  ##__VA_ARGS__)
#else
inline void empty_log_format_function1(LoggerId , const char *, const char*, ...){}
inline void empty_log_format_function2(const char *, const char*, ...){}
#define LOGFMT_TRACE empty_log_format_function1
#define LOGFMT_DEBUG LOGFMT_TRACE
#define LOGFMT_INFO LOGFMT_TRACE
#define LOGFMT_WARN LOGFMT_TRACE
#define LOGFMT_ERROR LOGFMT_TRACE
#define LOGFMT_ALARM LOGFMT_TRACE
#define LOGFMT_FATAL LOGFMT_TRACE
#define LOGFMTT empty_log_format_function2
#define LOGFMTD LOGFMTT
#define LOGFMTI LOGFMTT
#define LOGFMTW LOGFMTT
#define LOGFMTE LOGFMTT
#define LOGFMTA LOGFMTT
#define LOGFMTF LOGFMTT
#endif

namespace SOUI{
//! optimze from std::stringstream to Log4zStream
#if defined (WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable:4996)
#endif
class Log4zBinary
{
public:
    Log4zBinary(const char * buf, int len)
    {
        _buf = buf;
        _len = len;
    }
    const char * _buf;
    int  _len;
};
class Log4zStream
{
public:
    inline Log4zStream(char * buf, int len);
    inline int getCurrentLen(){return (int)(_cur - _begin);}
private:
    template<class T>
    inline Log4zStream & writeData(const char * ft, T t);
    inline Log4zStream & writeLongLong(long long t);
    inline Log4zStream & writeULongLong(unsigned long long t);
    inline Log4zStream & writePointer(const void * t);
    inline Log4zStream & writeString(const char* t);
    inline Log4zStream & writeWString(const wchar_t* t);
    inline Log4zStream & writeBinary(const Log4zBinary & t);
public:
    inline Log4zStream & operator <<(const void * t){ return  writePointer(t); }

    inline Log4zStream & operator <<(const char * t){return writeString(t);}
#if defined (WIN32) || defined(_WIN64)
    inline Log4zStream & operator <<(const wchar_t * t){ return writeWString(t);}
#endif
    inline Log4zStream & operator <<(bool t){ return (t ? writeData("%s", "true") : writeData("%s", "false"));}

    inline Log4zStream & operator <<(char t){return writeData("%c", t);}

    inline Log4zStream & operator <<(unsigned char t){return writeData("%u",(unsigned int)t);}

    inline Log4zStream & operator <<(short t){ return writeData("%d", (int)t); }

    inline Log4zStream & operator <<(unsigned short t){ return writeData("%u", (unsigned int)t); }

    inline Log4zStream & operator <<(int t){return writeData("%d", t);}

    inline Log4zStream & operator <<(unsigned int t){return writeData("%u", t);}

    inline Log4zStream & operator <<(long t) { return writeLongLong(t); }

    inline Log4zStream & operator <<(unsigned long t){ return writeULongLong(t); }

    inline Log4zStream & operator <<(long long t) { return writeLongLong(t); }

    inline Log4zStream & operator <<(unsigned long long t){ return writeULongLong(t); }

    inline Log4zStream & operator <<(float t){return writeData("%.4f", t);}

    inline Log4zStream & operator <<(double t){return writeData("%.4lf", t);}

    inline Log4zStream & operator << (const Log4zBinary & binary){ return writeBinary(binary); }

private:
    Log4zStream(){}
    Log4zStream(Log4zStream &){}
    char *  _begin;
    char *  _end;
    char *  _cur;
};

inline Log4zStream::Log4zStream(char * buf, int len)
{
    _begin = buf;
    _end = buf + len;
    _cur = _begin;
}

template<class T>
inline Log4zStream& Log4zStream::writeData(const char * ft, T t)
{
    if (_cur < _end)
    {
        int len = 0;
        int count = (int)(_end - _cur);
#if defined (WIN32) || defined(_WIN64)
        len = _snprintf(_cur, count, ft, t);
        if (len == count || (len == -1 && errno == E_RANGE))
        {
            len = count;
            *(_end - 1) = '\0';
        }
        else if (len < 0)
        {
            *_cur = '\0';
            len = 0;
        }
#else
        len = snprintf(_cur, count, ft, t);
        if (len < 0)
        {
            *_cur = '\0';
            len = 0;
        }
        else if (len >= count)
        {
            len = count;
            *(_end - 1) = '\0';
        }
#endif
        _cur += len;
    }
    return *this;
}

inline Log4zStream & Log4zStream::writeLongLong(long long t)
{
#if defined (WIN32) || defined(_WIN64) 
    writeData("%I64d", t);
#else
    writeData("%lld", t);
#endif
    return *this;
}

inline Log4zStream & Log4zStream::writeULongLong(unsigned long long t)
{
#if defined (WIN32) || defined(_WIN64) 
    writeData("%I64u", t);
#else
    writeData("%llu", t);
#endif
    return *this;
}

inline Log4zStream & Log4zStream::writePointer(const void * t)
{
#if defined (WIN32) || defined(_WIN64)
    sizeof(t) == 8 ? writeData("%016I64x", (unsigned long long)t) : writeData("%08I64x", (unsigned long long)t);
#else
    sizeof(t) == 8 ? writeData("%016llx", (unsigned long long)t) : writeData("%08llx", (unsigned long long)t);
#endif
    return *this;
}

inline Log4zStream & Log4zStream::writeBinary(const Log4zBinary & t)
{
    writeData("%s", "\r\n\t[");
    for (int i = 0; i < t._len; i++)
    {
        if (i % 16 == 0)
        {
            writeData("%s", "\r\n\t");
            *this << (void*)(t._buf + i);
            writeData("%s", ": ");
        }
        writeData("%02x ", (unsigned char)t._buf[i]);
    }
    writeData("%s", "\r\n\t]\r\n\t");
    return *this;
}

inline Log4zStream & Log4zStream::writeString(const char* t)
{
    writeData("%s", t);
    return *this;
}

inline Log4zStream & Log4zStream::writeWString(const wchar_t* t)
{
#if defined (WIN32) || defined(_WIN64)
    DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, t, -1, NULL, 0, NULL, NULL);
    if (dwLen < LOG4Z_LOG_BUF_SIZE)
    {
        char buf[LOG4Z_LOG_BUF_SIZE];
        dwLen = WideCharToMultiByte(CP_ACP, 0, t, -1, buf, dwLen, NULL, NULL);
        if (dwLen > 0)
        {
            buf[dwLen] = 0;
            writeData("%s", buf);
        }
    }
#else
    //not support
#endif
    return *this;
}


#if defined (WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

}//end of namespace SOUI
