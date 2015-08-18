#ifndef __TIME_H__
#define __TIME_H__

#ifdef _WIN32

#include <windows.h>
#define raccoon_time FILETIME
#define gettime(a) GetSystemTimePreciseAsFileTime(a)

#else

#include <sys/time.h>
#define raccoon_time struct timeval
#define gettime(a) gettimeofday(a, 0)

#endif

double msecdiff(raccoon_time *before);

#endif /* __TIME_H__ */