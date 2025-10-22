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
	static int readCount;        // ��Ծ��������
	static int writeCount;       // �ȴ�д������

	static QSemaphore readLock;  // ����������ʵ��д������
	static QSemaphore resource;  // ��Դ�ź���
	static QMutex readMutex;     // ����readCount
	static QMutex writeMutex;    // ����writeCount
};