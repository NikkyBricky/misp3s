#include "time_meter.h"
#include "time_meter_impl.h"

TimeMeter::TimeMeter(unsigned count) : pImpl(new Impl(count)) {}

TimeMeter::~TimeMeter() = default;

double TimeMeter::setTimeStamp(unsigned num) {
	return pImpl->setTimeStamp(num);
}

double TimeMeter::getSTimeStamp(unsigned num) const {
	return pImpl->getSTimeStamp(num);
}

int64_t TimeMeter::getMSTimeStamp(unsigned num) const {
	return pImpl->getMSTimeStamp(num);
}

double TimeMeter::getSDiff(unsigned first, unsigned second) const {
	return pImpl->getSDiff(first, second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) const {
	return pImpl->getMSDiff(first, second);
}

bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) const {
	return pImpl->isLess(first, second, expected);
}

bool TimeMeter::isLess(unsigned num, int64_t expected) const {
	return pImpl->isLess(num, expected);
}
