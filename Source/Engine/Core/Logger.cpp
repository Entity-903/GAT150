#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace kiko
{

	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case kiko::LogLevel::Info:
			*this << "INFO: ";
			break;
		case kiko::LogLevel::Warning:
			*this << "WARNING: ";
			break;
		case kiko::LogLevel::Error:
			*this << "ERROR: ";
			break;
		case kiko::LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}
}