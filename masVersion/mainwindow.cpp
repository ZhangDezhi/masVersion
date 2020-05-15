#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //设置窗体大小
    setFixedSize(365, 240);

    //设置透明
    // setWindowOpacity(0.9);
    ui->setupUi(this);

    ui->statusbar->hide();
    this->setAcceptDrops(true); //设置接受拖拽

    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::WindowMinimizeButtonHint); //设置无标题栏窗体

    setWindows = new SetWin;

    //设置窗体背景颜色。
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    // ui->textEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    // ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // TODO: 总结窗口增加右键菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* openFileMenu = new QAction(MENU_SELECT, this);
    QAction* setMenu      = new QAction(MENU_SET, this);
    QAction* exportMenu   = new QAction(MENU_EXPORT, this);
    QAction* lineMenu     = new QAction(this);
    lineMenu->setSeparator(true); //增加分割线
    QAction* abortMenu = new QAction(MENU_ABORT, this);
    QAction* exitMenu  = new QAction(MENU_EXIT, this);

    addAction(openFileMenu);
    // addAction(setMenu);
    addAction(exportMenu);
    addAction(lineMenu);
    addAction(abortMenu);
    addAction(exitMenu);

    connect(setMenu, SIGNAL(triggered(bool)), this,
            SLOT(on_action_Menu_triggered()));
    connect(openFileMenu, SIGNAL(triggered(bool)), this,
            SLOT(on_action_Menu_triggered()));
    connect(exportMenu, SIGNAL(triggered(bool)), this,
            SLOT(on_action_Menu_triggered()));
    connect(lineMenu, SIGNAL(triggered(bool)), this,
            SLOT(on_action_Menu_triggered()));
    connect(abortMenu, SIGNAL(triggered(bool)), this,
            SLOT(on_action_Menu_triggered()));
    connect(exitMenu, SIGNAL(triggered(bool)), this,
            SLOT(on_action_Menu_triggered()));
}

MainWindow::~MainWindow()
{
    delete setWindows;
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent* event)
{
    //      const QMimeData* mimeData = event->mimeData();
    //      if(mimeData->hasUrls())
    //      {
    //        QList<QUrl>urlList = mimeData->urls();
    //        QString fileName = urlList.at(0).toLocalFile();
    //        if(!fileName.isEmpty())
    //        {
    //          QFile file(fileName);
    //          if(!file.open(QIODevice::ReadOnly))return;
    //          QTextStream in(&file);
    //          ui->textEdit->setText(in.readAll());
    //        }
    //      }

    //获取文件路径 (QString)
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    m_filePath = urls.first().toLocalFile();

    // QFileInfo fileInfo(urls.first().path());
    // m_fileName=fileInfo.fileName();

    QString qName = urls.first().fileName();

    m_fileName = qName.split(".").at(0);

    QFileInfo fileinfo(m_filePath);

    if (!fileinfo.isFile())
    {
        //路径
        isfile = false;
        ui->lineEdit->setText(m_filePath);
    }
    else
    {
        //文件
        isfile = true;
        ui->lineEdit->setText(qName);
    }

    //转为char*
    // QByteArray qByteArrary = qStr.toLatin1();
    // char* filePath = qByteArrary.data();

    //  QString file_full, file_name, file_path，file_suffix ;
    //  QFileInfo fileinfo;
    //  file_full = QFileDialog::getOpenFileName(this,.....);
    //  fileinfo = QFileInfo(file_full);
    //  //文件名
    //  file_name = fileinfo.fileName();
    //  //文件后缀
    //  file_suffix = fileinfo.suffix()
    //  //绝对路径
    //  file_path = fileinfo.absolutePath();

    // qDebug() << m_filePath;
}

void MainWindow::enterEvent(QEvent*)
{

    // if(button->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    //    qDebug() << "123";
    //    qDebug() << tr("鼠标进入主界面事件");
}

void MainWindow::leaveEvent(QEvent*)
{
    // qDebug() << tr("鼠标离开主界面事件");
}

