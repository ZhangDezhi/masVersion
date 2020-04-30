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
   // setWindowFlags(Qt::FramelessWindowHint |
   //                Qt::WindowMinimizeButtonHint); //设置无标题栏窗体

    //设置窗体背景颜色。
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    ui->textEdit->setEnabled(false);
    //ui->textEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    // ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // TODO: 总结窗口增加右键菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* setMenu      = new QAction(MENU_SELECT, this);
    QAction* openFileMenu = new QAction(MENU_SET, this);
    QAction* exportMenu   = new QAction(MENU_EXPORT, this);
    QAction* lineMenu     = new QAction(this);
    lineMenu->setSeparator(true); //增加分割线

    QAction* abortMenu = new QAction(MENU_EXPORT, this);
    QAction* exitMenu  = new QAction(MENU_EXIT, this);

    addAction(openFileMenu);
    addAction(setMenu);
    addAction(exportMenu);
    addAction(lineMenu);
    addAction(abortMenu);
    addAction(exitMenu);
    connect(setMenu,
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_action_Menu_triggered()));
    connect(openFileMenu,
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_action_Menu_triggered()));
    connect(exportMenu,
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_action_Menu_triggered()));
    connect(lineMenu,
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_action_Menu_triggered()));
    connect(abortMenu,
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_action_Menu_triggered()));
    connect(exitMenu,
            SIGNAL(triggered(bool)),
            this,
            SLOT(on_action_Menu_triggered()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}


void MainWindow::dropEvent(QDropEvent* event) {
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
    if (urls.isEmpty()) return;

    m_filePath = urls.first().toLocalFile();

    // QFileInfo fileInfo(urls.first().path());
    // m_fileName=fileInfo.fileName();

    QString qName = urls.first().fileName();

    m_fileName = qName.split(".").at(0);

    if(m_fileName.isEmpty()){
        //路径
         qDebug() << m_filePath;
         isfile = false;
          ui->lineEdit->setText(m_filePath);
    }
    else{
        //文件
        isfile = true;
         ui->lineEdit->setText(qName);
         qDebug() << "----------->" << m_fileName;
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
    qDebug() << "123";
    qDebug() << tr("鼠标进入主界面事件");
}

void MainWindow::leaveEvent(QEvent*) { qDebug() << tr("鼠标离开主界面事件"); }

void MainWindow::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        isDrag     = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWindow::wheelEvent(QWheelEvent* event) {
    return;
    QTextCursor tmpCursor = ui->textEdit->textCursor();
    if (event->delta() > 0) //当滚轮向上滑，远离使用者
    {

        QTextCursor tmpCursor = ui->textEdit->textCursor();
        if (!tmpCursor.atBlockStart()) {
            ui->textEdit->moveCursor(QTextCursor::StartOfBlock);
            //  tmpCursor.setPosition(QTextCursor::StartOfBlock);

            // tmpCursor.movePosition(QTextCursor::StartOfBlock,
            // QTextCursor::MoveAnchor, 1);
            qDebug() << "------------>>>1";
            //  ui->textEdit->setTextCursor(tmpCursor);
        }

        //  tmpCursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, 4);

        ui->textEdit->moveCursor(QTextCursor::Up);
    } else //当滚轮向下滑，靠近使用者
    {
        if (!tmpCursor.atBlockEnd()) {
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

void MainWindow::mouseMoveEvent(QMouseEvent* e) {
    if (isDrag && (e->buttons() && Qt::LeftButton)) {
        move(e->globalPos() - m_position);
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent*) { isDrag = false; }

void MainWindow::printfText(QString tStr, int tColor) {
    if (tColor == 0) {
        ui->textEdit->setTextColor(Qt::blue);
    } else if (tColor == 1) {
        ui->textEdit->setTextColor(Qt::green);
    } else if (tColor == 2) {
        ui->textEdit->setTextColor(Qt::red);
    } else {
        ui->textEdit->setTextColor(Qt::black);
    }

    ui->textEdit->append(tStr);
}

QString MainWindow::searchVersionFile(QString tPath, QString tName) {
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
    QStringList files = dir.entryList(
            nameFilters, QDir::Files | QDir::Readable, QDir::Name);

    int total = files.count();
    for (int i = 0; i < total; ++i) {

        if (files.at(i).contains(tName, Qt::CaseInsensitive)) {
            // printfText(files.at(i),0);
            rStr = dirpath + "//" + files.at(i);

            break;
        } else {
            // printfText(files.at(i),3);
        }
    }

    return rStr;
}

void MainWindow::readVersionFile(QString filePath) {
    qDebug() << filePath;
    QTextCodec* codec = QTextCodec::codecForName("GB2312");
    QFile       file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {

            QByteArray line = file.readLine();
            QString    str  = codec->toUnicode(line);
            // qDebug() << str;

            if (str == "\n") continue;

            if (str.contains(m_version, Qt::CaseInsensitive)) {

                printfText(codec->toUnicode(line), 2);
            } else {
                printfText(codec->toUnicode(line), 0);
            }
        }
        file.close();
    }
}

void MainWindow::on_cmdButton_clicked() {

    ui->textEdit->clear();
    // m_process= QProcess(this);
  versionMap map =  checkVersionThread(ui->lineEdit->text(),isfile);

  qDebug() << ui->lineEdit->text();

  for (int i =0;i<map.count();i++) {

      QString verionStr = QString("%1\n%2 \n").arg(map.keys().at(i) ).arg(map.values().at(i));
      qDebug() <<verionStr;

      if(map.values().at(i).contains("version")){
          printfText(verionStr,0);
      }
      else{
           printfText(verionStr,2);
      }

  }
}

void MainWindow::on_action_Menu_triggered() {

    QAction* act = qobject_cast<QAction*>(
            sender()); //使用Qt的类型转换，将指针恢复为QAction类型
    printfText(act->text(), true);
    if (act->text() == MENU_SELECT)
    {

    }

    else if (act->text() == MENU_SET) {
        SetWin* setWindows = new SetWin;
        setWindows->show();
    } else if (act->text() == MENU_EXPORT) {

    } else if (act->text() == MENU_EXIT) {
        QApplication* app;
        app->exit(0);
    } else if (act->text() == MENU_ABORT) {
    }
}
QString MainWindow::checkVersionThread(QString tFile){
    QString rStr;
#ifdef Q_OS_MACOS
#endif
    m_process.setProgram("bash");
    QStringList argument;
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

    rStr= QString::fromLocal8Bit(m_process.readAllStandardOutput());
    m_process.close();

    //程序输出信息
    qDebug() << rStr;


#ifdef Q_OS_LINUX
#endif

#ifdef Q_OS_WIN

    // TODO: QProcess qDebug()<<cmdstr;// qDebug().noquote()<<cmdstr;
    m_process.setProgram("cmd");
    QStringList argument;
    argument << "/c"
             << "find "
             << ""
                "version:"
                ""
             << " " << tFile;

    m_process.setArguments(argument);
    m_process.start();
    m_process.waitForStarted();  //等待程序启动
    m_process.waitForFinished(); //等待程序关闭
    QString cmdOutStr = QString::fromLocal8Bit(
            m_process.readAllStandardOutput()); //程序输出信息
    qDebug() << cmdOutStr;
    QStringList outList = cmdOutStr.split("\r\n");
    for (int lineNum = 0; lineNum < outList.count(); ++lineNum) {
        QString tmpStr = outList.at(lineNum);

        tmpStr.remove(QRegExp("\\s"));

        if (tmpStr.contains("version", Qt::CaseInsensitive)) {
            qDebug() << tmpStr;
            tmpStr.replace(QString(":"), QString(""));
            m_version          = tmpStr.split("version").at(1);
            rStr = QString("当前版本为: %1").arg(m_version);
            printfText(rStr, 2);

            printfText("", 0);
            printfText("", 0);
            printfText("-------------------------", 0);
            printfText("update List:", 0);

           // readVersionFile(searchVersionFile("", m_fileName));
            break;
        }
    }

#endif
    return  rStr;
}
versionMap MainWindow::checkVersionThread(QString tStr,bool isfile)
{
    versionMap rMap;
    QString rfullPath;
    QString version ;

    if(!isfile){

        //设置要遍历的目录
        QDir dir(tStr);

        //将过滤后的文件名称存入到files列表中
        QStringList files = dir.entryList( QDir::Files | QDir::Readable, QDir::Name);

        int total = files.count();
        for (int i = 0; i < total; ++i) {


           // rStr = tStr + "//" + files.at(i);
            rfullPath = tStr  + files.at(i);
            version = checkVersionThread(rfullPath);
            rMap.insert(rfullPath,version);

        }
    }
    else{
        rfullPath = tStr;
        version = checkVersionThread(rfullPath);
        rMap.insert(rfullPath,version);

    }
    return  rMap;
}
