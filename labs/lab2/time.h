class Time {
public:
	Time();
	Time(int aHour, int aMinute, int aSecond);

	// Accessors
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	//  Modifiers
	void setHour(int aHour);
	void setMinute(int aMinute);
	void setSecond(int aSecond);

	// Other member functions that work on Time objects
	void PrintAMPM();
	
private:
	int hour;
	int minute;
	int second;
};
bool IsEarlierThan(const Time& t1, const Time& t2);
