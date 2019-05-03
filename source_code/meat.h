#ifndef MEAT_H
#define MEAT_H

#include "item.h"
#include "date.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

class meat :public item {
public:
	meat() {}
	meat(string n, string c, float p, int s, date best);
	void setMeat(string n, string c, float p, int s, date best);
	void setBest(date best);
	date getBest();
	time_t getDaysFromNow();
	void outFile(ofstream& fout);
	friend ostream& operator<<(ostream& out, const meat &thing);	
	const meat& operator=(const meat& rightObject);
private:
	date bestBy;
};


#endif
