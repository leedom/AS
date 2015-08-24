#include "Log.h"

static const char *Error[] =
{
    "[NONE ]",
    "[ERROR]",
    "[WARN ]",
    "[NOTCE]",
    "[INFO ]",
    "[DEBUG]"

};

Log::Log()
{
}
Log::~Log()
{
    //log4cpp::Category::shutdown();
}
bool Log::InitLog(const char *cpConf, const char* categoryName)
{
    if (NULL == cpConf || NULL == categoryName)
    {
        fprintf(stderr, "cpConf or categoryName is NULL");
        return false;
    }

    try
    {
        log4cpp::PropertyConfigurator::configure(cpConf);
    }
    catch(log4cpp::ConfigureFailure& f)
    {
        fprintf(stderr, "Configure Problem");
        return false;
    }

    log4cpp::Category& root = log4cpp::Category::getRoot();
    this->plog = &log4cpp::Category::getInstance(std::string(categoryName));

    return true;
}
/* 函 数 名：WriteLog
 * 功能说明：将cpFormat中的字符串写入到日志文件
 * 输入参数：iLevel         日志级别
 *           cpFile         文件名
 *           iLine          行数
 *           cpFun          函数名
 *           cpFormat       需要写入的字符串
 * 输出参数：
 * 返 回 值：true 成功；false 失败
 */
bool Log::WriteLog(LEVEL_TYPE iLevel,const char *cpFile,int iLine,const char *cpFun,const char *cpFormat, ...)
{
    if (cpFormat == NULL)
        return false;

    char cpMsg[2048];

    va_list val;
    va_start(val, cpFormat);
    vsnprintf(cpMsg, sizeof(cpMsg)-1, cpFormat, val);
    va_end(val);
    switch (iLevel)
    {
        case LEVEL_DEBUG:
            plog->debug("%s", cpMsg);
            //plog->debug("%s:%d %s", cpFile, iLine, cpMsg);
            break;
        case LEVEL_INFO:
            plog->info("%s", cpMsg);
            //plog->info("%s:%d %s", cpFile, iLine, cpMsg);
            break;
        case LEVEL_NOTICE:
            plog->notice("%s", cpMsg);
            //plog->notice("%s:%d %s", cpFile, iLine, cpMsg);
            break;
        case LEVEL_WARN:
            plog->warn("%s", cpMsg);
            //plog->warn("%s:%d %s", cpFile, iLine, cpMsg);
            break;
        case LEVEL_ERROR:
            plog->error("%s:%d %s", cpFile, iLine, cpMsg);
            break;

    }
    return true;
}
