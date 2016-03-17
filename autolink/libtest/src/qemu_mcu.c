/*************************************************************************
	test_mcu.c
 ************************************************************************/

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <string.h>
 #include <errno.h>
 #include <pthread.h>
 #include <fcntl.h>
 #include <sys/epoll.h>
 #include <math.h>
 #include <time.h>
 #include <sys/time.h>
 #include "autolink_log.h"
 #include "autolink_mcu.h"




 #define  MCU_SYNC_BYTE_0            0xAA
 #define  MCU_SYNC_BYTE_1            0x77
 #define  MCU_FLAG_BYTE_NORMAL       0x00
 #define  MCU_FLAG_BYTE_REPLY        0xFF
 #define  MCU_ACK_BYTE_FALSE         0
 #define  MCU_ACK_BYTE_TRUE          (!MCU_ACK_BYTE_FALSE)
 #define  MCU_END_BYTE_REPLY         0x55
 #define  MCU_REPLY_BYTE_SUM         5
 #define  MCUINFO_MAX_SIZE  127
 #define FRAME_LEN_MAX   255
 #define DATA_LEN_MAX   247 //(255-8)



#define MCU_UART_DEV  "/dev/pts/19"
#define MCU_UART_BAUD  115200

#define MCU_TO_ARM_FALG "MCU-ARM:"

typedef struct {
    int                       mcufd;
    unsigned int              pos;
    unsigned char             flag;
    unsigned char             checksum;
    unsigned char             framecounter;
    unsigned char             cmd1;
    unsigned char             ack;
    unsigned char             len;
    unsigned char             data[ MCUINFO_MAX_SIZE+1 ];
} mcuinfo_st;

mcuinfo_st mcuinfo;


