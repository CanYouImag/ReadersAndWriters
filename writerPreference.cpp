// writerPreference.cpp
#include "writerPreference.h"
#include <QRandomGenerator>
#include <QThread>

// 静态成员初始化
QSemaphore WriterPreference::readLock(1);
QSemaphore WriterPreference::resource(1);
QMutex WriterPreference::readMutex;
QMutex WriterPreference::writeMutex;
int WriterPreference::readCount = 0;
int WriterPreference::writeCount = 0;

void WriterPreference::runReader(int id, const LogCallback& log, const OnDebugCallback& debug)
{
	QString prefix = QString("读者 R%1").arg(id);

	DebugInfo info;
	info.threadType = "Reader";
	info.id = id;

	// 请求读权限
	info.action = "请求读权限";
	debug(info);
	log(prefix + " 请求读权限...");

	// 获取读锁（写者优先的关键）
	readLock.acquire();
	info.action = "通过读锁检查";
	debug(info);

	// 更新读者计数
	readMutex.lock();
	readCount++;
	info.readCount = readCount;
	info.action = "增加读者计数";
	if (readCount == 1) {
		resource.acquire();  // 第一个读者锁定资源
		info.resourceHeld = true;
	}
	debug(info);
	readMutex.unlock();

	readLock.release();  // 释放读锁，允许其他读者进入
	info.action = "释放读锁";
	debug(info);

	// 执行读操作
	log(prefix + " 开始读取数据...");
	info.action = "正在读取";
	debug(info);
	QThread::sleep(QRandomGenerator::global()->bounded(1, 4));  // 模拟读操作
	log(prefix + " 完成读取");
	info.action = "读取完成";
	debug(info);

	// 更新读者计数
	readMutex.lock();
	readCount--;
	info.readCount = readCount;
	info.action = "减少读者计数";
	if (readCount == 0) {
		resource.release();  // 最后一个读者释放资源
		info.resourceHeld = false;
	}
	debug(info);
	readMutex.unlock();
}

void WriterPreference::runWriter(int id, const LogCallback& log, const OnDebugCallback& debug)
{
	QString prefix = QString("写者 W%1").arg(id);

	DebugInfo info;
	info.threadType = "Writer";
	info.id = id;

	// 请求写权限
	info.action = "请求写权限";
	debug(info);
	log(prefix + " 请求写权限...");

	// 更新写者计数
	writeMutex.lock();
	writeCount++;
	info.writeCount = writeCount;
	info.action = "增加写者计数";
	if (writeCount == 1) {
		readLock.acquire();  // 第一个写者锁定读锁，阻止新读者
		info.readLockHeld = true;
	}
	debug(info);
	writeMutex.unlock();

	// 获取资源独占权
	resource.acquire();
	info.resourceHeld = true;
	info.action = "获取资源独占权";
	debug(info);

	// 执行写操作
	log(prefix + " 开始写入数据...");
	info.action = "正在写入";
	debug(info);
	QThread::sleep(QRandomGenerator::global()->bounded(2, 5));  // 模拟写操作
	log(prefix + " 完成写入");
	info.action = "写入完成";
	debug(info);

	// 释放资源
	resource.release();
	info.resourceHeld = false;
	info.action = "释放资源";
	debug(info);

	// 更新写者计数
	writeMutex.lock();
	writeCount--;
	info.writeCount = writeCount;
	info.action = "减少写者计数";
	if (writeCount == 0) {
		readLock.release();  // 最后一个写者释放读锁
		info.readLockHeld = false;
	}
	debug(info);
	writeMutex.unlock();
}