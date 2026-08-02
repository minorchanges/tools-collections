#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "engine/engine.h"

#include <QPushButton>

// ---------------- Worker ----------------

void Worker::onWorkStarted()
{
    startProcess();
}

void Worker::startProcess()
{
    emit progressChanged(0);

    engine::process(
        100,
        [this](int progress)
        {
            emit progressChanged(progress);
        },
        &m_cancelFlag
    );

    emit progressChanged(100);

    emit finished();
}

// ---------------- MainWindow ----------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workerThread(new QThread(this))
    , worker(new Worker)
{
    ui->setupUi(this);

    setFixedSize(size());
    setWindowTitle("QTThreadModExample");

    // Move worker into background thread
    worker->moveToThread(workerThread);

    // GUI -> Worker
    connect(this,
            &MainWindow::workStarted,
            worker,
            &Worker::onWorkStarted);

    // Worker -> GUI
    connect(worker,
            &Worker::progressChanged,
            this,
            &MainWindow::onProgressChanged);

    connect(worker,
            &Worker::finished,
            this,
            &MainWindow::onWorkerFinished);

    // Cleanup
    connect(workerThread,
            &QThread::finished,
            worker,
            &QObject::deleteLater);

    // Button
    connect(ui->pushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onButtonClicked);

    // Start thread event loop
    workerThread->start();
}

MainWindow::~MainWindow()
{
    worker->m_cancelFlag = true;
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

// ---------------- Button ----------------

void MainWindow::onButtonClicked()
{
    setButtonEnabled(false);
    setProgressLabeltext("Processing...");

    emit workStarted();
}

// ---------------- GUI updates ----------------

void MainWindow::onProgressChanged(int value)
{
    setProgressBarValue(value);
}

void MainWindow::onWorkerFinished()
{
    setProgressLabeltext("Ready");
    setButtonEnabled(true);
}

// ---------------- Native UI functions ----------------

void MainWindow::setProgressLabeltext(const QString& text)
{
    ui->label->setText(text);
}

void MainWindow::setProgressBarValue(int progress)
{
    ui->progressBar->setValue(progress);
}

void MainWindow::setButtonEnabled(bool enabled)
{
    ui->pushButton->setEnabled(enabled);
}
