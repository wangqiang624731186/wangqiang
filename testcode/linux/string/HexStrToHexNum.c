/*******************************************************************************
    \file          123.c
    \author        wangqiang
    \mail          wangqiang@auto-link.com
    \version       0.1
    \date          2016-03-08 18:10
*******************************************************************************/

/*******************************************************************************
    Include Files
*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*******************************************************************************
    Type Definition
*******************************************************************************/
char HexStrToChar(char* str)
{
    int i = 0;
    int len = strlen(str);

    //printf("%d\n",len);
    char var = 0;
    char result = 0;
    if(len>2)
        return -1;


    for(i=0;i<len;i++)
    {
        if(str[i] >= '0' && str[i] <= '0')
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
            return -1;;
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


/*******************************************************************************
    Function  Definition
*******************************************************************************/
int main()
{
    char a[3] = {'A','A',0};


    printf("[%02X]\n",HexStrToChar(a));

    a[0] = 'a';

    printf("[%02X]\n",HexStrToChar(a));

    a[0] = '0';

    printf("[%02X]\n",HexStrToChar(a));

    a[1] = '0';

    printf("[%02X]\n",HexStrToChar(a));

    a[0] = 'a';
    a[1] = 'a';
    printf("[%02X]\n",HexStrToChar(a));

    a[0] = 'a';
    a[1] = '0';
    printf("[%02X]\n",HexStrToChar(a));

    a[0] = 'F';
    a[1] = 'F';
    printf("[%02X]\n",HexStrToChar(a));


    return 0;
}
