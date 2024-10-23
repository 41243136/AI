#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtWidgets>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    QTextEdit*   displayTextEdit;
    QPushButton* colorPushBtn;
    QPushButton* errorPushBtn;
    QPushButton* filePushBtn;
    QPushButton* fontPushBtn;
    QPushButton* inputPushBtn;
    QPushButton* pagePushBtn;
    QPushButton* progressPushBtn;
    QPushButton* printPushBtn;
    QPushButton* clearTextPushBtn;
    QPushButton* randomNumPushBtn;
    QPushButton* reverseTextPushBtn;
private slots:
    void doPushBtn();
};
#endif // DIALOG_H
