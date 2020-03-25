#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  bool isDrag;
  QPoint m_position;

  //重写拖拽
  void dragEnterEvent(QDragEnterEvent* event);
  void dropEvent(QDropEvent* event);
  //重写鼠标拖动

  void mouseReleaseEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
};
#endif // MAINWINDOW_H
