#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <sys/stat.h>
#include <libgen.h>

#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include "log4cpp/BasicLayout.hh"


typedef enum
{
    LEVEL_NONE = 0, // no log
    LEVEL_ERROR,
    LEVEL_WARN,
    LEVEL_NOTICE,
    LEVEL_INFO,
    LEVEL_DEBUG
} LEVEL_TYPE;


#define Print olog.WriteLog

#define ErrorLog(cpFormat...) Print(LEVEL_ERROR,__FILE__,__LINE__,__FUNCTION__, ##cpFormat)
#define WarnLog(cpFormat...) Print(LEVEL_WARN,__FILE__,__LINE__,__FUNCTION__, ##cpFormat)
#define NoticeLog(cpFormat...) Print(LEVEL_WARN,__FILE__,__LINE__,__FUNCTION__, ##cpFormat)
#define InfoLog(cpFormat...) Print(LEVEL_INFO,__FILE__,__LINE__,__FUNCTION__, ##cpFormat)
#define DebugLog(cpFormat...) Print(LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__, ##cpFormat)

class Log
{
    public:
        Log();
        ~Log();
        bool InitLog(const char *cpConf, const char* categoryName);
        bool WriteLog(LEVEL_TYPE iLevel, const char *cpFile,int iLine,const char *cpFun,const char *cpFormat, ...);

    private:
        log4cpp::Category *plog;

};
#endif
