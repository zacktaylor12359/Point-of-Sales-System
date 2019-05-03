#include "date.h"
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

ofstream fout;
ifstream fin;

date::date(time_t m, time_t d, time_t y) {
	month = m;
	day = d;
	year = y;
}

void date::setDate(time_t m, time_t d, time_t y) {
	month = m;
	day = d;
	year = y;
}

void date::setMonth(time_t m) {
	month = m;
}

void date::setDay(time_t d) {
	day = d;
}

void date::setYear(time_t y) {
	year = y;
}

time_t date::getMonth() {
	return month;
}

time_t date::getDay() {
	return day;
}

time_t date::getYear() {
	return year;
}

time_t date::numLeapYears() {
	if (month <= 2)
		year--;

	return year / 4 - year / 100 + year / 400;
}

time_t date::convertDate() {
	time_t num = year * 365 + day;

	for (int i = 0; i < month - 1; i++)
		num += monthDays[i];

	num += numLeapYears();

	return num;
}

time_t date::daysFromNow() {
	date compare(1, 1, 1970);
	time_t forCompare = convertDate() - compare.convertDate();

	time_t now = time(0) - 14400;
	time_t nowDays = now / 86400;

	return forCompare - nowDays;
}

void date::printDate() {
	cout << month << "/" << day << "/" << year;
}

ostream& operator<<(ostream& output, const date &thing) {
	output << thing.month << "/" << thing.day << "/" << thing.year;
	return output;
}


istream& operator>>(istream& input, date &thing) {
	input >> thing.month >> thing.day >> thing.year;
	return input;
}

const date& date::operator=(const date& rightObject) {
	if (this != &rightObject)
	{
		month = rightObject.month;
		day = rightObject.day;
		year = rightObject.year;
	}

	return *this;
}

