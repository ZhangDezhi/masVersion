#ifndef ABORTWIN_H
#define ABORTWIN_H

#include <QDialog>

namespace Ui {
class AbortWin;
}

class AbortWin : public QDialog
{
    Q_OBJECT

  public:
    explicit AbortWin(QWidget *parent = nullptr);
    ~AbortWin();

  private:
    Ui::AbortWin *ui;
};

#endif // ABORTWIN_H