void MainWindow::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        isDrag     = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
    return;
    QTextCursor tmpCursor = ui->textEdit->textCursor();
    if (event->delta() > 0) //当滚轮向上滑，远离使用者
    {

        QTextCursor tmpCursor = ui->textEdit->textCursor();
        if (!tmpCursor.atBlockStart())
        {
            ui->textEdit->moveCursor(QTextCursor::StartOfBlock);
            //  tmpCursor.setPosition(QTextCursor::StartOfBlock);

            // tmpCursor.movePosition(QTextCursor::StartOfBlock,
            // QTextCursor::MoveAnchor, 1);
            qDebug() << "------------>>>1";
            //  ui->textEdit->setTextCursor(tmpCursor);
        }

        //  tmpCursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, 4);

        ui->textEdit->moveCursor(QTextCursor::Up);
    }
    else //当滚轮向下滑，靠近使用者
    {
        if (!tmpCursor.atBlockEnd())
        {
            ui->textEdit->moveCursor(QTextCursor::EndOfBlock);
            // tmpCursor.setPosition(QTextCursor::EndOfBlock);
            // tmpCursor.movePosition(QTextCursor::EndOfBlock,
            // QTextCursor::MoveAnchor, 1);
            qDebug() << "------------>>>2";
            //  ui->textEdit->setTextCursor(tmpCursor);
        }
        ui->textEdit->moveCursor(QTextCursor::Down);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    if (isDrag && (e->buttons() && Qt::LeftButton))
    {
        move(e->globalPos() - m_position);
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent*)
{
    isDrag = false;
}

void MainWindow::printfText(QString tStr, int tColor)
{
    if (tColor == TEXT_COLOR_BLUE)
    {
        ui->textEdit->setTextColor(Qt::blue);
    }
    else if (tColor == TEXT_COLOR_GREEN)
    {
        ui->textEdit->setTextColor(Qt::green);
    }
    else if (tColor == TEXT_COLOR_RED)
    {
        ui->textEdit->setTextColor(Qt::red);
    }
    else
    {
        ui->textEdit->setTextColor(Qt::black);
    }

    ui->textEdit->append(tStr);
}

QString MainWindow::searchVersionFile(QString tPath, QString tName)
{
    QString rStr;

    QString dirpath = "E://Server//Repository//SVN//工作//软件平台源码//"
                      "3、产品发布//1、郑州14号线//程序修改记录";
    //设置要遍历的目录
    QDir dir(dirpath);
    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤格式
    nameFilters << "*.so"
                << "*.txt"
                << "*.doc";
    //将过滤后的文件名称存入到files列表中
    QStringList files =
        dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);

    int total = files.count();
    for (int i = 0; i < total; ++i)
    {

        if (files.at(i).contains(tName, Qt::CaseInsensitive))
        {
            // printfText(files.at(i),0);
            rStr = dirpath + "//" + files.at(i);

            break;
        }
        else
        {
            // printfText(files.at(i),3);
        }
    }

    return rStr;
}

void MainWindow::readVersionFile(QString filePath)
{
    qDebug() << filePath;
    QTextCodec* codec = QTextCodec::codecForName("GB2312");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {

            QByteArray line = file.readLine();
            QString str     = codec->toUnicode(line);
            // qDebug() << str;

            if (str == "\n")
                continue;

            //            if (str.contains(m_version, Qt::CaseInsensitive))
            //            {

            //                printfText(codec->toUnicode(line),
            //                TEXT_COLOR_RED);
            //            }
            //            else
            //            {
            //                printfText(codec->toUnicode(line),
            //                TEXT_COLOR_BLUE);
            //            }
        }
        file.close();
    }
}

void MainWindow::on_cmdButton_clicked()
{

    ui->textEdit->clear();
    //

    firstThread    = new QThread; //线程容器
    myObjectThread = new MyThread;
    myObjectThread->moveToThread(firstThread); //将创建的对象移到线程容器中
    connect(firstThread, SIGNAL(finished()), myObjectThread,
            SLOT(deleteLater())); //终止线程时要调用deleteLater槽函数
    connect(firstThread, SIGNAL(started()), myObjectThread,
            SLOT(startThreadSlot())); //开启线程槽函数
    connect(myObjectThread, SIGNAL(checkFinishiSignal()), this,
            SLOT(finishedThreadSlot()));
    connect(myObjectThread, SIGNAL(writeLogSignal(QString, int)), this,
            SLOT(writLogSlog(QString, int)));

    closeThreadSlot();

    myObjectThread->initThread(m_filePath, isfile, firstThread);

    firstThread->start(); //开启多线程槽函数
}

