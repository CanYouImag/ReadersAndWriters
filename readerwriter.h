// readerwriter.h
#pragma once

#include <QThread>
#include <functional>
#include "writerPreference.h"
#include "readerPreference.h"
#include "fair.h"
#include "debuginfo.h"
#include "common.h"

class ReaderWriter : public QThread
{
	Q_OBJECT

public:
	explicit ReaderWriter(int id, bool isWriter, ReadWriteMode mode, QObject* parent = nullptr);
	void run() override;
	void setDebugMode(bool enabled);

signals:
	void logMessage(const QString& msg);
	void debugMessage(const QString& debugStr);

private:
	int id;
	bool isWriter;
	bool debugMode;
	ReadWriteMode mode;
};