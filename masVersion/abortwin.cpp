#include "abortwin.h"
#include "ui_abortwin.h"

// 版本信息,Linux使用strings命令,Win使用find命令
#define APP_VERSION "V1.4"

AbortWin::AbortWin( QWidget* parent ) : QDialog( parent ), ui( new Ui::AbortWin ) {
    ui->setupUi( this );
    QString verStr;
    verStr = QString( "当前版本: %1 \nPowered by 基础研发\n\n" ).arg( APP_VERSION );
    ui->textBrowser->append( verStr );

    QString abtStr = QString( ""
                              "使用终端(CMD)查询命令:\n"
                              "-------------------------------------\n"
                              "Win: \n"
                              " find \"version:\"  fileName \n"
                              "\n"
                              "RHEL: "
                              "\n"
                              "strings fileName | grep \"version:\""
                              "\n"
                              "\n"
                              "程序查询逻辑: \n"
                              "1. 查询 MD5值 \n"
                              "2. 查询包含 Version/VERSION/version 并且包涵 V2.0 的字符串\n" );
    ui->textBrowser->append( abtStr );
}

AbortWin::~AbortWin()
{
    delete ui;
}
