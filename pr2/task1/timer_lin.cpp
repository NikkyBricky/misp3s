#include "time_meter_impl.h"

#include <ctime>

int64_t TimeMeter::Impl::now() {
	timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return int64_t(t.tv_sec) * 1000000000LL + t.tv_nsec;
}
