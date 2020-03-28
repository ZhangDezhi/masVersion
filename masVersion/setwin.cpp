#include "setwin.h"
#include "ui_setwin.h"

SetWin::SetWin(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SetWin)
{

  //设置窗体大小
  setFixedSize(365,240);

  //设置透明
  setWindowOpacity(0.8);
  ui->setupUi(this);


  this->setAcceptDrops(true);//设置接受拖拽
  setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);//设置无标题栏窗体

  //设置窗体背景颜色。
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, Qt::cyan);
  this->setPalette(palette);

  //置顶
  Qt::WindowFlags m_flags = windowFlags();
  setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);

  ui->setupUi(this);

}

SetWin::~SetWin()
{
  delete ui;
}
