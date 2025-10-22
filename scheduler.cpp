// scheduler.cpp
#include "scheduler.h"
#include <QTimer>
#include <QThread>

Scheduler::Scheduler(QObject* parent) : QObject(parent) {}

Scheduler::~Scheduler()
{
	stop();
}

void Scheduler::start(int numReaders, int numWriters)
{
	stop();
	threads.clear();
	activeThreadCount = 0;

	// 创建读者线程
	for (int i = 1; i <= numReaders; ++i)
	{
		auto* readerWriter = new ReaderWriter(i, false, currentMode);
		readerWriter->setDebugMode(debugMode);
		connect(readerWriter, &ReaderWriter::logMessage, this, &Scheduler::logMessage);
		connect(readerWriter, &ReaderWriter::debugMessage, this, &Scheduler::debugMessage);
		connect(readerWriter, &QThread::finished, this, &Scheduler::onThreadFinished);

		threads.append(readerWriter);
		activeThreadCount++;
		readerWriter->start();
		QThread::msleep(100);  // 延迟创建，模拟动态过程
	}

	// 创建写者线程
	for (int i = 1; i <= numWriters; ++i)
	{
		auto* readerWriter = new ReaderWriter(i, true, currentMode);
		readerWriter->setDebugMode(debugMode);
		connect(readerWriter, &ReaderWriter::logMessage, this, &Scheduler::logMessage);
		connect(readerWriter, &ReaderWriter::debugMessage, this, &Scheduler::debugMessage);
		connect(readerWriter, &QThread::finished, this, &Scheduler::onThreadFinished);

		threads.append(readerWriter);
		activeThreadCount++;
		readerWriter->start();
		QThread::msleep(200);  // 延迟创建，模拟动态过程
	}

	isRunning = true;
}

void Scheduler::onThreadFinished()
{
	activeThreadCount--;

	if (activeThreadCount <= 0 && isRunning) {
		isRunning = false;
		QTimer::singleShot(0, this, [this]() {
			for (auto* thread : threads) {
				if (thread) {
					thread->deleteLater();
				}
			}
			threads.clear();
			emit simulationFinished();
			});
	}
}

void Scheduler::stop()
{
	if (!isRunning) {
		return;
	}

	isRunning = false;

	// 停止所有线程
	for (auto* thread : threads)
	{
		if (thread && thread->isRunning()) {
			thread->requestInterruption();
			thread->quit();
			if (!thread->wait(1000)) {
				thread->terminate();
				thread->wait();
			}
		}
	}

	QTimer::singleShot(0, this, [this]() {
		for (auto* thread : threads) {
			if (thread) {
				thread->deleteLater();
			}
		}
		threads.clear();
		emit simulationFinished();
		});
}

void Scheduler::setMode(ReadWriteMode mode)
{
	if (isRunning) {
		return;
	}
	currentMode = mode;
}

void Scheduler::setDebugMode(bool enabled)
{
	debugMode = enabled;

	// 如果模拟正在运行，更新所有现有线程的调试模式
	if (isRunning) 
	{
		for (auto* thread : threads) 
		{
			if (thread) 
			{
				thread->setDebugMode(enabled);
			}
		}
	}
}

void Scheduler::reset()
{
	stop();
}