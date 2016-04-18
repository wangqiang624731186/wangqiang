#########################################################################
# File Name: monitor.sh
# Author: wangqiang
# mail: wqa@ample.net.cn
# Created Time: Mon 18 Apr 2016 02:13:04 PM CST
#########################################################################
#!/bin/sh

FILE=$1
NEWFILE=newfile
TMPFILE=tmpfile

cat $FILE | cut -d ] -f 2 | cut -b 7,7- > $NEWFILE


cat $NEWFILE | grep "CPU ALL USE:" > $TMPFILE
cat $TMPFILE | sed 's/CPU ALL USE://g' > result_cpuall_use

cat $NEWFILE | grep "CPU0 USE:" > $TMPFILE
cat $TMPFILE | sed 's/CPU0 USE://g' > result_cpu0_use

cat $NEWFILE | grep "CPU1 USE:" > $TMPFILE
cat $TMPFILE | sed 's/CPU1 USE://g' > result_cpu1_use

cat $NEWFILE | grep "CPU TEMP:" > $TMPFILE
cat $TMPFILE | sed 's/CPU TEMP://g' > result_cpu_temp

cat $NEWFILE | grep "MEM FREE:" > $TMPFILE
cat $TMPFILE | sed 's/MEM FREE://g' > result_mem_free

cat $NEWFILE | grep "CPU0 FREQ:" > $TMPFILE
cat $TMPFILE | sed 's/CPU0 FREQ://g' > result_cpu0_freq

cat $NEWFILE | grep "CPU1 FREQ:" > $TMPFILE
cat $TMPFILE | sed 's/CPU1 FREQ://g' > result_cpu1_freq


rm $NEWFILE $TMPFILE
