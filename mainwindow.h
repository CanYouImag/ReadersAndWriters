// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include "scheduler.h"
#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void on_startButton_clicked();
	void onLogMessage(const QString& msg);
	void on_stopButton_clicked();
	void on_resetButton_clicked();
	void on_simulationFinished();
	void on_modeComboBox_currentIndexChanged(int index);
	void onDebugMessage(const QString& debugStr);
	void on_debugCheckBox_stateChanged(int state);

private:
	void setupConnections();
	void setupShortcuts();
	Ui::MainWindow* ui;
	Scheduler* scheduler;
};

#endif // MAINWINDOW_H