/*******************************************************************************
    Function  Definition
*******************************************************************************/
static unsigned char autolink_mcu_checksum2(unsigned char flag,unsigned char framecounter,
                                            unsigned char cmd1,unsigned char ack,
                                            unsigned char *data, int len)
{
	int i = 0;
    unsigned char checksum = 0;
    if(data == NULL){
        return -1;
    }


    checksum = checksum^flag;
    checksum = checksum^framecounter;
    checksum = checksum^cmd1;
    checksum = checksum^ack;
    checksum = checksum^len;

    for(i = 0; i < len ; i++){
        checksum = checksum^data[i];
    }
    return checksum;
}
/*******************************************************************************
    Function  Definition
*******************************************************************************/
static void autolink_mcu_parse(unsigned char  c )
{
    if (mcuinfo.pos >= (int) sizeof(mcuinfo.data)-1 ) {
        printf("-------------------------------------------\n");
        printf("             mcu overflow data \n");
        printf("-------------------------------------------\n");
        mcuinfo.pos      = 0;
        return;
    }

    if (MCU_SYNC_BYTE_0 != c && mcuinfo.pos == 0) {
        printf("-------------------------------------------\n");
        printf("             mcu lost sync data 0\n");
        printf("-------------------------------------------\n");
        mcuinfo.pos      = 0;
        return;
    }

    if (MCU_SYNC_BYTE_1 != c && mcuinfo.pos == 1) {
        printf("-------------------------------------------\n");
        printf("             mcu lost sync data 1\n");
        printf("-------------------------------------------\n");
        mcuinfo.pos      = 0;
        return;
    }

    if (MCU_FLAG_BYTE_NORMAL != c && mcuinfo.pos == 2) {
        printf("-------------------------------------------\n");
        printf("             mcu flag data error\n");
        printf("-------------------------------------------\n");
        mcuinfo.pos      = 0;
        return;
    }

    if (mcuinfo.pos == 3) {
        mcuinfo.checksum = c;
    }

    if(mcuinfo.pos == 4){
        mcuinfo.framecounter = c;
    }

    if(mcuinfo.pos == 5){
        mcuinfo.cmd1 = c;
    }

    if(mcuinfo.pos == 6){
        mcuinfo.ack = c;
    }

    if(mcuinfo.pos == 7){
        mcuinfo.len = c;
    }

    if(mcuinfo.pos>=8){
        mcuinfo.data[mcuinfo.pos-8] = c;
    }

    mcuinfo.pos       += 1;
    if(mcuinfo.pos == mcuinfo.len + 8){
        //get a full frame


        if(mcuinfo.checksum != autolink_mcu_checksum2(mcuinfo.flag,mcuinfo.framecounter,
                                                      mcuinfo.cmd1,mcuinfo.ack,
                                                      mcuinfo.data,mcuinfo.len)){
            printf("-------------------------------------------\n");
            printf("             check sum failed\n");
            printf("-------------------------------------------\n");
        }else{
            printf("--------------------SUCESS-----------------------\n");
        }
        mcuinfo.pos = 0;
    }
}
/*******************************************************************************
    Function  Definition
*******************************************************************************/
static unsigned char autolink_mcu_checksum(unsigned char flag,unsigned char *data, int size)
{
    int i = 0;
    unsigned char checksum = flag;
    if(data == NULL){
        return -1;
    }
    for(i = 0; i < size ; i++){
        checksum = checksum^data[i];
    }

    return checksum;
}
/*******************************************************************************
    Function  Definition
*******************************************************************************/
extern int autolink_mcu_sendinfo1(unsigned  char *data,int len)
{

    printf("Send ");
    int i;
    for(i = 0;i<len;i++){
        printf("[%02X]",*(data + i));
    }
    printf("\n");


    if(mcuinfo.mcufd <= 0){
        return -1;
    }

    return write(mcuinfo.mcufd, data, len);
}
/*******************************************************************************
    Function  Definition
*******************************************************************************/
extern int autolink_mcu_send_msg1(int times,unsigned char cmd1,unsigned char* data,char len)
{
    unsigned char reply[FRAME_LEN_MAX];
    int result = -1;
    int iter = 0;
    reply[0] = MCU_SYNC_BYTE_0;
    reply[1] = MCU_SYNC_BYTE_1;
    reply[2] = MCU_FLAG_BYTE_NORMAL;
    reply[4] = 0; //framecounter ???
    reply[5] = cmd1;
    reply[6] = MCU_ACK_BYTE_FALSE;
    reply[7] = len;
    memcpy(reply+8,data,len);

    reply[3] = autolink_mcu_checksum(reply[2],reply+4,len+4);

    while(iter < times){
        if( len+8 == autolink_mcu_sendinfo1(reply,len+8) ){
            result = 0;
            break;
        }
        iter++;
        printf("-------------------------------------------\n");
        printf("mcu send data failed %d times\n",iter);
        printf("-------------------------------------------\n");
    }

    return result;
}


static int autolink_mcu_uart_init()
{
    int fd = autolink_uart_open(MCU_UART_DEV,O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd < 0){
        printf("open %s failed\n",MCU_UART_DEV);
        return -1;
    }

    if(0 != autolink_uart_set_speed(fd, MCU_UART_BAUD)){
        printf("set speed %d failed\n",MCU_UART_BAUD);
        return -1;
    }

    if(0 != autolink_uart_set_parity(fd, 8, 1, 'N')){
        printf("set parity error\n");
        return -1;
    }

    return fd;
}

/*******************************************************************************
    Function  Definition
*******************************************************************************/
static void AUTOLINK_UARTINFO(unsigned char *buff,int size)
{
    int iter = 0;

    if(size <= 0)
        return;

    for(iter = 0;iter < size;iter++){
        printf("[%02X]",buff[iter]);
    }

    printf("\n");
}

/*******************************************************************************
    Function  Definition
*******************************************************************************/
static int epoll_register( int epoll_fd, int fd )
{
    struct epoll_event  ev;
    int ret, flags;

    /* important: make the fd non-blocking */
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    ev.events  = EPOLLIN;
    ev.data.fd = fd;
    do {
        ret = epoll_ctl( epoll_fd, EPOLL_CTL_ADD, fd, &ev );
    } while (ret < 0 && errno == EINTR);
    return ret;
}

