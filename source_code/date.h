#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const time_t monthDays[12] = { 31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };

class date {
public:
	date() {};
	date(time_t m, time_t d, time_t y);
	void setDate(time_t m, time_t d, time_t y);
	void setMonth(time_t m);
	void setDay(time_t d);
	void setYear(time_t y);
	time_t getMonth();
	time_t getDay();
	time_t getYear();
	time_t numLeapYears();
	time_t convertDate();
	time_t daysFromNow();
	void printDate();
	
	friend ostream& operator<<(ostream& out, const date &thing);
	friend istream& operator>>(istream& out, date &thing);
	//friend ofstream& operator<<(ofstream& out, const date &thing);
	friend istream& operator>>(istream& out, date &thing);
	const date& operator=(const date&);

private:
	time_t day = 0;
	time_t month = 0;
	time_t year = 0;
}; 

#endif