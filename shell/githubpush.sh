#########################################################################
# File Name: githubpush.sh
# Author: wangqiang
# mail: 624731186@qq.com
# Created Time: 2016年01月04日 星期一 09时32分14秒
#########################################################################
#!/bin/sh
/usr/bin/expect  <<-EOF
spawn git push -u origin master
expect "*Username*"
send "---name---\r"
expect "*Password*"
send "---passwd---\r"
send "exit\r"
expect eof
EOF
