// readerwriter.cpp
#include "readerwriter.h"
#include <QRandomGenerator>
#include <QThread>

ReaderWriter::ReaderWriter(int id, bool isWriter, ReadWriteMode mode, QObject* parent)
	: QThread(parent), id(id), isWriter(isWriter), debugMode(false), mode(mode) {
}

void ReaderWriter::run()
{
	auto logCallback = [this](const QString& msg) {
		emit logMessage(msg);
		};

	auto debugCallback = [this](const DebugInfo& info) {
		if (debugMode) {
			emit debugMessage(info.toString());
		}
		};

	// 根据模式选择算法
	switch (mode) {
	case ReadWriteMode::ReaderPreference:
		if (isWriter) {
			ReaderPreference::runWriter(id, logCallback, debugCallback);
		}
		else {
			ReaderPreference::runReader(id, logCallback, debugCallback);
		}
		break;
	case ReadWriteMode::WriterPreference:
		if (isWriter) {
			WriterPreference::runWriter(id, logCallback, debugCallback);
		}
		else {
			WriterPreference::runReader(id, logCallback, debugCallback);
		}
		break;
	case ReadWriteMode::Fair:
		if (isWriter) {
			Fair::runWriter(id, logCallback, debugCallback);
		}
		else {
			Fair::runReader(id, logCallback, debugCallback);
		}
		break;
	}
}

void ReaderWriter::setDebugMode(bool enabled)
{
	debugMode = enabled;
}