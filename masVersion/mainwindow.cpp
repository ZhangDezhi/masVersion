#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
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
  QString qStr = urls.first().toLocalFile();
  QString qName = urls.first().fileName();

  //转为char*
  QByteArray qByteArrary = qStr.toLatin1();
  char* filePath = qByteArrary.data();



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

  qDebug() << qStr;



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
