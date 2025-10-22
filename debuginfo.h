// debuginfo.h
#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include <QString>
#include <functional>

struct DebugInfo
{
	QString threadType;   // 线程类型："Reader" 或 "Writer"
	int id = 0;           // 线程ID
	QString action;       // 当前执行的动作

	int readCount = 0;        // 当前活跃的读者数量
	int writeCount = 0;       // 当前等待的写者数量
	bool resourceHeld = false; // 资源是否被占用
	bool readLockHeld = false; // 读锁是否被占用

	QString toString() const {
		return QString("[%1-%2] %3 | 活跃读者:%4 等待写者:%5 | 资源:%6 读锁:%7")
			.arg(threadType)
			.arg(id)
			.arg(action)
			.arg(readCount)
			.arg(writeCount)
			.arg(resourceHeld ? "占用" : "空闲")
			.arg(readLockHeld ? "锁定" : "释放");
	}
};

// 回调函数类型定义
using LogCallback = std::function<void(const QString&)>;
using OnDebugCallback = std::function<void(const DebugInfo&)>;

#endif // DEBUGINFO_H