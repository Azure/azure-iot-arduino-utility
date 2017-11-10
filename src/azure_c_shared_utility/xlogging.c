// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/consolelogger.h"

#ifndef NO_LOGGING


#ifdef WINCE
#include <stdarg.h>

void consolelogger_log(LOG_CATEGORY log_category, const char* file, const char* func, int line, unsigned int options, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	time_t t = time(NULL);

	switch (log_category)
	{
	case AZ_LOG_INFO:
		(void)printf("Info: ");
		break;
	case AZ_LOG_ERROR:
		(void)printf("Error: Time:%.24s File:%s Func:%s Line:%d ", ctime(&t), file, func, line);
		break;
	default:
		break;
	}

	(void)vprintf(format, args);
	va_end(args);

	(void)log_category;
	if (options & LOG_LINE)
	{
		(void)printf("\r\n");
	}
}
#endif

LOGGER_LOG global_log_function = consolelogger_log;

void xlogging_set_log_function(LOGGER_LOG log_function)
{
    global_log_function = log_function;
}

LOGGER_LOG xlogging_get_log_function(void)
{
    return global_log_function;
}

#if (defined(_MSC_VER)) && (!(defined WINCE))

LOGGER_LOG_GETLASTERROR global_log_function_GetLastError = consolelogger_log_with_GetLastError;

void xlogging_set_log_function_GetLastError(LOGGER_LOG_GETLASTERROR log_function_GetLastError)
{
    global_log_function_GetLastError = log_function_GetLastError;
}

LOGGER_LOG_GETLASTERROR xlogging_get_log_function_GetLastError(void)
{
    return global_log_function_GetLastError;
}
#endif

#endif