void MainWindow::on_action_Menu_triggered()
{

    //使用Qt的类型转换，将指针恢复为QAction类型
    QAction* act = qobject_cast<QAction*>(sender());
    // printfText(act->text(), true);
    if (act->text() == MENU_SELECT)
    {
        QUrl url = QFileDialog::getOpenFileUrl(this, tr("导入文件或文件夹"));

        m_filePath = url.toLocalFile();

        // QFileInfo fileInfo(urls.first().path());
        // m_fileName=fileInfo.fileName();

        QString qName = url.fileName();

        m_fileName = qName.split(".").at(0);

        QFileInfo fileinfo(m_filePath);

        if (!fileinfo.isFile())
        {
            //路径
            isfile = false;
            ui->lineEdit->setText(m_filePath);
        }
        else
        {
            //文件
            isfile = true;
            ui->lineEdit->setText(qName);
        }
    }

    else if (act->text() == MENU_SET)
    {

        setWindows->show();
    }
    else if (act->text() == MENU_EXPORT)
    {
        if (m_ExportList.count() < 1)
        {
            printfText("Export Error", TEXT_COLOR_RED);
        }
        else
        {
            QString fileName = QFileDialog::getSaveFileName(
                this, tr("导出版本信息"), "output.txt",
                tr("版本信息文件 (*.txt"));
            if (!fileName.isEmpty())
            {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly))
                {
                    QMessageBox msgBox;
                    msgBox.setText("保存失败");
                    msgBox.exec();
                    printfText("导出文件Error", TEXT_COLOR_RED);
                }
                else
                {
                    QString qs;
                    for (int i = 0; i < m_ExportList.count(); i++)
                    {
                        qs.append(m_ExportList.at(i));

                        qs.append("\n");
                    }
                    QTextStream stream(&file);
                    stream << qs;
                    stream.flush();
                    file.close();
                    printfText("导出文件OK", TEXT_COLOR_GREEN);
                }
            }
        }
    }
    else if (act->text() == MENU_EXIT)
    {
        QApplication* app = nullptr;
        app->exit(0);
    }
    else if (act->text() == MENU_ABORT)
    {
        AbortWin* abortWindows = new AbortWin;
        abortWindows->show();
    }
}

void MainWindow::closeThreadSlot()
{
    if (firstThread->isRunning())
    {
        myObjectThread->closeThread(); //关闭线程槽函数
        firstThread->quit();           //退出事件循环
        firstThread->wait();           //释放线程槽函数资源
    }
}

void MainWindow::finishedThreadSlot()
{

    qDebug() << tr("多线程触发了finished信号123")
             << myObjectThread->m_verMap.count();
    int tNum = myObjectThread->m_verMap.count();
    printfText(QString("查询结束: 查询个数为: %1").arg(tNum),
               tNum < 1 ? TEXT_COLOR_RED : TEXT_COLOR_GREEN);

    ui->textEdit->clear();

    for (int i = 0; i < myObjectThread->m_verMap.count(); i++)
    {
        QString verionStr = QString("--->%1   %2\n%3 \n")
                                .arg(i)
                                .arg(myObjectThread->m_verMap.keys().at(i))
                                .arg(myObjectThread->m_verMap.values().at(i));
        qDebug() << verionStr;

        QString exportStr = QString("%1  ==  %2")
                                .arg(myObjectThread->m_verMap.keys().at(i))
                                .arg(myObjectThread->m_verMap.values().at(i));

        m_ExportList.append(exportStr);

        if (myObjectThread->m_verMap.values().at(i).contains("version"))
        {
            printfText(verionStr, TEXT_COLOR_BLUE);
        }
        else
        {
            printfText(verionStr, TEXT_COLOR_RED);
        }
    }

    if (firstThread->isRunning())
    {
        firstThread->quit(); //退出事件循环
        firstThread->wait(); //释放线程槽函数资源
    }
}

void MainWindow::writLogSlog(QString log, int color)
{
    printfText(log, color);
}

MyThread::MyThread(QObject* parent) : QObject(parent)
{
    isStop = false;
}

void MyThread::closeThread()
{
    isStop = true;
}

versionMap MyThread::checkVersionThread(QString tStr, bool isPath)
{
    versionMap rMap;
    QString rfullPath;
    QString version;

    if (!isPath)
    {

        emit writeLogSignal(tr("当前查询为文件夹"), TEXT_COLOR_BLUE);
        //设置要遍历的目录
        QDir dir(tStr);

        //将过滤后的文件名称存入到files列表中
        QStringList files =
            dir.entryList(QDir::Files | QDir::Readable, QDir::Name);

        int total = files.count();
        for (int i = 0; i < total; ++i)
        {

#ifdef Q_OS_WIN
            rfullPath = tStr + "/" + files.at(i);
#endif
#ifdef Q_OS_LINUX
            rfullPath = tStr + "/" + files.at(i);
#endif
#ifdef Q_OS_MACOS
            rfullPath = tStr + files.at(i);
#endif

            version = checkVersionThread(rfullPath);
            rMap.insert(rfullPath, version);
        }
    }
    else
    {
        emit writeLogSignal(tr("当前查询为文件"), TEXT_COLOR_BLUE);
        rfullPath = tStr;
        version   = checkVersionThread(rfullPath);
        rMap.insert(rfullPath, version);
    }
    return rMap;
}