static void* autolink_mcu_service_thread(void* user_data)
{

    int    epoll_fd   = epoll_create(1);

    epoll_register( epoll_fd, mcuinfo.mcufd );

    for (;;) {
        struct epoll_event    events[1];
        int    ne, nevents;

        nevents = epoll_wait( epoll_fd, events, 1, -1 );
        if (nevents < 0) {
            if (errno != EINTR)
                printf("epoll_wait() unexpected error: %s\n", strerror(errno));
            continue;
        }

        for (ne = 0; ne < nevents; ne++) {
            int  fd = events[ne].data.fd;
            if (fd == mcuinfo.mcufd){
                char  buff[32];
                int  nn, ret;
                for (;;) {
                    ret = read( fd, buff, 32);
                    if (ret < 0) {
                        if (errno == EINTR)
                            continue;
                        if (errno != EWOULDBLOCK)
                            printf("error while reading from mcu: %s:\n", strerror(errno));
                        break;
                    }

                    if(ret == 0){
                        break;
                    }
                    AUTOLINK_UARTINFO(buff,ret);

                    for (nn = 0; nn < ret; nn++){
                        autolink_mcu_parse(  buff[nn] );
                    }
                }
            }else{
                printf("epoll_wait() returned unkown fd %d ?\n", fd);
            }
        }
    }
    return NULL;
}

static int autolink_mcu_init1()
{
    pthread_t tid;
    mcuinfo.mcufd = autolink_mcu_uart_init();
    if(mcuinfo.mcufd < 0){
        printf("autolink_mcu_uart_init failed\n");
        return -1;
    }

    pthread_create(&tid, NULL, autolink_mcu_service_thread, NULL);
    return 0;
}

char HexStrToChar(char* str)
{
    int i = 0;
    int len = strlen(str);

    //printf("%d\n",len);
    char var = 0;
    char result = 0;
    if(len>2)
    {
        exit(-1);
    }

    for(i=0;i<len;i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
           var = str[i] -48;
        }
        else if(str[i] >= 'A' && str[i] <= 'F')
        {
            var = str[i] - 65 + 10;
        }
        else if(str[i] >= 'a' && str[i] <= 'f')
        {
            var = str[i] - 97 + 10;
        }
        else
        {
            exit(-1);
        }


        if(i == 0)
        {
            result |= var<<4;
        }
        else
        {
            result |= var;
        }

        //printf("%x\n",result);
    }


    return result;
}


int autolink_mcu_read_conf(char* file)
{
    FILE   *fp = NULL;
	char   data[255];
	char   buf[255];
	char   *tmp = buf;
    char   *temp =data;
	char   len = 0;
    int    i = 0;
    int     cmd = 0;
    char   msg_data[255];
    char   num = 0;
    char *p = NULL;
	fp = fopen(file, "r");
	if(!fp){
        printf("open %s failed\n",file);
		return -1;
	}

	while(!feof(fp)){
		memset(buf,0,255);
		tmp = fgets(buf,255,fp);
		if(buf[0] == '#' || buf[0] == '\r' || buf[0] == '\n')
        {
            continue;
        }

        i = strlen(buf);
        while(i > 0)
        {
            i--;
            if(buf[i] == '\r' || buf[i] == '\n' || buf[i] == 0 )
            {
                buf[i] = 0;
            }
            else
            {
                break;
            }

        }

		len = strlen(buf)+1;

        if(0 != strncmp (buf,MCU_TO_ARM_FALG,strlen(MCU_TO_ARM_FALG)))
        {
            continue;
        }

        //printf("%s\n",buf);
        memcpy(data,buf+strlen(MCU_TO_ARM_FALG),len);

        p = NULL;
        temp = data;
        i = 0;
        while((p = strsep(&temp, ",")) != NULL)
        {
            //printf("%s\n",p);
            num = HexStrToChar(p);
            if(0 == i)
            {
                cmd = num;
            }
            else
            {
                msg_data[i-1] = num;
            }
            i++;
        }

        autolink_mcu_send_msg1(1,cmd,msg_data,i-1);

        getchar();
	}
}
int main(int argc,char** argv)
{
    autolink_mcu_init1();

    //autolink_mcu_read_conf(argv[1]);

    while(1)
    {
        sleep(5);
    }
}
