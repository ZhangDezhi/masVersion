#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    //设置窗体大小
    setFixedSize( 365, 540 );

    //设置透明
    // setWindowOpacity(0.9);
    ui->setupUi( this );

    ui->statusbar->hide();
    this->setAcceptDrops( true ); //设置接受拖拽

    setWindowFlags( Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint ); //设置无标题栏窗体

    setWindows = new SetWin;

    //设置窗体背景颜色。
    QPalette palette( this->palette() );
    palette.setColor( QPalette::Background, Qt::black );
    this->setPalette( palette );

    // ui->textEdit->setEnabled(false);
    ui->lineEdit->setEnabled( false );

    // ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // TODO: 总结窗口增加右键菜单
    setContextMenuPolicy( Qt::ActionsContextMenu );
    QAction* openFileMenu = new QAction( MENU_SELECT, this );
    QAction* setMenu      = new QAction( MENU_SET, this );
    QAction* exportMenu   = new QAction( MENU_EXPORT, this );
    QAction* lineMenu     = new QAction( this );
    lineMenu->setSeparator( true ); //增加分割线
    QAction* abortMenu = new QAction( MENU_ABORT, this );
    QAction* exitMenu  = new QAction( MENU_EXIT, this );

    addAction( openFileMenu );
    // addAction(setMenu);
    addAction( exportMenu );
    addAction( lineMenu );
    addAction( abortMenu );
    addAction( exitMenu );

    connect( setMenu, SIGNAL( triggered( bool ) ), this, SLOT( on_action_Menu_triggered() ) );
    connect( openFileMenu, SIGNAL( triggered( bool ) ), this, SLOT( on_action_Menu_triggered() ) );
    connect( exportMenu, SIGNAL( triggered( bool ) ), this, SLOT( on_action_Menu_triggered() ) );
    connect( lineMenu, SIGNAL( triggered( bool ) ), this, SLOT( on_action_Menu_triggered() ) );
    connect( abortMenu, SIGNAL( triggered( bool ) ), this, SLOT( on_action_Menu_triggered() ) );
    connect( exitMenu, SIGNAL( triggered( bool ) ), this, SLOT( on_action_Menu_triggered() ) );
}

MainWindow::~MainWindow() {
    delete setWindows;
    delete ui;
}

