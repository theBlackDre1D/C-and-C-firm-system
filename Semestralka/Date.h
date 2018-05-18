#pragma once
#include <string>

using namespace std;
class Date {
public:
	Date();
	Date(int day, int mounth, int year);
	Date(const Date &other);
	~Date();

	int day_;
	int month_;
	int year_;

	void oneDayForward();
	void oneDayBack();
	void nDaysForward(int dayCount);
	int differenceBetweenDates(Date &date);
	bool isBigger(Date &date);
	bool isEqual(Date &date);
	string toString();

private:
	bool increaseDay();
	bool increaseMonth();
	void increaseYear();
};
