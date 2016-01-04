#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/select.h>
#include <time.h>
#include <sys/times.h>

#define MAX_STR_LEN     256

#define E_NG 0
#define E_OK 1


static  int core_opendev(const char * dev);
static  int core_set_parity(int fd, int databits,
							  int stopbits, int parity);
static  int core_set_baudrate(int fd, speed_t speed);
static  int core_read_gps_port_conf(char *serialport,int *baud,int*databits,
        int *stopbits,char *check);

/*******************************************************************************
    \fn			int core_gps_openserial()
	\brief		open GPS serial
	\return		fd : Success.\n
				-1 : Error.
*******************************************************************************/
int core_gps_openserial()
{
	int fd = 0;

	fd = core_opendev("dev/ttymxc1");
	if(fd == E_NG)
	{
		return -1;
	}

	if(core_set_baudrate(fd, 9600) == E_NG)
	{
		return -1;
	}

	if(core_set_parity(fd,8,1,'S') == E_NG)
	{
		return -1;
	}


	return fd;
}

/*******************************************************************************
    \fn			int core_set_baudrate(int fd,  speed_t speed)
	\brief		set baud rate 
	\param[in]	fd: the return value of open().
	\param[in]	speed: baud rate.
	\return		E_OK : Success.\n
				E_NG : Error..
*******************************************************************************/
int core_set_baudrate(int fd, speed_t speed)
{

	int status;
	struct termios Opt;
    if(tcgetattr(fd, &Opt) != 0)		//get current setting of serial port
    {
        printf("get baudrate error\n");
       // return E_NG;
    }

    if(tcflush(fd, TCIOFLUSH) != 0)		//fflush buf
    {
        printf("tcflush  error\n");
        //return E_NG;
    }

    if(cfsetispeed(&Opt, speed) != 0)
    {
        printf("cfsetispeed  error\n");
        //return E_NG;
    }
    if(cfsetospeed(&Opt, speed) != 0)
    {
        printf("cfsetospeed  error\n");
        //return E_NG;
    }

	status = tcsetattr(fd, TCSANOW, &Opt);
	if(status != 0)
	{
		printf("set baudrate error\n");
        return E_NG;
	}

    if(tcflush(fd, TCIOFLUSH) != 0)
    {
        printf("tcflush  error\n");
       // return E_NG;
    }
	return E_OK;
}

/*******************************************************************************
    \fn			int core_set_parity(int fd, int databits,
                                        int stopbits, int parity)
	\brief		set serial port 
	\param[in]	fd: the return value of open().
	\param[in]	databits: the number of data bit .
	\param[in]	stopbits: the number of stop bit.
	\param[in]	parity: the style of check.
	\return		E_OK : Success.\n
				E_NG : Error..
*******************************************************************************/
int core_set_parity(int fd, int databits,
					   int stopbits, int parity)
{
	struct termios options;

	if(tcgetattr(fd, &options) != 0)
	{
		printf("get attr error\n");
		return E_NG;
	}

	options.c_cflag &= ~CSIZE;

	switch (databits)
	{
	case 7:
		options.c_cflag |= CS7;
		break;
	case 8:
		options.c_cflag |= CS8;
		break;
	default:
		printf("set data bit error\n");
		return E_NG;
	}

	switch (parity)
	{
	case 'n':
	case 'N':
		options.c_cflag &= ~PARENB;
		options.c_iflag &= ~INPCK;
		break;
	case 'o':
	case 'O':
		options.c_cflag |= (PARODD | PARENB);
		options.c_iflag |= INPCK;
		break;
	case 'e':
	case 'E':
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		options.c_iflag |= INPCK;
		break;
	case 'S':
	case 's':					/*as no parity */
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break;
	default:
		printf("unsupported parity\n");
		return E_NG;
	}

	switch (stopbits)
	{
	case 1:
		options.c_cflag &= ~CSTOPB;
		break;
	case 2:
		options.c_cflag |= CSTOPB;
		break;
	default:
		printf("unsupported stop bits\n");
		return E_NG;
	}

	/* Set input parity option */
	if(parity != 'n')
	{
		options.c_iflag |= INPCK;
	}

    if(tcflush(fd, TCIFLUSH) != 0)
    {
        printf("tcflush  error\n");
        return E_NG;
    }
	options.c_cc[VTIME] = 10;	/* timeout  seconds */
	options.c_cc[VMIN] = 0;		/* Update the options and do it NOW */

	if(tcsetattr(fd, TCSANOW, &options) != 0)
	{
		printf("setup serial error\n");
		return E_NG;
	}

	return E_OK;
}

/*******************************************************************************
    \fn			int core_opendev(const char *dev)
	\brief		open Serial Port 
	\param[in]	Dev: the serial port.
	\return		fd :  id.\n
				E_NG : Error..
*******************************************************************************/
int core_opendev(const char * dev)
{
	int fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if(-1 == fd)
	{
		printf("gps open %s failed\n", dev);
		return E_NG;
	}
	else
	{
		return fd;
	}
}





/*******************************************************************************
    \fn			int core_gps_read(int fd)
    \brief		read data
    \return		E_OK : Success.\n
                E_NG : Error.
*******************************************************************************/
static void core_gps_read(int fd)
{
    int i = 0;
    int checkflag = 0;
    char buff[256];
    char data = 0;


    printf("gps begin read\n");
    while(1)
    {
        while(read(fd, &data, 1) > 0)
        {
			printf("%c",data);
 		}
    }
}






/********************************************************************************
    \fn			int main()
    \brief		start process..
    \return		E_OK : Success.\n
                E_NG : Error.
********************************************************************************/
int main()
{
 
	int fd = 0;

    fd = core_gps_openserial();


    if(fd == -1)
    {
        return E_NG;
    }
    core_gps_read(fd);
    core_gps_end();
    return E_OK;
}



