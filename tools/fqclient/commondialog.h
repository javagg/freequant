#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H

#include <QDialog>

class CommonDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CommonDialog(QWidget *parent = 0);
    ~CommonDialog() {}
};

#endif // COMMONDIALOG_H
