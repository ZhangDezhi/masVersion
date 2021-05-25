#!/bin/bash
#!Author:ZhangDezhi
# Create Time:2021-05-25 10:10
# Last Modified  : 2021-05-25 16:04:19
# Name:svnMasVersion.sh
# Version: v1.0
# Description: This is a Script.

UPTIME=$(echo `date '+%Y%m%d-%H:%M:%S'`)
_HTML_="

<!DOCTYPE html> 
<html>

<head>
<meta charset=\"utf-8\">
<title>iscs综合监控平台</title>
</head>

<body>
<p align=\"center\">ISCS平台mas2.0 更新:$UPTIME </p>

<h2 align=\"center\">郑州3号线</h2>
<ol style=\"text-align:center;\">
<li align=\"left\"><a href=\"./rhel_zz03_bin/Report/index.html\"   >   rhel-bin </a></li>
<li align=\"left\"><a href=\"./rhel_zz03_lib/Report/index.html\"   >   rhel-lib </a></li>
<li align=\"left\"><a href=\"./windows_zz03_bin/Report/index.html\">windows-bin(无) </a></li>
<li align=\"left\"><a href=\"./windows_zz03_lib/Report/index.html\">windows-lib(无) </a></li>
<li align=\"left\"><a href=\"./hpux_zz03_bin/Report/index.html\"   >   hpux-bin(无) </a></li>
<li align=\"left\"><a href=\"./hpux_zz03_lib/Report/index.html\"   >   hpux-lib(无) </a></li>
</ol>

<h2 align=\"center\">郑州4号线</h2>
<ol style=\"text-align:center;\">
<li align=\"left\"><a href=\"./rhel_zz04_bin/Report/index.html\"> rhel-bin</a></li>
<li align=\"left\"><a href=\"./rhel_zz04_lib/Report/index.html\"> rhel-lib</a></li>
<li align=\"left\"><a href=\"./windows_zz04_bin/Report/index.html\">windows-bin</a></li>
<li align=\"left\"><a href=\"./windows_zz04_lib/Report/index.html\">windows-lib</a></li>
<li align=\"left\"><a href=\"./hpux_zz04_bin/Report/index.html\"> hpux-bin</a></li>
<li align=\"left\"><a href=\"./hpux_zz04_lib/Report/index.html\"> hpux-lib</a></li>
</ol>

<h2 align=\"center\">郑州6号线</h2>
<ol style=\"text-align:center;\">
<li align=\"left\"><a href=\"./rhel_zz06_bin/Report/index.html\" >rhel-bin</a></li>
<li align=\"left\"><a href=\"./rhel_zz06_lib/Report/index.html\" >rhel-lib</a></li>
<li align=\"left\"><a href=\"./windows_zz06_bin/Report/index.html\" >windows-bin(无)</a></li>
<li align=\"left\"><a href=\"./windows_zz06_lib/Report/index.html\" >windows-lib(无)</a></li>
<li align=\"left\"><a href=\"./hpux_zz06_bin/Report/index.html\" >hpux-bin(无)</a></li>
<li align=\"left\"><a href=\"./hpux_zz06_lib/Report/index.html\" >hpux-lib(无)</a></li>
</ol>

<h2 align=\"center\">洛阳1号线</h2>
<ol style=\"text-align:center;\">
<li align=\"left\"><a href=\"./rhel_ly01_bin/Report/index.html\" >rhel-bin</a></li>
<li align=\"left\"><a href=\"./rhel_ly01_lib/Report/index.html\" >rhel-lib</a></li>
<li align=\"left\"><a href=\"./windows_ly01_bin/Report/index.html\" >windows-bin(无)</a></li>
<li align=\"left\"><a href=\"./windows_ly01_lib/Report/index.html\" >windows-lib(无)</a></li>
<li align=\"left\"><a href=\"./hpux_ly01_bin/Report/index.html\" >hpux-bin(无)</a></li>
<li align=\"left\"><a href=\"./hpux_ly01_lib/Report/index.html\" >hpux-lib(无)</a></li>
</ol>

<h6 align=\"right\">powered by 基础研发</h6>

</body>
</html>
"

echo $_HTML_ >> index.html



