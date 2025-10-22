// scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include "readerwriter.h"
#include "common.h"

class Scheduler : public QObject
{
	Q_OBJECT

public:
	explicit Scheduler(QObject* parent = nullptr);
	~Scheduler();

	void start(int numReaders, int numWriters);
	void stop();
	void reset();
	void setMode(ReadWriteMode mode);
	void setDebugMode(bool enabled);

signals:
	void logMessage(const QString& msg);
	void debugMessage(const QString& debugStr);
	void simulationFinished();

private slots:
	void onThreadFinished();

private:
	QList<ReaderWriter*> threads;
	ReadWriteMode currentMode = ReadWriteMode::WriterPreference;
	bool isRunning = false;
	bool debugMode = false;
	int activeThreadCount = 0;
};

#endif // SCHEDULER_H