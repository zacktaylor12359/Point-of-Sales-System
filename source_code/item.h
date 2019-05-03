#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class item {
public:
	item() {}
	item(string n, string c, float p, int s);
	void setItem(string n, string c, float p, int s);
	void setName(string n);
	void setCategory(string c);
	void setPrice(float p);
	void setStock(int s);
	string getName();
	string getCategory();
	float getPrice();
	int getStock();
	void outFile(ofstream& fout);
	const item& operator=(const item&);

protected:
	string name = "";
	string category = "";
	float price = 0.0;
	int stock = 0;
};


#endif
