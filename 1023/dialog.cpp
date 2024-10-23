#include "dialog.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPageSetupDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout;

    displayTextEdit = new QTextEdit(QStringLiteral("Qt的標準通用對話盒"));
    colorPushBtn = new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn = new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn = new QPushButton(QStringLiteral("列印對話盒"));
    clearTextPushBtn = new QPushButton(QStringLiteral("清除文字"));
    randomNumPushBtn = new QPushButton(QStringLiteral("隨機三位數"));  // 新增一個按鈕來生成隨機三位數
    reverseTextPushBtn = new QPushButton(QStringLiteral("反轉文字"));

    gridLayout->addWidget(colorPushBtn, 0, 0, 1, 1);
    gridLayout->addWidget(errorPushBtn, 0, 1, 1, 1);
    gridLayout->addWidget(filePushBtn, 0, 2, 1, 1);
    gridLayout->addWidget(fontPushBtn, 1, 0, 1, 1);
    gridLayout->addWidget(inputPushBtn, 1, 1, 1, 1);
    gridLayout->addWidget(pagePushBtn, 1, 2, 1, 1);
    gridLayout->addWidget(progressPushBtn, 2, 0, 1, 1);
    gridLayout->addWidget(printPushBtn, 2, 1, 1, 1);
    gridLayout->addWidget(clearTextPushBtn, 2, 2, 1, 1);
    gridLayout->addWidget(randomNumPushBtn, 3, 0, 1, 1);
    gridLayout->addWidget(reverseTextPushBtn, 3, 1, 1, 1);  // 加入反轉文字按鈕
    gridLayout->addWidget(displayTextEdit, 4, 0, 3, 3);

    setLayout(gridLayout);
    setWindowTitle(QStringLiteral("Built-in dialog box display"));
    resize(400, 300);

    connect(colorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(errorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(filePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(fontPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(inputPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(progressPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(pagePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn())); // 修正了 pagePushBtn 的拼寫
    connect(printPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(clearTextPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(randomNumPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));  // 連接隨機三位數按鈕
    connect(reverseTextPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));  // 連接反轉文字按鈕
}

void Dialog:: doPushBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == colorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor& color = QColorDialog::getColor(
            palette.color(QPalette::Base),
            this,
            QStringLiteral("設定背景顏色")
            );

        if (color.isValid()) {
            palette.setColor(QPalette::Base, color);
            displayTextEdit->setPalette(palette);
        }
    }
    if (btn == errorPushBtn) {
        QErrorMessage box(this);
        box.setWindowTitle(QStringLiteral("Error message box"));

        box.showMessage(QStringLiteral("Error message box instance xx."));
        box.showMessage(QStringLiteral("Error message box instance yy."));
        box.showMessage(QStringLiteral("Error message box instance zz: "));

        box.exec();
    }

    if (btn == filePushBtn) {
        QString fileName = QFileDialog::getOpenFileName(
            this,
            QStringLiteral("Open file"),
            ".",
            QStringLiteral("Any file (*.*);;Text file (*.txt);;XML file (*.xml)")
            );
        displayTextEdit->setText(fileName);
    }
    if (btn == fontPushBtn)
    {
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok, displayTextEdit->font(), this, QStringLiteral("Font Dialog Box"));

        if (ok) {
            displayTextEdit->setFont(font);
        }
    }
    if (btn == inputPushBtn) {
        bool ok;
        QString text = QInputDialog::getText(
            this,
            QStringLiteral("Input dialog box"),
            QStringLiteral("Input text"),
            QLineEdit::Normal,
            QDir::home().dirName(),
            &ok
            );

        if (ok && !text.isEmpty()) {
            displayTextEdit->setText(text);
        }
    }
    if (btn == pagePushBtn) {
        QPrinter printer(QPrinter::HighResolution);
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer, this);
        dlg->setWindowTitle(QStringLiteral("Page Settings Box"));

        if (dlg->exec() == QDialog::Accepted) {
            // 在這裡可以處理頁面設置的邏輯
        }
    }
    if (btn == progressPushBtn) {
        QProgressDialog progress(
            QStringLiteral("Copying files..."),
            QStringLiteral("Cancel"),0,10000,this);
        progress.setWindowTitle(QStringLiteral("Progress Dialog Box"));
        progress.show();

        for (int i = 0; i < 10000; i++) {
            progress.setValue(i);
            qApp->processEvents();

            if (progress.wasCanceled()) {
                break;
            }

            qDebug() << i;
        }

        progress.setValue(10000);
    }

    if (btn == printPushBtn) {
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dialog(&printer, this);

        if (dialog.exec() != QDialog::Accepted) {
            return;
        }
    }
    if (btn == clearTextPushBtn) {
        displayTextEdit->clear();  // 清除顯示區的文字
    }
    if (btn == randomNumPushBtn) {
        int randomNum = QRandomGenerator::global()->bounded(100, 1000);  // 生成一個三位數隨機數 (100 到 999)
        displayTextEdit->setText(QString::number(randomNum));  // 將隨機數顯示在文字編輯區
    }
    if (btn == reverseTextPushBtn) {
        QString text = displayTextEdit->toPlainText();  // 取得目前顯示的文字
        std::reverse(text.begin(), text.end());  // 反轉文字
        displayTextEdit->setText(text);  // 將反轉後的文字顯示在文字編輯區
    }
}




Dialog::~Dialog()
{

}