echo " ---------------   zz04  ----------------"
#zz04
./svnMasVersion2Csv.sh  "rhel_zz04_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/2)_redhat/bin" 
./svnMasVersion2Html.sh "rhel_zz04_bin"
./svnMasVersion2Csv.sh  "rhel_zz04_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/2)_redhat/lib" 
./svnMasVersion2Html.sh "rhel_zz04_lib"
./svnMasVersion2Csv.sh  "windows_zz04_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/3)_windows/bin"
./svnMasVersion2Html.sh "windows_zz04_bin"
./svnMasVersion2Csv.sh  "windows_zz04_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/3)_windows/dll"
./svnMasVersion2Html.sh "windows_zz04_lib"
./svnMasVersion2Csv.sh  "hpux_zz04_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/1)_hpunix/bin"
./svnMasVersion2Html.sh "hpux_zz04_bin"
./svnMasVersion2Csv.sh  "hpux_zz04_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/1)_hpunix/lib"
./svnMasVersion2Html.sh "hpux_zz04_lib"

echo " ---------------   zz03  ----------------"

#zz03
./svnMasVersion2Csv.sh  "rhel_zz03_bin"   "https://172.16.4.236/svn/MAS平台软件/2_项目软件/3_郑州3号线/00_软件发布/2)_redhat/bin" 
./svnMasVersion2Html.sh "rhel_zz03_bin"

./svnMasVersion2Csv.sh  "rhel_zz03_lib"    "https://172.16.4.236/svn/MAS平台软件/2_项目软件/3_郑州3号线/00_软件发布/2)_redhat/lib"
./svnMasVersion2Html.sh "rhel_zz03_lib"

#./svnMasVersion2Csv.sh  "windows_zz03_bin"
#./svnMasVersion2Html.sh "windows_zz03_bin"
#./svnMasVersion2Csv.sh  "windows_zz03_lib"
#./svnMasVersion2Html.sh "windows_zz03_lib"
#
#./svnMasVersion2Csv.sh  "hpux_zz03_bin"
#./svnMasVersion2Html.sh "hpux_zz03_bin"
#./svnMasVersion2Csv.sh  "hpux_zz03_lib"
#./svnMasVersion2Html.sh "hpux_zz03_bin"


echo " ---------------   zz06  ----------------"
##zz06
./svnMasVersion2Csv.sh "rhel_zz06_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/6_郑州6号线/00_软件发布/2)_redhat/bin"
./svnMasVersion2Html.sh "rhel_zz06_bin"
./svnMasVersion2Csv.sh "rhel_zz06_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/6_郑州6号线/00_软件发布/2)_redhat/lib"
./svnMasVersion2Html.sh "rhel_zz06_lib"

#./svnMasVersion2Csv.sh  "windows_zz06_bin"
#./svnMasVersion2Html.sh "windows_zz06_bin"
#./svnMasVersion2Csv.sh  "windows_zz06_lib"
#./svnMasVersion2Html.sh "windows_zz06_lib"
#
#./svnMasVersion2Csv.sh  "hpux_zz06_bin"
#./svnMasVersion2Html.sh "hpux_zz06_bin"
#./svnMasVersion2Csv.sh  "hpux_zz06_lib"
#./svnMasVersion2Html.sh "hpux_zz06_bin"
#

echo " ---------------   ly01  ----------------"
##ly01
./svnMasVersion2Csv.sh  "rhel_ly01_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/4_洛阳1号线/00_软件发布/2)_redhat/bin" 
./svnMasVersion2Html.sh "rhel_ly01_bin"
./svnMasVersion2Csv.sh  "rhel_ly01_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/4_洛阳1号线/00_软件发布/2)_redhat/lib"
./svnMasVersion2Html.sh "rhel_ly01_lib"

#./svnMasVersion2Csv.sh  "windows_ly01_bin"
#./svnMasVersion2Html.sh "windows_ly01_bin"
#./svnMasVersion2Csv.sh  "windows_ly01_lib"
#./svnMasVersion2Html.sh "windows_ly01_lib"
#
#./svnMasVersion2Csv.sh  "hpux_ly01_bin"
#./svnMasVersion2Html.sh "hpux_ly01_bin"
#./svnMasVersion2Csv.sh  "hpux_ly01_lib"
#./svnMasVersion2Html.sh "hpux_ly01_bin"


