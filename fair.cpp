// fair.cpp
#include "fair.h"
#include <QRandomGenerator>
#include <QThread>

int Fair::readCount = 0;
int Fair::writeCount = 0;
QSemaphore Fair::resource(1);
QSemaphore Fair::readMutex(1);
QSemaphore Fair::queue(1);
QMutex Fair::writeMutex;

void Fair::runReader(int id, const LogCallback& log, const OnDebugCallback& debug)
{
	QString prefix = QString("读者 R%1 ").arg(id);

	DebugInfo info;
	info.threadType = "Reader";
	info.id = id;
	info.action = "请求读权限";
	debug(info);

	queue.acquire();
	info.action = "进入公平队列";
	debug(info);

	readMutex.acquire();
	readCount++;
	info.readCount = readCount;
	if (readCount == 1) {
		resource.acquire();
		info.resourceHeld = true;
		info.action = "首个读者锁定资源";
	}
	else {
		info.action = "增加读者计数";
	}
	debug(info);
	readMutex.release();

	queue.release();
	info.action = "释放队列";
	debug(info);

	log(prefix + "开始读...");
	info.action = "执行读操作";
	debug(info);

	QThread::sleep(QRandomGenerator::global()->bounded(1, 3));
	log(prefix + "结束读");

	info.action = "读操作完成";
	debug(info);

	readMutex.acquire();
	readCount--;
	info.readCount = readCount;
	if (readCount == 0) {
		resource.release();
		info.resourceHeld = false;
		info.action = "最后一个读者释放资源";
	}
	else {
		info.action = "减少读者计数";
	}
	debug(info);
	readMutex.release();
}

void Fair::runWriter(int id, const LogCallback& log, const OnDebugCallback& debug)
{
	QString prefix = QString("写者 W%1 ").arg(id);

	DebugInfo info;
	info.threadType = "Writer";
	info.id = id;
	info.action = "请求写权限";
	debug(info);

	queue.acquire();
	info.action = "进入公平队列";
	debug(info);

	writeMutex.lock();
	writeCount++;
	info.writeCount = writeCount;
	info.action = "增加写者计数";
	debug(info);
	writeMutex.unlock();

	resource.acquire();
	info.resourceHeld = true;
	info.action = "获取资源独占权";
	debug(info);

	queue.release();
	info.action = "释放队列";
	debug(info);

	log(prefix + "开始写...");
	info.action = "执行写操作";
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
	info.action = "减少写者计数";
	debug(info);
	writeMutex.unlock();
}