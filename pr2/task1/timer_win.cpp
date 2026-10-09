#include <windows.h>
 
#include "time_meter_impl.h"
 
int64_t TimeMeter::Impl::now() {
	LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);

	return (t.QuadPart / freq) * 1000000000LL + (t.QuadPart % freq) * 1000000000LL / freq;
}
