#########################################################################
# File Name: tar.sh
# Author: wangqiang
# mail: 624731186@qq.com
# Created Time: 2016年01月06日 星期三 13时41分37秒
#########################################################################
#!/bin/sh

YESORNO="no"

TarFile()
{
    sfilename=$*
    dfilename=$sfilename.tar.bz2 
    echo "--------------------------------------------"
    echo $sfilename    
    if [ "$sfilename" !=  "." ] && [ "$sfilename" !=  ".." ] ; then
        echo $dfilename    
        if [ "$YESORNO" ==  "yes" ] ; then
            tar cjvf $dfilename $sfilename
        fi
    fi
    echo "--------------------------------------------"
}


TMPFILE=/tmp/wangqiang_tar
YESORNO=$1

rm $TMPFILE
find . -maxdepth 1 > $TMPFILE
sed -i 's/^..//' $TMPFILE
while read line  
do  
    TarFile $line     
done < $TMPFILE

