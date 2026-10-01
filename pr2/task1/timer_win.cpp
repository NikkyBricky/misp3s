#include <windows.h>

#include "time_meter.h"

#include <cmath>
#include <stdexcept>
#include <vector>

class TimeMeter::Impl {
	public:
	    Impl(unsigned count) {
		LARGE_INTEGER f;
		QueryPerformanceFrequency(&f);
		_freq = f.QuadPart;

		_start = now();
		_stamps.assign(count, _start);
	    }

	    double setStamp(unsigned num) {
		check(num);
		_stamps[num] = now();
		return secBetween(_start, _stamps[num]);
	    }

	    double secFromStart(unsigned num) const {
		check(num);
		return secBetween(_start, _stamps[num]);
	    }

	    double secDiff(unsigned first, unsigned second) const {
		check(first);
		check(second);
		return secBetween(_stamps[first], _stamps[second]);
	    }

	private:
	    static LONGLONG now() {
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		return t.QuadPart;
	    }

	    double secBetween(LONGLONG a, LONGLONG b) const {
		return double(b - a) / double(_freq);
	    }

	    void check(unsigned num) const {
		if (num >= _stamps.size()) {
		    throw std::out_of_range("TimeMeter: bad stamp index");
		}
	    }

	    LONGLONG _freq;
	    LONGLONG _start;
	    std::vector<LONGLONG> _stamps;
};

TimeMeter::TimeMeter(unsigned count) : pImpl(new Impl(count)) {
}

TimeMeter::~TimeMeter() = default;

double TimeMeter::setTimeStamp(unsigned num) {
    return pImpl->setStamp(num);
}

double TimeMeter::getSTimeStamp(unsigned num) const {
    return pImpl->secFromStart(num);
}

int64_t TimeMeter::getMSTimeStamp(unsigned num) const {
    return std::llround(pImpl->secFromStart(num) * 1000);
}

double TimeMeter::getSDiff(unsigned first, unsigned second) const {
    return pImpl->secDiff(first, second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) const {
    return std::llround(pImpl->secDiff(first, second) * 1000);
}

bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) const {
    return getMSDiff(first, second) < expected;
}

bool TimeMeter::isLess(unsigned num, int64_t expected) const {
    return getMSTimeStamp(num) < expected;
}
