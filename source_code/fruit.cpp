#include "fruit.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

fruit::fruit(string n, string c, float p, int s, date best)
	:item(n, c, p, s) {
	bestBy = best;
}

void fruit::setFruit(string n, string c, float p, int s, date best) {
	item::setItem(n, c, p, s);
	bestBy = best;
}

void fruit::setBest(date best) {
	bestBy = best;
}

date fruit::getBest() {
	return bestBy;
}

time_t fruit::getDaysFromNow() {
	return bestBy.daysFromNow();
}

void fruit::outFile(ofstream &fout) {
	item::outFile(fout);
	fout << bestBy.getMonth() << " " << bestBy.getDay() << " " << bestBy.getYear();
}

ostream& operator<<(ostream& out, const fruit &thing) {
	cout << "Name: " << thing.name << endl;
	cout << "Category: " << thing.category << endl;
	cout << "Price: $" << fixed << showpoint << setprecision(2) << thing.price << endl;
	cout << "Quantity: " << thing.stock << endl;
	cout << "Best by: " << thing.bestBy << endl;
	return out;
}

const fruit& fruit::operator=(const fruit& rightObject) {
	if (this != &rightObject)
	{
		item::operator=(rightObject);
		bestBy = rightObject.bestBy;
	}
	return *this;
}
