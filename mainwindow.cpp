// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QDebug>
#include <QShortcut>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, scheduler(new Scheduler(this))
{
	ui->setupUi(this);
	setupConnections();
	setupShortcuts();

	ui->stopButton->setEnabled(false);
	ui->debugLogTextEdit->setVisible(false);
	ui->debugloglabel->setVisible(false);

	// 设置默认模式为写者优先
	ui->modeComboBox->setCurrentIndex(0); // 写者优先

	// 初始设置调试模式
	scheduler->setDebugMode(ui->debugCheckBox->isChecked());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_startButton_clicked()
{
	ui->startButton->setEnabled(false);
	ui->stopButton->setEnabled(true);
	ui->resetButton->setEnabled(false);

	int readers = ui->readerSpinBox->value();
	int writers = ui->writerSpinBox->value();

	ui->logTextEdit->clear();
	ui->debugLogTextEdit->clear();

	QString currentModeName = ui->modeComboBox->currentText();

	ui->logTextEdit->append(QString("<b>启动模拟：%1个读者，%2个写者</b>").arg(readers).arg(writers));
	ui->logTextEdit->append(QString("<b>使用模式：%1</b>").arg(currentModeName));
	ui->logTextEdit->append("========================================================");

	scheduler->start(readers, writers);
}

void MainWindow::onLogMessage(const QString& msg)
{
	QTextCharFormat format;

	if (msg.contains("读者") || msg.contains("Reader")) 
	{
		format.setForeground(Qt::yellow);
	}
	else if (msg.contains("写者") || msg.contains("Writer")) 
	{
		format.setForeground(Qt::red);
	}
	else 
	{
		format.setForeground(Qt::black);
	}

	auto cursor = ui->logTextEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	cursor.insertText(msg + "\n", format);
	ui->logTextEdit->verticalScrollBar()->setValue(ui->logTextEdit->verticalScrollBar()->maximum());
}

void MainWindow::setupConnections()
{
	connect(scheduler, &Scheduler::logMessage, this, &MainWindow::onLogMessage);
	connect(scheduler, &Scheduler::debugMessage, this, &MainWindow::onDebugMessage);
	connect(scheduler, &Scheduler::simulationFinished, this, &MainWindow::on_simulationFinished);
}

void MainWindow::setupShortcuts()
{
	QShortcut* startShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
	connect(startShortcut, &QShortcut::activated, this, &MainWindow::on_startButton_clicked);

	QShortcut* stopShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_P), this);
	connect(stopShortcut, &QShortcut::activated, this, &MainWindow::on_stopButton_clicked);

	QShortcut* resetShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_R), this);
	connect(resetShortcut, &QShortcut::activated, this, &MainWindow::on_resetButton_clicked);
}

void MainWindow::on_stopButton_clicked()
{
	scheduler->stop();
	ui->logTextEdit->append("<font color='gray'><b>用户已停止模拟，所有线程正在安全退出...</b></font>");
	ui->startButton->setEnabled(true);
	ui->stopButton->setEnabled(false);
	ui->resetButton->setEnabled(true);
}

void MainWindow::on_resetButton_clicked()
{
	scheduler->stop();
	ui->logTextEdit->clear();
	ui->debugLogTextEdit->clear();
	ui->readerSpinBox->setValue(1);
	ui->writerSpinBox->setValue(1);
	ui->modeComboBox->setCurrentIndex(0); // 重置为写者优先
	ui->startButton->setEnabled(true);
	ui->stopButton->setEnabled(false);
	ui->resetButton->setEnabled(true);
	ui->logTextEdit->append("<font color='blue'><b>已重置模拟参数</b></font>");
}

void MainWindow::on_simulationFinished()
{
	ui->logTextEdit->append("<font color='green'><b>模拟已完成！所有线程已安全结束。</b></font>");
	ui->startButton->setEnabled(true);
	ui->stopButton->setEnabled(false);
	ui->resetButton->setEnabled(true);
}

void MainWindow::on_modeComboBox_currentIndexChanged(int index)
{
	if (!scheduler) return;

	ReadWriteMode mode;
	QString modeName;
	QString modeDescription;

	switch (index) {
	case 0: // 写者优先
		mode = ReadWriteMode::WriterPreference;
		modeName = "写者优先";
		modeDescription = "写者可以优先访问资源，当有写者等待时，新读者会被阻塞";
		break;
	case 1: // 读者优先
		mode = ReadWriteMode::ReaderPreference;
		modeName = "读者优先";
		modeDescription = "读者可以优先访问资源，写者必须等待所有读者完成";
		break;
	case 2: // 读写公平
		mode = ReadWriteMode::Fair;
		modeName = "读写公平";
		modeDescription = "读者和写者公平竞争资源，按照请求顺序交替访问";
		break;
	default:
		mode = ReadWriteMode::WriterPreference;
		modeName = "写者优先";
		modeDescription = "写者可以优先访问资源，当有写者等待时，新读者会被阻塞";
		break;
	}

	scheduler->setMode(mode);
	ui->logTextEdit->append(QString("<font color='green'><b>已切换到：%1 - %2</b></font>").arg(modeName).arg(modeDescription));
}

void MainWindow::onDebugMessage(const QString& msg)
{
	if (ui->debugCheckBox->isChecked()) {
		ui->debugLogTextEdit->append(msg);
		ui->debugLogTextEdit->verticalScrollBar()->setValue(ui->debugLogTextEdit->verticalScrollBar()->maximum());
	}
}

void MainWindow::on_debugCheckBox_stateChanged(int state)
{
	bool visible = (state == Qt::Checked);
	ui->debugLogTextEdit->setVisible(visible);
	ui->debugloglabel->setVisible(visible);
	scheduler->setDebugMode(visible);
}