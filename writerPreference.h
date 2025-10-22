// writerPreference.h
#pragma once
#include <QString>
#include <functional>
#include <QSemaphore>
#include <QMutex>
#include "debuginfo.h"

class WriterPreference
{
public:
	static void runReader(int id, const LogCallback& log, const OnDebugCallback& debug);
	static void runWriter(int id, const LogCallback& log, const OnDebugCallback& debug);

private:
	static int readCount;        // 活跃读者数量
	static int writeCount;       // 等待写者数量

	static QSemaphore readLock;  // 读锁，用于实现写者优先
	static QSemaphore resource;  // 资源信号量
	static QMutex readMutex;     // 保护readCount
	static QMutex writeMutex;    // 保护writeCount
};