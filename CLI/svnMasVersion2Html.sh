#!/bin/bash
#!Author:ZhangDezhi
# Create Time:2021-05-24 19:55
# Last Modified  : 2021-05-25 13:07:13
# Name:svnMasVersion_html.sh
# Version: v1.0
# Description: This is a Script.


function readfile() {
#{{{
linecount=0
cat $1 | while read LINE 
do
    # <th align=\"center\" valign=\"middle\" style=\"width\":90px;\">时间:</th>
    HTML_VER_START="
    <tr>
    "
    echo $HTML_VER_START >> $OUTHTML
    #echo $LINE
    OLD_LFS="$IFS"
    IFS=","
    array=($LINE)
    IFS="$OLD_LFS"

    count=0
    for var in ${array[@]}
    do 
        NBB=$( echo $var | sed 's/__//g')
        if [ $linecount == 0 -o $linecount == 1 ];then
            #Title
            if [ $count == 0 ];then 
                HTML_VER=" <td style=\"WORD-WRAP: break-word; overflow:hidden; width:100px;\">$NBB</td>"
            else
                #HTML_VER=" <td style=\"WORD-WRAP: break-word\">$NBB</td>"
                HTML_VER=" <td style=\"WORD-WRAP: break-all; overflow:hidden; \"><div title=\"$NBB\">$NBB</div></td>"
            fi

        else
            if [ $count == 0 ];then 
                #文件名
                HTML_VER=" <td style=\"WORD-WRAP: break-word; width:100px;\"><a href=\"./file/$NBB.html\">$NBB</a></td>"
            else
                if [[ $NBB == r* ]]
                then
                    #有版本号的
                    # HTML_VER="<td style=\"WORD-WRAP: break-word\" bgcolor=\"#93FF93\">$NBB</td>"
                    HTML_VER="<td style=\"WORD-WRAP: break-all; overflow:hidden; \" bgcolor=\"#93FF93\"><div title=\"$NBB\">$NBB</div></td>"
                else
                    HTML_VER="<td style=\"WORD-WRAP: break-word\" >$NBB</td>"
                fi
            fi
        fi

        # HTML_VER="<td style=\"white-space: nowrap; text-overflow: ellipsis;overflow: hidden;\" align=\"left\"><div title=\"$var\">$var</div></td>"

        echo $HTML_VER >> $OUTHTML
        count=$((${count} + 1))


    done

    HTML_VER_END="
    </tr>
    "
    echo $HTML_VER_END >> $OUTHTML

    linecount=$((${linecount} + 1))


done
#}}}
}


main() {
    INPUT=$1

    UPTIME=$(echo `date '+%Y%m%d-%H:%M:%S'`) 
    INPUTCSV="$INPUT/Report/info2.csv"
    OUTHTML="$INPUT/Report/index.html"

    HTML_START="
    <HTML>
    <head>
    <title> $INPUT </title>
    <style>
    table { border-collapse:collapse;}
    table,table tr th,table tr td {border:1px solid #000000;}
    div{height:20px; width:100px;}
    .font{font-size:10px}
    </style>
    </head>
    <body>
    <table class=\"font\" style=\"table-layout: fixed;overflow:hidden; width:100%;\" align=\"left\">
    <caption> 版本号汇总$INPUT 更新时间:$UPTIME</caption>
    "
    HTML_END="</table></HTML>"

    rm Report.html
    echo $HTML_START >> $OUTHTML

    readfile $INPUTCSV
    echo $HTML_END >> $OUTHTML


}
main $1

