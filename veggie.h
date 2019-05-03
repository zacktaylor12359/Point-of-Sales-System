#ifndef VEGGIE_H
#define VEGGIE_H

#include "item.h"
#include "date.h"
#include <iostream>
#include <iomanip>
#include <string>

class veggie :public item {
public:
	veggie() {}
	veggie(string n, string c, float p, int s, date best);
	void setVeggie(string n, string c, float p, int s, date best);
	void setBest(date best);
	date getBest();
	time_t getDaysFromNow();
	void outFile(ofstream &fout);
	friend ostream& operator<<(ostream& out, const veggie& thing);
	const veggie& operator=(const veggie& rightObject);
private:
	date bestBy;
};


#endif

