#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "default.h"
#include "setwin.h"
#include <QAction>
#include <QDir>
#include <QDragEnterEvent>
#include <QFile>
#include <QMainWindow>
#include <QMimeData>
#include <QProcess>
#include <QTextCodec>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void on_cmdButton_clicked();
    void on_action_Menu_triggered();

  private:
    Ui::MainWindow* ui;
    bool isDrag;
    QPoint m_position;
    QString m_fileName;
    QString m_filePath;
    QString m_version;
    QProcess m_process;

    //重写窗口拖拽
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

    void enterEvent(QEvent*); //进入QWidget瞬间事件
    void leaveEvent(QEvent*); //离开QWidget瞬间事件

    //重写鼠标拖动
    void mouseReleaseEvent(QMouseEvent*);

    void mouseMoveEvent(QMouseEvent* e); //摁住鼠标事件
    void mousePressEvent(QMouseEvent* e);

    //滚轮事件
    void wheelEvent(QWheelEvent* event);

    //打印
    void printfText(QString tStr, int tColor);

    //查找文件
    QString searchVersionFile(QString tPath, QString tName);

    //读取文件
    readVersionFile(QString filePath);
};
#endif // MAINWINDOW_H
