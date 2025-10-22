// readerPreference.cpp
#include "readerpreference.h"
#include <QRandomGenerator>
#include <QThread>

int ReaderPreference::readCount = 0;
int ReaderPreference::writeCount = 0;
QSemaphore ReaderPreference::resource(1);
QSemaphore ReaderPreference::readMutex(1);
QSemaphore ReaderPreference::serviceQueue(1);
QMutex ReaderPreference::writeMutex;

void ReaderPreference::runReader(int id, const LogCallback& log, const OnDebugCallback& debug)
{
	QString prefix = QString("读者 R%1 ").arg(id);

	DebugInfo info;
	info.threadType = "Reader";
	info.id = id;
	info.action = "请求读权限";
	debug(info);

	log(prefix + "请求读权限...");

	serviceQueue.acquire();
	info.action = "进入服务队列";
	debug(info);

	readMutex.acquire();
	readCount++;
	info.readCount = readCount;
	info.action = "更新读者计数";
	if (readCount == 1) {
		resource.acquire();
		info.resourceHeld = true;
	}
	debug(info);
	readMutex.release();

	serviceQueue.release();
	info.action = "释放服务队列";
	debug(info);

	log(prefix + "开始读...");
	info.action = "正在读";
	debug(info);
	QThread::sleep(QRandomGenerator::global()->bounded(1, 3));
	log(prefix + "结束读");
	info.action = "读操作结束";
	debug(info);

	readMutex.acquire();
	readCount--;
	info.readCount = readCount;
	info.action = "更新读者计数";
	if (readCount == 0) {
		resource.release();
		info.resourceHeld = false;
	}
	debug(info);
	readMutex.release();
}

void ReaderPreference::runWriter(int id, const LogCallback& log, const OnDebugCallback& debug)
{
	QString prefix = QString("写者 W%1 ").arg(id);

	DebugInfo info;
	info.threadType = "Writer";
	info.id = id;
	info.action = "请求写权限";
	debug(info);

	log(prefix + "请求写权限...");

	serviceQueue.acquire();
	info.action = "进入服务队列";
	debug(info);

	writeMutex.lock();
	writeCount++;
	info.writeCount = writeCount;
	info.action = "更新写者计数";
	debug(info);
	writeMutex.unlock();

	resource.acquire();
	info.resourceHeld = true;
	info.action = "获取资源独占权";
	debug(info);

	serviceQueue.release();
	info.action = "释放服务队列";
	debug(info);

	log(prefix + "开始写...");
	info.action = "正在写";
	debug(info);
	QThread::sleep(QRandomGenerator::global()->bounded(2, 4));
	log(prefix + "完成写");
	info.action = "写操作完成";
	debug(info);

	resource.release();
	info.resourceHeld = false;
	info.action = "释放资源";
	debug(info);

	writeMutex.lock();
	writeCount--;
	info.writeCount = writeCount;
	info.action = "更新写者计数";
	debug(info);
	writeMutex.unlock();
}