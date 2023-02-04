#include "time.h"
#include <iostream>

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}
Time::Time(int aHour, int aMinute, int aSecond) {
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int aHour) {
	hour = aHour;
}

void Time::setMinute(int aMinute) {
	minute = aMinute;
}

void Time::setSecond(int aSecond) {
	second = aSecond;
}

void Time::PrintAMPM() {
	if (getHour() > 12) {
		std::cout << (getHour() - 12) << ":" << getMinute() << ":" << getSecond() << " PM" << std::endl;
	} else {
		std::cout << getHour() << ":" << getMinute() << ":" << getSecond() << " AM" << std::endl;
	}
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour() < t2.getHour()) {
		return true;
	}
	if (t1.getMinute() < t2.getMinute() && t1.getHour() == t2.getHour()) {
		return true;
	}
	if (t1.getSecond() < t2.getSecond() && t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute()) {
		return true;
	}
	return false;
}
