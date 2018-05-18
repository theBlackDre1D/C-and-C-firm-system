#include "Date.h"
#include <iostream>
#include <sstream>

using namespace std;
Date::Date() {
	day_ = month_ = year_ = 0;
}

Date::~Date() {
	
}

Date::Date(int day, int month, int year) {
	day_ = day;
	month_ = month;
	year_ = year;
}

Date::Date(const Date &other) {
	day_ = other.day_;
	month_ = other.month_;
	year_ = other.year_;
}

void Date::oneDayForward() {
	if (increaseDay()) {
		if (increaseMonth()) {
			increaseYear();
		}
	}
}

void Date::oneDayBack()
{
	if (day_ == 1)
	{
		day_ == 30;
		if (month_ == 1)
		{
			month_ == 12;
			year_ = year_ - 1;
		}
		else
		{
			month_ = month_ - 1;
		}
	}
	else
	{
		day_ = day_ - 1;
	}
}

void Date::nDaysForward(int dayCount)
{
	if (day_ + dayCount <= 30)
	{
		day_ += dayCount;
	}
	else
	{
		day_ += dayCount;
		day_ - 30;
		if (increaseMonth())
		{
			increaseYear();
		}
	}
}

bool Date::increaseDay() {
	if (day_ == 30) {
		day_ = 1;
		return true;
	}
	else {
		day_++;
		return false;
	}
}

bool Date::increaseMonth() {
	if (month_ == 12) {
		month_ = 1;
		return true;
	}
	else {
		month_++;
		return false;
	}
}

void Date::increaseYear() {
	year_++;
}

int Date::differenceBetweenDates(Date &date) {
	int dayGap = 0;
	if (isEqual(date)) {
		return dayGap;
	}
	if (month_ != date.month_) {
		dayGap += 30 - day_;
		dayGap += (date.day_);
		dayGap += 30 * abs(month_ - date.month_ - 1); // -1 must be
	}
	else {
		dayGap += abs(day_ - date.day_);
	}
	if (year_ != date.year_) {
		dayGap += 30 * (12 - month_);
		dayGap += 30 * date.month_;
	}
	else {
		dayGap += 30 * abs(month_ - date.month_);
	}
	return dayGap;
}

bool Date::isBigger(Date & date) // vrati true ak date (parameter) je vacsi ako this
{
	if (year_ < date.year_) {
		return true;
	}
	else if (month_ < date.month_) {
		return true;
	}
	else if (day_ < date.year_) {
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Date::isEqual(Date & date)
{
	if (day_ == date.day_ &&
		month_ == date.month_ &&
		year_ == date.year_) {
		return true;
	}
	else
		return false;
}

string Date::toString()
{
	stringstream stream;
	stream << day_ << ". " << month_ << ". " << year_;
	return stream.str();
}