void MainWindow::dragEnterEvent( QDragEnterEvent* event ) {
    if ( event->mimeData()->hasUrls() ) {
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void MainWindow::dropEvent( QDropEvent* event ) {

    //获取文件路径 (QString)
    QList<QUrl> urls = event->mimeData()->urls();
    if ( urls.isEmpty() )
        return;
    m_filePath = urls.first().toLocalFile();
    QString qName = urls.first().fileName();
    m_fileName = qName.split( "." ).at( 0 );
    QFileInfo fileinfo( m_filePath );
    if ( !fileinfo.isFile() ) {
        //路径
        isfile = false;
        ui->lineEdit->setText( m_filePath );
    }
    else {
        //文件
        isfile = true;
        ui->lineEdit->setText( qName );
    }
}

void MainWindow::mousePressEvent( QMouseEvent* e ) {
    if ( e->button() == Qt::LeftButton ) {
        isDrag     = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWindow::mouseMoveEvent( QMouseEvent* e ) {
    if ( isDrag && ( e->buttons() && Qt::LeftButton ) ) {
        move( e->globalPos() - m_position );
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent( QMouseEvent* ) {
    isDrag = false;
}

void MainWindow::printfText( QString tStr, int tColor ) {
    if ( tColor == TEXT_COLOR_BLUE ) {
        ui->textEdit->setTextColor( Qt::blue );
    }
    else if ( tColor == TEXT_COLOR_GREEN ) {
        ui->textEdit->setTextColor( Qt::green );
    }
    else if ( tColor == TEXT_COLOR_RED ) {
        ui->textEdit->setTextColor( Qt::red );
    }
    else {
        ui->textEdit->setTextColor( Qt::black );
    }

    ui->textEdit->append( tStr );
}

void MainWindow::readVersionFile( QString filePath ) {
    qDebug() << filePath;
    QTextCodec* codec = QTextCodec::codecForName( "GB2312" );
    QFile file( filePath );
    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        while ( !file.atEnd() ) {
            QByteArray line = file.readLine();
            QString str     = codec->toUnicode( line );

            if ( str == "\n" )
                continue;
        }
        file.close();
    }
}

void MainWindow::on_cmdButton_clicked() {
    ui->textEdit->clear();
    firstThread    = new QThread; //线程容器
    myObjectThread = new MyThread;
    myObjectThread->moveToThread( firstThread ); //将创建的对象移到线程容器中
    connect( firstThread, SIGNAL( finished() ), myObjectThread,
             SLOT( deleteLater() ) ); //终止线程时要调用deleteLater槽函数
    connect( firstThread, SIGNAL( started() ), myObjectThread,
             SLOT( startThreadSlot() ) ); //开启线程槽函数
    connect( myObjectThread, SIGNAL( checkFinishiSignal() ), this, SLOT( finishedThreadSlot() ) );
    connect( myObjectThread, SIGNAL( writeLogSignal( QString, int ) ), this,
             SLOT( writLogSlog( QString, int ) ) );

    closeThreadSlot();

    myObjectThread->initThread( m_filePath, isfile, firstThread );

    firstThread->start(); //开启多线程槽函数
}

void MainWindow::on_action_Menu_triggered() {

    //使用Qt的类型转换，将指针恢复为QAction类型
    QAction* act = qobject_cast<QAction*>( sender() );
    // printfText(act->text(), true);
    if ( act->text() == MENU_SELECT ) {
        QUrl url = QFileDialog::getOpenFileUrl( this, tr( "导入文件或文件夹" ) );

        m_filePath    = url.toLocalFile();
        QString qName = url.fileName();
        m_fileName    = qName.split( "." ).at( 0 );
        QFileInfo fileinfo( m_filePath );
        if ( !fileinfo.isFile() ) {
            //路径
            isfile = false;
            ui->lineEdit->setText( m_filePath );
        }
        else {
            //文件
            isfile = true;
            ui->lineEdit->setText( qName );
        }
    }

    else if ( act->text() == MENU_SET ) {

        setWindows->show();
    }
    else if ( act->text() == MENU_EXPORT ) {
        if ( m_ExportList.count() < 1 ) {
            printfText( "Export Error", TEXT_COLOR_RED );
        }
        else {
            QString fileName = QFileDialog::getSaveFileName(
                this, tr( "导出版本信息" ), "output.csv", tr( "版本信息文件 (*.txt" ) );
            if ( !fileName.isEmpty() ) {
                QFile file( fileName );
                if ( !file.open( QIODevice::WriteOnly ) ) {
                    QMessageBox msgBox;
                    msgBox.setText( "保存失败" );
                    msgBox.exec();
                    printfText( "导出文件Error", TEXT_COLOR_RED );
                }
                else {
                    QString qs;
                    for ( int i = 0; i < m_ExportList.count(); i++ ) {
                        qs.append( m_ExportList.at( i ) );

                        qs.append( "\n" );
                    }
                    QTextStream stream( &file );
                    stream << qs;
                    stream.flush();
                    file.close();
                    printfText( "导出文件OK", TEXT_COLOR_GREEN );
                }
            }
        }
    }
    else if ( act->text() == MENU_EXIT ) {
        QApplication* app = nullptr;
        app->exit( 0 );
    }
    else if ( act->text() == MENU_ABORT ) {
        AbortWin* abortWindows = new AbortWin;
        abortWindows->show();
    }
}

void MainWindow::closeThreadSlot() {
    if ( firstThread->isRunning() ) {
        myObjectThread->closeThread(); //关闭线程槽函数
        firstThread->quit();           //退出事件循环
        firstThread->wait();           //释放线程槽函数资源
    }
}

void MainWindow::finishedThreadSlot() {

    qDebug() << tr( "多线程触发了finished信号123" ) << myObjectThread->m_verMap.count();
    int tNum = myObjectThread->m_verMap.count();
    printfText( QString( "查询结束: 查询个数为: %1" ).arg( tNum ),
                tNum < 1 ? TEXT_COLOR_RED : TEXT_COLOR_GREEN );

    ui->textEdit->clear();

    for ( int i = 0; i < myObjectThread->m_verMap.count(); i++ ) {
        QString verionStr = QString( "--->%1   %2\n%3 \n" )
                                .arg( i )
                                .arg( myObjectThread->m_verMap.keys().at( i ) )
                                .arg( myObjectThread->m_verMap.values().at( i ) );
        qDebug() << verionStr;

        QString valueRaw = myObjectThread->m_verMap.values().at( i );
        QStringList valueList = valueRaw.split("\n");
        QString valueAllStr;
        foreach (QString tmpStr, valueList) {
            valueAllStr += tmpStr;
            valueAllStr += QString(",");
        }
        QString exportStr = QString( "  %1  ,  %2  " )
                                .arg( myObjectThread->m_verMap.keys().at( i ) )
                                .arg( valueAllStr );

        m_ExportList.append( exportStr );

        if ( myObjectThread->m_verMap.values().at( i ).contains( "version" ) ) {
            printfText( verionStr, TEXT_COLOR_BLUE );
        }
        else {
            printfText( verionStr, TEXT_COLOR_RED );
        }
    }

    if ( firstThread->isRunning() ) {
        firstThread->quit(); //退出事件循环
        firstThread->wait(); //释放线程槽函数资源
    }
}

void MainWindow::writLogSlog( QString log, int color ) {
    printfText( log, color );
}

MyThread::MyThread( QObject* parent ) : QObject( parent ) {
    isStop = false;
}

void MyThread::closeThread() {
    isStop = true;
}

versionMap MyThread::checkVersionThread( QString tStr, bool isPath ) {
    versionMap rMap;
    QString rfullPath;
    QString version;

    if ( !isPath ) {

        emit writeLogSignal( tr( "当前查询为文件夹" ), TEXT_COLOR_BLUE );
        //设置要遍历的目录
        QDir dir( tStr );

        //将过滤后的文件名称存入到files列表中
        QStringList files = dir.entryList( QDir::Files | QDir::Readable, QDir::Name );

        int total = files.count();
        for ( int i = 0; i < total; ++i ) {

#ifdef Q_OS_WIN
            rfullPath = tStr + "/" + files.at( i );
#endif
#ifdef Q_OS_LINUX
            rfullPath = tStr + "/" + files.at( i );
#endif
#ifdef Q_OS_MACOS
            rfullPath = tStr + files.at( i );
#endif

            version = checkVersionThread( rfullPath );
            rMap.insert( rfullPath, version );
        }
    }
    else {
        emit writeLogSignal( tr( "当前查询为文件" ), TEXT_COLOR_BLUE );
        rfullPath = tStr;
        version   = checkVersionThread( rfullPath );
        rMap.insert( rfullPath, version );
    }
    return rMap;
}

QString MyThread::checkVersionThread( QString tFile ) {
    QString rStr;
    QStringList argument;
    QProcess m_process;
    // MacOS
    {
#ifdef Q_OS_MACOS

        m_process.setProgram( "bash" );

        argument << "strings ";
        argument << tFile;
        argument << " | ";
        argument << " grep version:";
        QString bashStr = argument.join( "" );

        m_process.start();
        m_process.write( bashStr.toUtf8() );
        m_process.closeWriteChannel();
        m_process.waitForFinished(); //等待程序关闭
        // m_process.waitForReadyRead();

        rStr = QString::fromLocal8Bit( m_process.readAllStandardOutput() );
        m_process.close();

        //程序输出信息
        emit writeLogSignal( QString( "当前查询: %1" ).arg( rStr ), TEXT_COLOR_BLUE );

#endif
    }
    // Linux
    {
#ifdef Q_OS_LINUX

        m_process.setProgram( "bash" );

        argument << "strings ";
        argument << tFile;
        argument << " | ";
        argument << " grep version:";
        QString bashStr = argument.join( "" );

        m_process.start();
        m_process.write( bashStr.toUtf8() );
        m_process.closeWriteChannel();
        m_process.waitForFinished(); //等待程序关闭
        // m_process.waitForReadyRead();

        rStr = QString::fromLocal8Bit( m_process.readAllStandardOutput() );
        m_process.close();

        //程序输出信息
        emit writeLogSignal( QString( "当前查询: %1" ).arg( rStr ), TEXT_COLOR_BLUE );
#endif
    }
    // Win
    {
#ifdef Q_OS_WIN

        emit writeLogSignal( QString( "当前查询: %1" ).arg( tFile ), TEXT_COLOR_BLUE );
        QStringList searchList;

        //MD5
        rStr += checkMD5CMD(tFile);

        //Version
        searchList << "version"<< "Version"<< "VERSION";
        foreach ( QString searchStr, searchList ) {
            rStr += checkVersionCMD( tFile, searchStr );
        }
#endif
    }
    return rStr;
}
QString MyThread::checkMD5CMD(QString tFile){

    QString rStr;
    QStringList argument;
    QProcess process;
    QString cmdStr;
    QString path;
    QString strTemp;//MD5

#if 1  //MD5
    process.setProgram( "cmd" );
    path = QDir::toNativeSeparators( tFile ); //路径转换
    argument << "certutil " << " -hashfile " << "\"\"" << tFile << "\"\""  << " MD5";
    cmdStr = argument.join( "" );
    process.start( "cmd" );
    process.waitForStarted();
    process.write( cmdStr.toLocal8Bit() );
    process.write( "\n\r" );
    process.closeWriteChannel();
    process.waitForFinished();
    strTemp = QString::fromLocal8Bit( process.readAllStandardOutput() );//resoult
    //qDebug() <<"MD5:    " << strTemp2  ;
#endif

#if 1 //out MD5
        strTemp.remove( QRegExp( "\\s" ) );
        if ( strTemp.contains( "哈希:", Qt::CaseInsensitive ) ) {
            QStringList verList = strTemp.split( "哈希:" );

            QString ttStr = verList[1];
             if ( ttStr.contains( "CertUtil", Qt::CaseInsensitive ) ) {
                 QStringList verList2 = ttStr.split( "CertUtil" );
                 QString vvStr = verList2[0];
                 vvStr.replace( QString( "\r\n" ), QString( "" ) );
                 //qDebug() << vvStr;
                 vvStr += QString("\n");
                 return vvStr;
             }
        }
#endif
}

QString MyThread::checkVersionCMD( QString tFile, QString tStr ) {

    QString rStr;
    QStringList argument;
    QProcess process;
    QString cmdStr;
    QString path;
    QString strTemp;//version

#if 1  //version
    process.setProgram( "cmd" );
    path = QDir::toNativeSeparators( tFile ); //路径转换
    argument << "find " << "\"" << tStr << "\" " << "\"\"" << tFile << "\"\""  << "";

    cmdStr = argument.join( "" );
    process.start( "cmd" );
    process.waitForStarted();
    process.write( cmdStr.toLocal8Bit() );
    process.write( "\n\r" );
    process.closeWriteChannel();
    process.waitForFinished();
    strTemp = QString::fromLocal8Bit( process.readAllStandardOutput() );//resoult
    qDebug() <<"Version:    " << strTemp  <<"\n\n\n";
#endif

#if 1 //new
    QStringList outList = strTemp.split( "\r\n" );//按照行读取
    for ( int lineNum = 0; lineNum < outList.count(); ++lineNum ) {
        QString tmpStr = outList.at( lineNum );
        tmpStr.remove( QRegExp( "\\s" ) );
        if ( tmpStr.contains( "version", Qt::CaseInsensitive ) ) {//检测是否包含Version
            tmpStr.replace( QString( ":" ), QString( "" ) );
            tmpStr.replace( QString( "=" ), QString( "" ) );
            QStringList verList = tmpStr.split( tStr );//用version[区分大小写]分割，读取后面的版本
            if(verList.count() <2) continue;
            foreach ( QString verStr, verList ) {
                if ( verStr.contains( "v2.0", Qt::CaseInsensitive ) ) {
               // if ( verStr.contains( "version", Qt::CaseInsensitive ) ) {//版本都包括V2.0
                   // m_version = verStr;
                    //rStr = QString("%1\n %2").arg(rStr).arg(verStr);
                   rStr += QString( "%1" ).arg( verStr );
                    rStr += QString("\n");
                    //qDebug() << verStr;
               }
            }
        }
    }
    return rStr;
#endif

#if 0 //old
    QStringList outList = strTemp.split( "\r\n" );
    for ( int lineNum = 0; lineNum < outList.count(); ++lineNum ) {
        QString tmpStr = outList.at( lineNum );
        tmpStr.remove( QRegExp( "\\s" ) );
        if ( tmpStr.contains( "version", Qt::CaseInsensitive ) ) {
            tmpStr.replace( QString( ":" ), QString( "" ) );
            tmpStr.replace( QString( "=" ), QString( "" ) );
            QStringList verList = tmpStr.split( tStr );
            foreach ( QString verStr, verList ) {
                if ( verStr.contains( "v2.0", Qt::CaseInsensitive ) ) {
                   // m_version = verStr;
                  //  rStr      = QString( "version: %1" ).arg( m_version );
                    qDebug() << rStr;
                    return rStr;
                }
            }
        }
    }
#endif
}

void MyThread::initThread( QString tStr, bool isPath, QThread* tThread ) {
    m_filePath = tStr;
    isfile     = isPath;
    m_thread   = tThread;
}

void MyThread::startThreadSlot() {
    emit writeLogSignal( tr( "开始查询" ), TEXT_COLOR_GREEN );
    m_verMap = checkVersionThread( m_filePath, isfile );
    emit checkFinishiSignal();
}
