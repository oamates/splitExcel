#ifndef SPLITONLYWINDOW_H
#define SPLITONLYWINDOW_H

#include "xlsxdocument.h"
#include "configsetting.h"
#include "config.h"
#include "emailsender.h"
#include "common.h"
#include "processwindow.h"
#include "xlsxparser.h"

#include <QMainWindow>

namespace Ui {
class SplitOnlyWindow;
}

class SplitOnlyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SplitOnlyWindow(QWidget *parent = nullptr, QMainWindow *mainWindow = nullptr);
    ~SplitOnlyWindow();

    void doSplitXls(QString dataSheetName, QString savePath);

signals:
    void doSplit();

private slots:
    void on_selectFilePushButton_clicked();

    void changeGroupby(QString selectedSheetName);

    void on_savePathPushButton_clicked();

    void on_submitPushButton_clicked();

     void receiveMessage(const int msgType, const QString &result);

     void on_gobackPushButton_clicked();

private:
    Ui::SplitOnlyWindow *ui;
    QMainWindow *mainWindow;

    QXlsx::Document *xlsx = nullptr;
    QStringList *header = new QStringList();
    ConfigSetting *configSetting = new ConfigSetting(nullptr,this);

    Config *cfg = new Config();
    QThread *xlsxParserThread = nullptr;
    XlsxParser * xlsxParser = nullptr;
    QThread *mailSenderThread = nullptr;
    EmailSender *mailSender = nullptr;
    ProcessWindow *processWindow = nullptr;
    QString savePath;
};

#endif // SPLITONLYWINDOW_H