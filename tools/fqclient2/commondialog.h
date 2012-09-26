#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QLineEdit>

namespace Ui {
class CommonDialog;
}

class CommonDialog : public QDialog {
    Q_OBJECT
    
public:
    enum Type {
        EmptyDialog,
        ConnectionDialog,
        OrderDialog,
        OrderAttributesDialog
    };

    explicit CommonDialog(QWidget *parent = 0, Type type = EmptyDialog);
    ~CommonDialog() {}
    QMap<QString, QVariant>& params() { return m_params; }
public slots:
    void accept();

private:
    Ui::CommonDialog *ui;
    QMap<QString, QVariant> m_params;
    Type type;
};

#endif // COMMONDIALOG_H
