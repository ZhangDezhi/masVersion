#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <sstream>

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  //设置窗体大小
  setFixedSize(365,240);

  //设置透明
  setWindowOpacity(0.8);
  ui->setupUi(this);

  ui->statusbar->hide();
  this->setAcceptDrops(true);//设置接受拖拽
  setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);//设置无标题栏窗体

  //设置窗体背景颜色。
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, Qt::black);
  this->setPalette(palette);

  ui->textEdit->setEnabled(false);
  ui->lineEdit->setEnabled(false);

  //TODO: 总结窗口增加右键菜单
  setContextMenuPolicy(Qt::ActionsContextMenu);
  QAction *setMenu = new QAction("设置",this);
  QAction *openFileMenu = new QAction("选择文件",this);
  QAction *exportMenu = new QAction("导出",this);
  QAction *lineMenu=new QAction(this);
  lineMenu->setSeparator(true);//增加分割线
  QAction *abortMenu = new QAction("关于",this);
  QAction *exitMenu = new QAction("退出",this);

  addAction(openFileMenu);
  addAction(setMenu);
  addAction(exportMenu);
  addAction(lineMenu);
  addAction(abortMenu);
  addAction(exitMenu);
 // connect(setMenu,SIGNAL(triggered(bool)),this,SLOT(on_action_NewMenu_triggered()));
 // connect(openFileMenu,SIGNAL(triggered(bool)),this,SLOT(on_action_NewMenu_triggered()));
  //connect(exportMenu,SIGNAL(triggered(bool)),this,SLOT(on_action_NewMenu_triggered()));
  //connect(lineMenu,SIGNAL(triggered(bool)),this,SLOT(on_action_NewMenu_triggered()));
  //connect(abortMenu,SIGNAL(triggered(bool)),this,SLOT(on_action_NewMenu_triggered()));
  //connect(exitMenu,SIGNAL(triggered(bool)),this,SLOT(on_action_NewMenu_triggered()));



}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
  if(event->mimeData()->hasUrls())
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
  //  const QMimeData* mimeData = event->mimeData();
  //  if(mimeData->hasUrls())
  //  {
  //    QList<QUrl>urlList = mimeData->urls();
  //    QString fileName = urlList.at(0).toLocalFile();
  //    if(!fileName.isEmpty())
  //    {
  //      QFile file(fileName);
  //      if(!file.open(QIODevice::ReadOnly))return;
  //      QTextStream in(&file);
  //      ui->textEdit->setText(in.readAll());
  //    }
  //  }

  //获取文件路径 (QString)
  QList<QUrl> urls = event->mimeData()->urls();
  if (urls.isEmpty()) return;
  m_filePath = urls.first().toLocalFile();
  QString qName = urls.first().fileName();

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

  //qDebug() << m_filePath;



  ui->lineEdit->setText(qName);

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
  if(e->button() == Qt::LeftButton)
  {
    isDrag = true;
    m_position = e->globalPos() - this->pos();
    e->accept();
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
  if(isDrag && (e->buttons() && Qt::LeftButton))
  {
    move(e->globalPos() - m_position);
    e->accept();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
  isDrag = false;
}

void MainWindow::printfText(QString str, bool isError)
{
  if(isError){
      ui->textEdit->setTextColor(Qt::red);
    }

    ui->textEdit->append(str);
}

void MainWindow::on_cmdButton_clicked()
{

 //参考: https://blog.csdn.net/believe_s/article/details/82318860
 ui->textEdit->clear();
 //#file
 QProcess process(this);
 QString cmdstr ;
 cmdstr = QString("find \"version\" %1\n").arg(m_filePath);
 cmdstr.replace(QString("\""), QString(""));
 qDebug()<<cmdstr;// qDebug().noquote()<<cmdstr;

 process.setProgram("cmd");
 QStringList argument;
 argument<<"/c"<< cmdstr;
 qDebug()<<"list2="<<argument;



 process.setArguments(argument);
 process.start();
 process.waitForStarted(); //等待程序启动
 process.waitForFinished();//等待程序关闭
 QString temp=QString::fromLocal8Bit(process.readAllStandardOutput()); //程序输出信息

 qDebug()<<temp;
 printfText(temp,true);


 }


