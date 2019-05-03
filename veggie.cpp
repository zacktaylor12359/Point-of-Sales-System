#include "veggie.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

veggie::veggie(string n, string c, float p, int s, date best)
	:item(n, c, p, s) {
	bestBy = best;
}
void veggie::setVeggie(string n, string c, float p, int s, date best) {
	item::setItem(n, c, p, s);
	bestBy = best;
}
void veggie::setBest(date best) {
	bestBy = best;
}
date veggie::getBest() {
	return bestBy;
}

time_t veggie::getDaysFromNow() {
 	return bestBy.daysFromNow();
}

void veggie::outFile(ofstream &fout) {
	item::outFile(fout);
	fout << bestBy.getMonth() << " " << bestBy.getDay() << " " << bestBy.getYear();
}

ostream& operator<<(ostream& out, const veggie &thing) {
	cout << "Name: " << thing.name << endl;
	cout << "Category: " << thing.category << endl;
	cout << "Price: $" << fixed << showpoint << setprecision(2) << thing.price << endl;
	cout << "Quantity: " << thing.stock << endl;
	cout << "Best by: " << thing.bestBy << endl;
	return out;
}

const veggie& veggie::operator=(const veggie& rightObject) {
	if (this != &rightObject)
	{
		item::operator=(rightObject);
		bestBy = rightObject.bestBy;
	}
	return *this;
}