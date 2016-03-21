#include <stdio.h>
#include <stdlib.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
/************************************************
设置操作系统时间
参数:*dt数据格式为"2006-4-20 20:30:30"
调用方法:
char *pt="2006-4-20 20:30:30";
SetSystemTime(pt);
**************************************************/
int main(char *dt)
{
    /*
struct rtc_time tm;
struct tm _tm;
struct timeval tv;
time_t timep;


tm.tm_year = 2012;
tm.tm_mon = 4;
tm.tm_mday = 2;
tm.tm_hour = 3;
tm.tm_min = 30;
tm.tm_sec = 30;

_tm.tm_sec = tm.tm_sec;
_tm.tm_min = tm.tm_min;
_tm.tm_hour = tm.tm_hour;
_tm.tm_mday = tm.tm_mday;
_tm.tm_mon = tm.tm_mon - 1;
_tm.tm_year = tm.tm_year - 1900;

timep = mktime(&_tm);
tv.tv_sec = timep;
tv.tv_usec = 0;
if(settimeofday (&tv, (struct timezone *) 0) < 0)
{
printf("Set system datatime error!\n");
return -1;
}
*/

    time_t now;

    struct tm *tm_now;



    time(&now);

    tm_now = localtime(&now);



    printf("now datetime: %d-%d-%d %d:%d:%d\n", tm_now->tm_year, tm_now->tm_mon, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
//system("hwclock  -w");  //写到硬时钟

return 0;
}
