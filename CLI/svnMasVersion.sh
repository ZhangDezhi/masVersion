#!/bin/bash
#!Author:ZhangDezhi
# Create Time:2021-05-25 10:10
# Last Modified  : 2021-05-25 10:45:25
# Name:svnMasVersion.sh
# Version: v1.0
# Description: This is a Script.

#zz04
./svnMasVersion2Csv.sh "rhel_zz04_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/2)_redhat/bin" 
./svnMasVersion2Html.sh "rhel_zz04_bin"
./svnMasVersion2Csv.sh "rhel_zz04_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/2_郑州4号线/00_软件发布/2)_redhat/lib" 
./svnMasVersion2Html.sh "rhel_zz04_lib"

#zz03
./svnMasVersion2Csv.sh "rhel_zz03_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/3_郑州3号线/00_软件发布/2)_redhat/bin" 
./svnMasVersion2Html.sh "rhel_zz03_bin"
./svnMasVersion2Csv.sh "rhel_zz03_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/3_郑州3号线/00_软件发布/2)_redhat/lib"
./svnMasVersion2Html.sh "rhel_zz03_lib"

##zz06
./svnMasVersion2Csv.sh "rhel_zz06_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/6_郑州6号线/00_软件发布/2)_redhat/bin"
./svnMasVersion2Html.sh "rhel_zz06_bin"
./svnMasVersion2Csv.sh "rhel_zz06_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/6_郑州6号线/00_软件发布/2)_redhat/lib"
./svnMasVersion2Html.sh "rhel_zz06_lib"
#
##ly01
./svnMasVersion2Csv.sh "rhel_ly01_bin" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/4_洛阳1号线/00_软件发布/2)_redhat/bin" 
./svnMasVersion2Html.sh "rhel_ly01_bin"
./svnMasVersion2Csv.sh "rhel_ly01_lib" "https://172.16.4.236/svn/MAS平台软件/2_项目软件/4_洛阳1号线/00_软件发布/2)_redhat/lib"
./svnMasVersion2Html.sh "rhel_ly01_bin"


