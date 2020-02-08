#include "Time.h"
#include <chrono>

string Time::NowToString() const
{
	chrono::system_clock::time_point p = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(p);
	char str[26];
	ctime_s(str, sizeof str, &t);
	return str;
	/*std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	long long ll = std::stoll(std::to_string(millis), 0, 0);
	return std::to_string(millis);*/
}

long long Time::NowToMili() const
{
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	return std::stoll(std::to_string(millis), 0, 0);
}