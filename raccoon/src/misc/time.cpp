#include "time.h"

double msecdiff(raccoon_time *before)
{
	raccoon_time now;
	gettime(&now);
	#ifdef _WIN32
		double dnow = (double)(now.dwHighDateTime) * 65535.0f * 6553.5f;
		dnow += (double)(now.dwLowDateTime) * 0.1f;
		double dprev = (double)(before->dwHighDateTime) * 65535.0f * 6553.5f;
		dprev += (double)(before->dwLowDateTime) * 0.1f;
		return (dnow - dprev);
	#else
		return (double)(now.tv_sec - before->tv_sec) * 1000.0f +
			   (double)(now.tv_usec - before->tv_usec) / 1000.0f;
	#endif
}