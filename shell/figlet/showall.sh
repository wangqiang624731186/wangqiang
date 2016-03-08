#########################################################################
# File Name: tar.sh
# Author: wangqiang
# mail: 624731186@qq.com
# Created Time: 2016年01月06日 星期三 13时41分37秒
#########################################################################
#!/bin/sh


ShowName()
{
    sfilename=$*
    dfilename=`basename $sfilename` 
    echo "--------------------------------------------"
    echo $dfilename    
    if [ "$dfilename" !=  "." ] && [ "$dfilename" !=  ".." ] && [ "$dfilename" !=  " " ] ; then
        figlet -f $dfilename WANGQIANG
    fi
    echo "--------------------------------------------"
}


TMPFILE=/tmp/wangqiang_figlet
YESORNO=$1

rm $TMPFILE
find /usr/share/figlet -maxdepth 1 > $TMPFILE
while read line  
do  
    ShowName $line     
done < $TMPFILE

