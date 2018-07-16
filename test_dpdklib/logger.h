#ifndef MM_LOGGER_H
#define MM_LOGGER_H

#define VERBOSE_LOGGING

#include <stdio.h>
#include <rte_lcore.h>
#include <sys/time.h>

typedef enum logging_level_t {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_DEFAUL    //Map to one of the previous log level
} logging_level;

//ret_status init_logger( const char* log_file );

#define log_format_time() \
    struct timeval tv;\
    time_t nowtime;\
    struct tm *nowtm;\
    char tmbuf[64], buf[64];\
    gettimeofday(&tv, NULL);\
    nowtime = tv.tv_sec;\
    nowtm = localtime(&nowtime);\
    strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);\
    snprintf(buf, sizeof buf, "%s.%06ld", tmbuf, tv.tv_usec);\

#define shell_log_printf(target,type,msg,...) \
    do{\
        log_format_time();\
        fprintf(target,"%s [%s](%d): "msg"\n",buf,type,rte_lcore_id(),##__VA_ARGS__); \
    } while( 0 );

#define shell_log(msg,...) do{ shell_log_printf(stdout,"LOG",msg,##__VA_ARGS__); }while(0);
#define shell_err(msg,...) do{ shell_log_printf(stderr,"ERR",msg,##__VA_ARGS__); }while(0);
#define shell_wrn(msg,...) do{ shell_log_printf(stderr,"WRN",msg,##__VA_ARGS__); }while(0);

#define log_printf(pref,msg,...) \
    do{\
        shell_log_printf(stderr,pref,msg,##__VA_ARGS__); \
    } while( 0 );

#define log(msg,...) log_printf("OUT",msg,##__VA_ARGS__)
#define err(msg,...) log_printf("ERR",msg,##__VA_ARGS__)
#define wrn(msg,...) log_printf("WRN",msg,##__VA_ARGS__)
#define dbg(msg,...) log_printf("DBG",msg,##__VA_ARGS__)

#define fenter(msg,...) log_printf("CLL"," -> %s "#msg,__func__,##__VA_ARGS__);
#define fexit(msg,val)  log_printf("EXT", " <- %s "#msg,__func__,val); return val;
#define fvoidexit()     log_printf("EXT", " <- %s",__func__);


#endif
