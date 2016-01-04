#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

char *confpath = "69-libmtp.rules";
char *hal_confpath = "hal_mtp";
char *idvendor = "idVendor";
char *idproduct = "idProduct";
char *flag = "==";
void main()
{

	FILE    *fp_read = NULL;
	FILE    *fp_write = NULL;	
	char  	read_buf[256];
	char  	write_buf[256];
	char 	*data = NULL;
	fp_read = fopen(confpath, "r");
	if(!fp_read){
		printf("open %s failed\n",confpath);
		return ;
	}

	fp_write = fopen(hal_confpath, "w+");
	if(!fp_write){
		printf("open %s failed\n",hal_confpath);
		return ;
	}


	while(!feof(fp_read)){
		memset(read_buf,0,256);   
		fgets(read_buf,256,fp_read);	
		if(read_buf[0] == '#' || read_buf[0] == '\r' || read_buf[0] == '\n')
        {
            continue;
        }  
		if(strstr(read_buf,idvendor) && strstr(read_buf,idproduct))
		{
			memset(write_buf,0,256);  
			data = strstr(read_buf,idvendor);
			data = strstr(data,flag);
			strcat(write_buf,"idVendor:");
			strncat(write_buf,data+3,4);
			strcat(write_buf,",");

			data = strstr(read_buf,idproduct);
			data = strstr(data,flag);
			strcat(write_buf,"idProduct:");
			strncat(write_buf,data+3,4);
			strcat(write_buf,"\n");
			fwrite(write_buf,strlen(write_buf),1,fp_write);
		}
	
	}




	fclose(fp_read);
	fclose(fp_write);

	return ;
}
