#include <time.h>
#include <stdio.h>

print_time(struct tm *time)
{
	printf("=================================\n");
	printf("tm_sec:%d \n",time->tm_sec);
	printf("tm_min:%d \n",time->tm_min);
	printf("tm_hour:%d \n",time->tm_hour);
	printf("tm_mday:%d \n",time->tm_mday);
	printf("tm_mon:%d \n",time->tm_mon);
	printf("tm_year:%d \n",time->tm_year);
	printf("tm_wday:%d \n",time->tm_wday);
	printf("tm_yday:%d \n",time->tm_yday);
	printf("tm_isdst:%d \n",time->tm_isdst);


}

int time1()
{
    time_t tNow =time(NULL);
    time_t tEnd = tNow + 1800;
    //注意下面两行的区别
    struct tm* ptm = localtime(&tNow);
    struct tm* ptmEnd = localtime(&tEnd);

    char szTmp[50] = {0};
    strftime(szTmp,50,"%H:%M:%S",ptm);
    char szEnd[50] = {0};
    strftime(szEnd,50,"%H:%M:%S",ptmEnd);
    
	print_time(ptm);
	print_time(ptmEnd);

    printf("%s \n",szTmp);
    printf("%s \n",szEnd);
    

    return 0;
}

int time2()
{
    time_t tNow =time(NULL);
    time_t tEnd = time(NULL);
    //注意下面两行的区别
    struct tm* ptm = gmtime(&tNow);
    struct tm* ptmEnd = gmtime(&tEnd);

    char szTmp[50] = {0};
    strftime(szTmp,50,"%H:%M:%S",ptm);
    char szEnd[50] = {0};
    strftime(szEnd,50,"%H:%M:%S",ptmEnd);
    
	print_time(ptm);
	print_time(ptmEnd);

    printf("%s \n",szTmp);
    printf("%s \n",szEnd);
    

    return 0;
}

int main()
{
	time1();
	time2();
	return 0;
}
