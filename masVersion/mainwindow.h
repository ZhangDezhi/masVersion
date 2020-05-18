#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QDir>
#include <QDragEnterEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QThread>
#include <QMessageBox>
#include <QMimeData>
#include <QProcess>
#include <QTextCodec>
#include <QUrl>

#include "abortwin.h"
#include "default.h"
#include "setwin.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

typedef QMap<QString, QString> versionMap;


class MyThread : public QObject
{
    Q_OBJECT
public:

    explicit MyThread(QObject *parent = nullptr);
    //设置路径和线程
    void initThread(QString tStr,bool isPath,QThread *tThread);

    void closeThread();

    //查询版本信息
    versionMap checkVersionThread(QString tStr, bool isPath);
    QString checkVersionThread(QString tFile);
    QString checkVersionCMD(QString tFile, QString tStr);

    //
    QString m_filePath;
    bool isfile; //是否为文件
    versionMap m_verMap;
    QThread* m_thread;

  signals:

    void checkFinishiSignal();
    void writeLogSignal(QString log ,int color);
  public slots:
    void startThreadSlot();

private:

    QString m_version;
    volatile bool isStop;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void on_cmdButton_clicked();
    void on_action_Menu_triggered();

    //

    void closeThreadSlot();
    void finishedThreadSlot();

    void writLogSlog(QString log ,int color);

  private:
    Ui::MainWindow* ui;
    SetWin* setWindows;


    bool isfile; //是否为文件
    bool isDrag;
    QPoint m_position;
    QString m_fileName;
    QString m_filePath;

    QString m_cfg_verMark;

    QStringList m_ExportList;


    QThread *firstThread;
    MyThread *myObjectThread;


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
    void readVersionFile(QString filePath);
};
















#endif // MAINWINDOW_H
