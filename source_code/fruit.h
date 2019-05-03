#ifndef FRUIT_H
#define FRUIT_H

#include "item.h"
#include "date.h"
#include <iostream>
#include <iomanip>
#include <string>

class fruit :public item {
public:
	fruit() {}
	fruit(string n, string c, float p, int s, date best);
	void setFruit(string n, string c, float p, int s, date best);
	void setBest(date best);
	date getBest();
	time_t getDaysFromNow();
	void outFile(ofstream &fout);
	friend ostream& operator<<(ostream& out, const fruit &thing);
	const fruit& operator=(const fruit& rightObject);
private:
	date bestBy;
};


#endif

