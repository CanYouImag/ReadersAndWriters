// readerPreference.h
#pragma once
#include <QString>
#include <functional>
#include <QSemaphore>
#include <QMutex>
#include "debuginfo.h"

class ReaderPreference
{
public:
	static void runReader(int id, const LogCallback& log, const OnDebugCallback& debug);
	static void runWriter(int id, const LogCallback& log, const OnDebugCallback& debug);

private:
	static int readCount;        // ��ǰ��Ծ�Ķ�������
	static int writeCount;       // ��ǰ��Ծ��д����������Ҫ���ڵ��ԣ�

	static QSemaphore resource;     // ��Դ������������������Դ
	static QSemaphore readMutex;    // ����readCount���ź���
	static QSemaphore serviceQueue; // ������У���֤�����̰߳�˳������
	static QMutex writeMutex;       // ����writeCount�Ļ�����
};