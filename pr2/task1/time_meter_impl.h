#pragma once
#include "time_meter.h"

#include <cstdint>
#include <vector>

class TimeMeter::Impl {
	public:
		Impl(unsigned count) : _start(now()), _stamps(count, _start) {}

		double setTimeStamp(unsigned num) {
		    _stamps.at(num) = now();
		    return getSTimeStamp(num);
		}

		double getSTimeStamp(unsigned num) const {
		    return (_stamps.at(num) - _start) / 1e9;
		}

		int64_t getMSTimeStamp(unsigned num) const {
		    return (_stamps.at(num) - _start) / 1000000;
		}

		double getSDiff(unsigned first, unsigned second) const {
		    return (_stamps.at(second) - _stamps.at(first)) / 1e9;
		}

		int64_t getMSDiff(unsigned first, unsigned second) const {
		    return (_stamps.at(second) - _stamps.at(first)) / 1000000;
		}

		bool isLess(unsigned first, unsigned second, int64_t expected) const {
		    return getMSDiff(first, second) < expected;
		}

		bool isLess(unsigned num, int64_t expected) const {
		    return getMSTimeStamp(num) < expected;
		}

	private:
		static int64_t now();

		int64_t _start;
		std::vector<int64_t> _stamps;
};
