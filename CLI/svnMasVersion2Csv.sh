#!/bin/bash
#!Author:ZhangDezhi
# Create Time:2021-05-19 08:17
# Last Modified  : 2021-05-25 16:24:58
# Name:svnAllVerson.sh
# Version: v1.0
# Description: 批量下载svn上所有版本

SVNPATH="$2"
SVNOUT="$1"
UPTIME=$(echo `date '+%Y%m%d-%H:%M:%S'`)
#SVNPATH="https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/2)_redhat/bin" 
#SVNOUT="HEAD_zz04_bin"
#UPTIME=$("echo `date '+%Y%m%d-%H%M%S'`)

#) 检出HEAD
svn co "$SVNPATH"  $SVNOUT  

#) 初始化目录结构
cd $SVNOUT
mkdir History
mkdir Report 
mkdir Report/file
mkdir Report/svn

#) 获得所有文件
#{{{
_title1="时间"
_title2="SVN"

for line in $(svn log "$SVNPATH" | awk '/^r/{print $1}' )
do 
    #  echo ">>> $line"
    mkdir History/$line
    _time=$(svn log -$line "$SVNPATH/$file" | awk '/^r/{print $5}' )
    _title1="$_title1,$_time"
    _title2="$_title2,$line"

    #   echo "文件/时间,$_time"
done

echo $_title1 >> Report/info2.csv
echo $_title2 >> Report/info2.csv
#}}}

#) 每个文件单独处理获得历史版本
#{{{
echo "文件名,时间,svn版本号,md5,mas版本号,修改人,描述" >> Report/allfile.csv
for file in $(ls)
do 
    #echo "------------------------"

    #) 输出内容
    _outputline=" "
    oldIFS=$IFS
    IFS=,
    arr=($_title2)
    for ((i=1;i<${#arr[@]};i++))
    do
        _outputline="$_outputline,__"
    done

    outArr=($_outputline)
    IFS=$oldIFS

    #echo "->>> ${#outArr[@]}"


    #)单个文件处理
    #{{{
    #生成单文件的版本历史html

    HTML_FILE_TITLE="
    <HTML>
    <head>
    <meta charset=\"utf-8\">
    <title> 辉煌科技mas平台版本查询</title>
    <style>
    table { border-collapse:collapse;}
    table,table tr th,table tr td {border:1px solid #000000;}
    .font{font-size:10px}
    </style>
    </head>

    <table border=\"1\" cellspacing=\"0\" align=\"center\" width=\"100%\">
    <caption> $SVNOUT: $file 更新时间:$UPTIME</caption>
    <tr>
    <th align=\"center\" valign=\"right\" >文件名</th>
    <th align=\"center\" valign=\"middle\" >时间</th>
    <th align=\"center\" valign=\"middle\" >SVN</th>
    <th align=\"center\" valign=\"middle\" >MD5</th>
    <th align=\"center\" valign=\"middle\" >masVersion</th>
    <th align=\"center\" valign=\"middle\" >提交人</th>
    <th align=\"center\" valign=\"middle\" >提交描述</th>
    </tr>
    <tr>
    "
    #}}}

    count=0
    echo $HTML_FILE_TITLE >> Report/file/$file.html

    for line in $(svn log "$SVNPATH/$file" | awk '/^r/{ print $1}' )
    do
        #echo ">> $line"
        #导出文件
        svn export -$line  "$SVNPATH/$file" History/$line/$file

        if [ $count -ne 0 ];then
            HTML_FILE_MARK="</tr><tr>"
            echo $HTML_FILE_MARK >> Report/file/$file.html
        fi


        #转数组-用于填充数据
        oldIFS=$IFS
        IFS=,
        arr=($_title2)
        for ((i=0;i<${#arr[@]};i++))
        do
            if [ "${arr[$i]}" == "$line" ];then
                #_outputline="$_outputline,$line"
                outArr[$i]=$line
                #echo "--------------->> ${outArr[$i]}"
            fi
        done
        IFS=$oldIFS

        #日志信息
        _message=$(svn log -$line  "$SVNPATH/$file" | sed -n 4p | sed 's/,/ /g')
        _time=$(svn log -$line "$SVNPATH/$file" | awk '/^r/{print $5}' )
        _who=$(svn log -$line  "$SVNPATH/$file" | awk '/^r/{print $3}' )
        _md5=$(md5sum "./History/$line/$file" | awk ' {print $1}')
        _masVersion=$(strings "./History/$line/$file" | grep "version" | sed -n 1p)
        echo "$file,$_time,$line,$_md5,$_masVersion,$_who,$_message" >> Report/allfile.csv

        echo " <th align=\"center\" valign=\"middle\"> $file</th>" >> Report/file/$file.html
        echo " <th align=\"center\" valign=\"middle\"> $_time</th>" >> Report/file/$file.html
        echo " <th align=\"center\" valign=\"middle\"> $line</th>" >> Report/file/$file.html
        echo " <th align=\"center\" valign=\"middle\"> $_md5</th>" >> Report/file/$file.html
        echo " <th align=\"center\" valign=\"left\"> $_masVersion</th>" >> Report/file/$file.html
        echo " <th align=\"center\" valign=\"left\"> $_who</th>" >> Report/file/$file.html
        echo " <th align=\"center\" valign=\"left\"> $_message</th>" >> Report/file/$file.html
        #echo " <th align=\"center\" valign=\"middle\"> $file,$_time,$line,$_md5,$_masVersion,$_who,$_message</th>" >> Report/file/$file.html
        count=$((${count} + 1))
    done

    HTML_FILE_TITLE_END="</tr></table></HTML>"
    echo $HTML_FILE_TITLE_END >> Report/file/$file.html

    #echo "------->>> ${#outArr[@]}"
    sss="$file"
    for i in ${outArr[@]};do
        sss="$sss,$i";
    done
    #echo "$sss" | sed 's/__//g' >> output/info2.csv
    echo "$sss"  >> Report/info2.csv
done

#}}}
#文件名, 时间$5,svn版本, md5 , masVersion ,修改人$3,描述




