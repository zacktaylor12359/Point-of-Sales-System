#include "meat.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std; 

meat::meat(string n, string c, float p, int s, date best)
	:item(n, c, p, s) {
	bestBy = best;
}
void meat::setMeat(string n, string c, float p, int s, date best)	{
	item::setItem(n, c, p, s);
	bestBy = best;
}
void meat::setBest(date best) {
	bestBy = best;
}
date meat::getBest() {
	return bestBy;
}

time_t meat::getDaysFromNow() {
	return bestBy.daysFromNow();
}

void meat::outFile(ofstream &fout) {
	item::outFile(fout);
	fout << bestBy.getMonth() << " " << bestBy.getDay() << " " << bestBy.getYear();
}

ostream& operator<<(ostream& out, const meat &thing) {
	cout << "Name: " << thing.name << endl;
	cout << "Category: " << thing.category << endl;
	cout << "Price: $" << fixed << showpoint << setprecision(2) << thing.price << endl;
	cout << "Quantity: " << thing.stock << endl;
	cout << "Best by: " << thing.bestBy << endl;
	return out;
}

const meat& meat::operator=(const meat& rightObject) {
	if (this != &rightObject)
	{
		item::operator=(rightObject);
		bestBy = rightObject.bestBy;
	}
	return *this;
}