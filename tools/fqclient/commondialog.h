#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H

#include <QDialog>

namespace Ui {
class CommonDialog;
}


class CommonDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CommonDialog(QWidget *parent = 0);
    ~CommonDialog() {}

private:
    Ui::CommonDialog *ui;
};

#endif // COMMONDIALOG_H
