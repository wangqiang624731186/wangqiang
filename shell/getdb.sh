#!/bin/bash                                                               
#file: mkcscope
#function: make cscope database and ctags database

ignore="( -name .git -o -name test -o -name tests ) -prune -o"
type="( -name *.java -o -name *.cpp -o -name *.[ch] -o -name *.xml -o -name
*.aidl )"
CSCOPE_CODE=$2

cscopedb=$CSCOPE_CODE/cscope
prepare()
{
    if [ ! -d $CSCOPE_CODE ]; then
        echo "no CSCOPE_CODE set"
        echo "please set CSCOPE_CODE at your .bashrc file"
        exit 1
    else
        echo "CSCOPE_CODE:$CSCOPE_CODE"
        if [ -d $cscopedb ]; then
            echo "$cscopedb exist already"
            if [ -e $cscopedb/cscope.files ]; then
                echo "file $cscopedb/cscope.files exist"
#               rm $cscopedb/cscope.files
            fi
        else
            mkdir $cscopedb
            echo "make directory $cscopedb"
        fi
    fi
    all_source | sort > $cscopedb/cscope.files
    lines=$(wc -l $cscopedb/cscope.files | awk '{ printf $1 }')
    echo "find $lines files totaly"
}
all_source()
{
    for src in $CSCOPE_CODE
    do
        find -L $src $ignore $type -print
    done
}

docscope()
{
    echo "Now begin build cscope cross-index file"
    start=`date +%s`
    cscope -b -k -q -i $cscopedb/cscope.files -f $cscopedb/cscope.out
    end=`date +%s`
    let "elapse=$end-$start"
    if [ $? -eq 0 ]; then
        echo "make cscope database file with total time ($elapse) seconds"
        size=$(du $cscopedb/cscope.out -h | awk '{ printf $1 }')
        echo "($cscopedb/cscope.out):$size"
    fi 
}
dotags()
{
    echo "Now begin build tags file"
    start=`date +%s`
    ctags --fields=+afiKlmnsSzt -L $cscopedb/cscope.files -f $cscopedb/tags
    end=`date +%s`
    let "elapse=$end-$start"
    if [ $? -eq 0 ]; then
        echo "make ctags database file with total time ($elapse) seconds"
        size=$(du $cscopedb/tags -h | awk '{ printf $1 }')
        echo "($cscopedb/tags):$size"
    fi 
}

usage()
{
    echo "Usages:"
    echo "$0    cscope . : make cscope database only"
    echo "      tags   . : make ctags database only"
    echo "      all . : make two databases"
}


case $1 in
    "cscope")
    prepare
    docscope
    ;;
                                                                          
    "tags")
    prepare
    dotags
    ;; 

    "all")
    prepare
    docscope
    dotags
    ;;
    "")
    usage
    ;;
esac    
