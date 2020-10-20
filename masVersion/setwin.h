#ifndef SETWIN_H
#define SETWIN_H

#include <QDialog>

namespace Ui
{
class SetWin;
}

class SetWin : public QDialog
{
    Q_OBJECT

  public:
    explicit SetWin(QWidget* parent = 0);
    ~SetWin();



  private:
    Ui::SetWin* ui;

  public:
    QString verMark;



};

#endif // SETWIN_H
