// fair.h
#pragma once
#include <QString>
#include <functional>
#include <QSemaphore>
#include <QMutex>
#include "debuginfo.h"

class Fair
{
public:
	static void runReader(int id, const LogCallback& log, const OnDebugCallback& debug);
	static void runWriter(int id, const LogCallback& log, const OnDebugCallback& debug);

private:
	static int readCount;        // 当前活跃的读者数量
	static int writeCount;       // 当前活跃的写者数量（主要用于调试）

	static QSemaphore resource;  // 资源访问锁，保护共享资源
	static QSemaphore readMutex; // 保护readCount的信号量
	static QSemaphore queue;     // 公平队列，确保读者写者公平排队
	static QMutex writeMutex;    // 保护writeCount的互斥锁
};