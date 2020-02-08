#include <string>

using namespace std;

class Time
{
public:
	Time() {}

	// singleton
	static Time &instance()
	{
		static Time T;

		return T;
	}

	string NowToString() const;
	long long NowToMili() const;
};

