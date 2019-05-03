#include"item.h"
#include <iostream>
#include <iomanip>
#include <fstream> 

using namespace std;

item::item(string n, string c, float p, int s) {
	name = n;
	category = c;
	price = p;
	stock = s;
}
void item::setItem(string n, string c, float p, int s) {
	name = n;
	category = c;
	price = p;
	stock = s;
}
void item::setStock(int s) {
	stock = s;
}
void item::setPrice(float p) {
	price = p;
}
void item::setName(string n) {
	name = n;
}
void item::setCategory(string c) {
	category = c;
}
int item::getStock() {
	return stock;
}
float item::getPrice() {
	return price;
}
string item::getName() {
	return name;
}
string item::getCategory() {
	return category;
}

void item::outFile(ofstream& fout) {
	fout << fixed << left;
	fout << setw(15) << name << setw(15) << category << setw(15);
	fout << fixed << showpoint << setprecision(2) << price << setw(15) << stock;

}

const item& item::operator=(const item& rightObject) {
	if (this != &rightObject)
	{
		price = rightObject.price;
		name = rightObject.name;
		stock = rightObject.stock;
		category = rightObject.category;
	}

	return *this;
}