#pragma once

#include <QMainWindow>
#include <QThread>
#include <atomic>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Worker : public QObject
{
    Q_OBJECT

public:
    std::atomic_bool m_cancelFlag;

public slots:
    void onWorkStarted();

signals:
    void progressChanged(int value);
    void finished();

private:
    void startProcess();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();
    void onProgressChanged(int value);
    void onWorkerFinished();

signals:
    void workStarted();

private:
    Ui::MainWindow *ui;

    QThread* workerThread;
    Worker* worker;

    void setProgressLabeltext(const QString& text);
    void setProgressBarValue(int progress);
    void setButtonEnabled(bool enabled);

};
