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
    explicit SetWin(QWidget* parent = nullptr);
    ~SetWin();

  private:
    Ui::SetWin* ui;
};

#endif // SETWIN_H