QString MyThread::checkVersionThread(QString tFile)
{
    QString rStr;
    QStringList argument;
    QProcess m_process;
    // MacOS
    {
#ifdef Q_OS_MACOS

        m_process.setProgram("bash");

        argument << "strings ";
        argument << tFile;
        argument << " | ";
        argument << " grep version:";
        QString bashStr = argument.join("");

        m_process.start();
        m_process.write(bashStr.toUtf8());
        m_process.closeWriteChannel();
        m_process.waitForFinished(); //等待程序关闭
        // m_process.waitForReadyRead();

        rStr = QString::fromLocal8Bit(m_process.readAllStandardOutput());
        m_process.close();

        //程序输出信息
        emit writeLogSignal(QString("当前查询: %1").arg(rStr), TEXT_COLOR_BLUE);

#endif
    }
    // Linux
    {
#ifdef Q_OS_LINUX

        m_process.setProgram("bash");

        argument << "strings ";
        argument << tFile;
        argument << " | ";
        argument << " grep version:";
        QString bashStr = argument.join("");

        m_process.start();
        m_process.write(bashStr.toUtf8());
        m_process.closeWriteChannel();
        m_process.waitForFinished(); //等待程序关闭
        // m_process.waitForReadyRead();

        rStr = QString::fromLocal8Bit(m_process.readAllStandardOutput());
        m_process.close();

        //程序输出信息
        emit writeLogSignal(QString("当前查询: %1").arg(rStr), TEXT_COLOR_BLUE);
#endif
    }
    // Win
    {
#ifdef Q_OS_WIN



        emit writeLogSignal(QString("当前查询: %1").arg(tFile),
                            TEXT_COLOR_BLUE);
        QStringList searchList ;

        searchList << "version"
                   << "Version"
                   << "VERSION";
        foreach (QString searchStr, searchList) {
          rStr =  checkVersionCMD(tFile,searchStr);
          if(rStr.length() > 1)
              return rStr;
        }

#endif
    }
    return rStr;
}

QString MyThread::checkVersionCMD(QString tFile, QString tStr)
{
    QString rStr;
    QStringList argument;
    QProcess process;
    process.setProgram("cmd");
    QString path = QDir::toNativeSeparators(tFile); //路径转换
    argument << " findstr "
             << tStr
             << " " << path << " | "
             << "find"
             << " "
             << "\""
             << tStr
             << "\"";

    QString cmdStr = argument.join("");

    process.start("cmd");
    process.waitForStarted();
    process.write(cmdStr.toUtf8());
    process.write("\n\r");
    process.closeWriteChannel();
    process.waitForFinished();
    QString strTemp =
        QString::fromLocal8Bit(process.readAllStandardOutput());

    QStringList outList = strTemp.split("\r\n");
    for (int lineNum = 0; lineNum < outList.count(); ++lineNum)
    {
        QString tmpStr = outList.at(lineNum);

        tmpStr.remove(QRegExp("\\s"));
        if (tmpStr.contains("version", Qt::CaseInsensitive))
        {
            tmpStr.replace(QString(":"), QString(""));
            tmpStr.replace(QString("="), QString(""));
            QStringList verList = tmpStr.split(tStr);
            foreach (QString verStr, verList)
            {
                if (verStr.contains("v2.0", Qt::CaseInsensitive))
                {
                    m_version = verStr;
                    rStr      = QString("version: %1").arg(m_version);
                    qDebug() << rStr;
                    // readVersionFile(searchVersionFile("", m_fileName));
                    return rStr;
                }
            }
        }
    }
}

void MyThread::initThread(QString tStr, bool isPath, QThread *tThread)
{
    m_filePath = tStr;
    isfile = isPath;
    m_thread = tThread;
}



void MyThread::startThreadSlot()
{

    emit  writeLogSignal(tr("开始查询"),TEXT_COLOR_GREEN);
    m_verMap =checkVersionThread(m_filePath, isfile);
    emit  checkFinishiSignal();

}










