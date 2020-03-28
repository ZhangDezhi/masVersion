#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTextStream>
#include <QAction>
#include <QProcess>
#include <QDir>
#include "default.h"
#include "setwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
 Q_OBJECT

public:
 MainWindow(QWidget *parent = nullptr);
 ~MainWindow();

private slots:
 void on_cmdButton_clicked();
 void on_action_Menu_triggered();


private:
 Ui::MainWindow *ui;
 bool isDrag;
 QPoint m_position;
 QString m_filePath;


  //重写窗口拖拽
  void dragEnterEvent(QDragEnterEvent* event);
  void dropEvent(QDropEvent* event);

  //重写鼠标拖动
  void mouseReleaseEvent(QMouseEvent *);


  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);

 //打印
 void printfText(QString str, bool isError);


};
#endif // MAINWINDOW_H
