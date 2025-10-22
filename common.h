// common.h
#pragma once

enum class ReadWriteMode
{
	ReaderPreference,	// 读者优先
	WriterPreference,	// 写者优先
	Fair				// 读写公平
};