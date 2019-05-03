#include "meat.h"
#include "veggie.h"
#include "fruit.h"
#include "date.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

//Function for loading in the catalog
void loadCatalog(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect);

//show menu function definitions
void displayMainMenu();
void displaySearchMenu();
void displayNavSearchMenu();
void displayItemFuncMenu();
void displayCategoryMenu();
void displayUpdateMenu();

//main menu function definitions
void searchInventory(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect);
void showAllInventory(vector<meat> meatVect, vector<veggie> veggieVect, vector<fruit> fruitVect);
void addItems(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect);
void showBestBy(vector<meat> meatVect, vector<veggie> veggieVect, vector<fruit> fruitVect);

//Search function definitions
void directSearch(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect);
void navigateSearch(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect);

//Function to update the catalog after modifying the items
void updateCatalog(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect);

//Modify menu function declaration
template<class Type> void itemFunctions(Type &YTitem);

//Item modification function declarations
template<class Type> void sellItems(Type &YTitem);
template<class Type> void returnItems(Type &YTitem);
template<class Type> void updateItems(Type &YTitem);

//Main function
int main() {
	vector<meat> meatVect;
	vector<veggie> veggieVect;
	vector<fruit> fruitVect;
	loadCatalog(meatVect, veggieVect, fruitVect);
	int mainMenuChoice;
	do {
		displayMainMenu();
		cin >> mainMenuChoice;

		switch (mainMenuChoice)
		{
		case 1: searchInventory(meatVect, veggieVect, fruitVect);
			break;
		case 2: showAllInventory(meatVect, veggieVect, fruitVect);
			break;
		case 3: addItems(meatVect, veggieVect, fruitVect);
			break;
		case 4: showBestBy(meatVect, veggieVect, fruitVect);
			break;
		case 5:
			break;
		default: cout << mainMenuChoice << " is not a valid selection.";
			break;
		}
	} while (mainMenuChoice != 5);
}

//Load catalog definition
void loadCatalog(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect){
	ifstream fin;
	fin.open("inventory.txt");

	string header;
	getline(fin, header);
	string category;
	float price;
	int stock;
	date bestBy, other;
	string name;
	meat meatTemp;
	veggie veggieTemp;
	fruit fruitTemp;
	
	while (!fin.eof())
	{
		fin >> name >> category >> price >> stock >> bestBy;
		if (category == "Meat")
		{
			meatTemp.setMeat(name, category, price, stock, bestBy);
			meatVect.push_back(meatTemp);
		}

		else if (category == "Veggie")
		{
			veggieTemp.setVeggie(name, category, price, stock, bestBy);
			veggieVect.push_back(veggieTemp);
		}

		else if (category == "Fruit")
		{
			fruitTemp.setFruit(name, category, price, stock, bestBy);
			fruitVect.push_back(fruitTemp);
		}
	}
}

//Show menu definitions
void displayMainMenu() {
	cout << "YT's POS system\n";

	cout << endl;
	cout << "Choose an option by typing the number of the corresponding option\n";
	cout << "1. Search for an item\n";
	cout << "2. Show all inventory\n";
	cout << "3. Add new items\n";
	cout << "4. Show items expiring within a given time\n";
	cout << "5. Exit\n\n";
}
void displaySearchMenu() {
	cout << "Searching for item\n";
	cout << "1. Search for the item directly\n";
	cout << "2. Search for the item by category\n";
	cout << "3. Back to main menu\n\n";
}
void displayNavSearchMenu() {
	cout << "Select category ";
	cout << "\n1. Meat";
	cout << "\n2. Veggie";
	cout << "\n3. Fruit";
	cout << "\n4. Return" << endl << endl;
}
void displayItemFuncMenu() {
	cout << "What action would you like to perform?\n";
	cout << "1. Sell item.\n";
	cout << "2. Return item.\n";
	cout << "3. Update item\n";
	cout << "4. Back to main menu\n\n";
}
void displayCategoryMenu() {
	cout << "\n1. Meat";
	cout << "\n2. Vegetables";
	cout << "\n3. Fruit";
	cout << "\n4. Cancel" << endl;
}
void displayUpdateMenu() {
	cout << "\n1. Price";
	cout << "\n2. Stock";
	cout << "\n3. Cancel";
}

//main menu function definitions
void searchInventory(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect) {
	int searchOption;
	bool validChoice = true, modItem = true;
	string category;

	do
	{
		validChoice = true;
		displaySearchMenu();
		cin >> searchOption;
		switch (searchOption)
		{
		case 1: directSearch(meatVect, veggieVect, fruitVect);
			break;
		case 2: navigateSearch(meatVect, veggieVect, fruitVect);
			break;
		case 3:
			return;
		default: {cout << searchOption << " is not a search option."; validChoice = false;
			break;}
		}
	} while (validChoice == false); //This way the user does not get kicked out of the search if they input incorrectly
}
void showAllInventory(vector<meat> meatVect, vector<veggie> veggieVect, vector<fruit> fruitVect) {

	for (unsigned int i = 0; i < meatVect.size(); i++)
	{
		cout << meatVect[i] << endl << endl;
	}

	for (unsigned int i = 0; i < veggieVect.size(); i++)
	{
		cout << veggieVect[i] << endl << endl;
	}

	for (unsigned int i = 0; i < fruitVect.size(); i++)
	{
		cout << fruitVect[i] << endl << endl;
	}
	cout << endl;
}
void addItems(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect) {
	bool valid, correctInfo;
	char input;
	cout << "Adding a new item to the inventory\n\n";
	int categoryChoice;

	string name;
	string category;
	float price;
	int stock;
	time_t month, day, year;
	date bestBy;
	meat meatTemp;
	veggie vegTemp;
	fruit fruitTemp;
	ofstream fout;
	fout.open("inventory.txt", ios_base::app);
	do {
		do {
			do {
				cout << "What category is this item in?: ";
				displayCategoryMenu();
				valid = true;
				cout << endl;
				cin >> categoryChoice;
				switch (categoryChoice)
				{
				case (1): {cout << "Category: " << "Meat\n"; category = "Meat";
					break; }
				case (2): {cout << "Category: " << "Veggie\n"; category = "Veggie";
					break; }
				case (3): {cout << "Category: " << "Fruit\n"; category = "Fruit";
					break; }
				case(4): cout << endl << endl << endl;
					return;
				default: {
					cout << "invalid input\n";
					valid = false;
				}
			}

		} while (valid == false);
		
			correctInfo = true;
			cout << "Name: ";
			cin >> name;
			cout << "Price: ";
			cin >> price;
			cout << "Quantity: ";
			cin >> stock;
			cout << "Best by: ";
			cin >> month >> day >> year;
			bestBy.setDate(month, day, year);

			if (categoryChoice == 1)
			{
				meat meatTemp(name, category, price, stock, bestBy);
				meatVect.push_back(meatTemp);
				cout << endl << meatTemp << "Is this information correct? (Y/N) ";
				cin >> input;
				input = toupper(input);
				cout << endl;

				if (input == 'N')
				{
					meatVect.pop_back();
					correctInfo = false;
				}
			}

			else if (categoryChoice == 2)
			{
				veggie vegTemp(name, category, price, stock, bestBy);
				veggieVect.push_back(vegTemp);
				cout << endl << vegTemp << "Is this information correct? (Y/N) ";
				cin >> input;
				input = toupper(input);
				cout << endl;

				if (input == 'N')
				{
					veggieVect.pop_back();
					correctInfo = false;
				}
			}

			else if (categoryChoice == 3)
			{
				fruit fruitTemp(name, category, price, stock, bestBy);
				fruitVect.push_back(fruitTemp);
				cout << endl << fruitTemp << "Is this information correct? (Y/N) ";
				cin >> input;
				input = toupper(input);
				cout << endl;

				if (input == 'N')
				{
					fruitVect.pop_back();
					correctInfo = false;
				}
			}
		} while (correctInfo == false);
		updateCatalog(meatVect, veggieVect, fruitVect);
		
		cout << name << " was successfully added";
		cout << "\n\nAdd another item? (Y/N) ";
		cin >> input;
		input = toupper(input);
		cout << endl;
	} while (input == 'Y');
	cout << endl << endl;
}
void showBestBy(vector<meat> meatVect, vector<veggie> veggieVect, vector<fruit> fruitVect) {
	cout << "Number of days until expiration? ";
	time_t input;
	cin >> input;
	cout << "\n\n List of all items expiring in the next " << input << " days.\n";

	for (unsigned int i = 0; i < meatVect.size(); i++)
	{
		if (meatVect[i].getDaysFromNow() <= input)
			cout << meatVect[i] << endl;
	}

	for (unsigned int i = 0; i < veggieVect.size(); i++)
	{
		if (meatVect[i].getDaysFromNow() <= input)
			cout << meatVect[i] << endl;
	}

	for (unsigned int i = 0; i < fruitVect.size(); i++)
	{
		if (meatVect[i].getDaysFromNow() <= input)
			cout << meatVect[i] << endl;
	}
	cout << endl << endl;
}

//Search functions definitions
void directSearch(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect) {
	string userItem;
	bool found;
	do {
		found = true;
		cout << "What item are you looking for?\n";
		cout << "To go back to the main menu, type Exit\n\n";
		cin >> userItem;
		userItem[0] = toupper(userItem[0]);
		if (userItem == "Exit")
		{
			cout << endl << endl << endl;
			return;
		}

		for (unsigned int i = 0; i < meatVect.size(); i++) {
			if (userItem == meatVect[i].getName()) {
				cout << "--------------\n";
				cout << meatVect[i];
				cout << "--------------\n\n";
				itemFunctions(meatVect[i]);
				updateCatalog(meatVect, veggieVect, fruitVect);
				return;
			}
		}

		for (unsigned int j = 0; j < veggieVect.size(); j++) {
			if (userItem == veggieVect[j].getName()) {
				cout << "--------------\n";
				cout << veggieVect[j];
				cout << "--------------\n\n";
				itemFunctions(veggieVect[j]);
				updateCatalog(meatVect, veggieVect, fruitVect);
				return;
			}
		}

		for (unsigned int k = 0; k < fruitVect.size(); k++) {
			if (userItem == fruitVect[k].getName()) {
				cout << "--------------\n";
				cout << fruitVect[k];
				cout << "--------------\n\n";
				itemFunctions(fruitVect[k]);
				updateCatalog(meatVect, veggieVect, fruitVect);
				return;
			}
		}
		cout << "Item not found.\n\n";
		found = false;
	} while (found == false);
	return;
}
void navigateSearch(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect) {

	int input1, input2;
	displayNavSearchMenu();
	while (true)
	{
		cin >> input1;
		if (input1 == 1)
		{
			cout << "Choose item\n";
			for (unsigned int i = 0; i < meatVect.size(); i++)
			{
				cout << (i + 1) << ". " << meatVect[i].getName();
				cout << endl;
			}
			cout << endl;
			cin >> input2;
			cout << "--------------\n";
			cout << meatVect[input2 - 1];
			cout << "--------------\n\n";
			itemFunctions(meatVect[input2 - 1]);
			updateCatalog(meatVect, veggieVect, fruitVect);
			return;
		}

		else if (input1 == 2)
		{
			cout << "Choose item\n";
			for (unsigned int i = 0; i < veggieVect.size(); i++)
			{
				cout << i + 1 << ". " << veggieVect[i].getName();
				cout << endl;
			}
			cout << endl;
			cin >> input2;
			cout << "--------------\n";
			cout << veggieVect[input2 - 1];
			cout << "--------------\n\n";
			itemFunctions(veggieVect[input2 - 1]);
			updateCatalog(meatVect, veggieVect, fruitVect);
			return;
		}

		else if (input1 == 3)
		{
			cout << "Choose item\n";
			for (unsigned int i = 0; i < fruitVect.size(); i++)
			{
				cout << i + 1 << ". " << fruitVect[i].getName();
				cout << endl;
			}
			cout << endl;
			cin >> input2;
			cout << "--------------\n";
			cout << fruitVect[input2 - 1];
			cout << "--------------\n\n";
			itemFunctions(fruitVect[input2 - 1]);
			updateCatalog(meatVect, veggieVect, fruitVect);
			return;
		}

		else if (input1 == 4)
		{
			cout << endl << endl << endl;
			return;
		}

		else
			cout << "Invalid input\n\n";
	}
}

//Function to decide how you would like to modify the item you searched for
template<class Type> void itemFunctions(Type &YTitem) {
	char input;
	int functionChoice;

	do {
		displayItemFuncMenu();
		cin >> functionChoice;
		switch (functionChoice)
		{
		case 1: sellItems(YTitem);
			break;
		case 2: returnItems(YTitem);
			break;
		case 3: updateItems(YTitem);
			break;
		case 4:
			cout << endl << endl << endl;
			return;
		default:
			cout << functionChoice << " is not a valid selection.";
		}
		cout << "Would you like to perform another action with this item? (Y/N) ";
		cin >> input;
		input = toupper(input);
		cout << endl;
	} while (input == 'Y');
}

//Item modification functions definitions
template<class Type> void sellItems(Type &YTitem) {
	int input;
	try {
		cout << "Selling " << YTitem.getName() << endl;
		cout << "How many " << YTitem.getName() << "s are being sold? ";
		cin >> input;
		if (YTitem.getStock() - input < 0)
			throw(input);
		YTitem.setStock(YTitem.getStock() - input);
	}

	catch (int input)
	{
		cout << "There are not " << input << " " << YTitem.getName() << "s in stock.\n";
	}
}
template<class Type> void returnItems(Type &YTitem) {
	int input;
	cout << "Returning " << YTitem.getName();
	cout << "\nHow many " << YTitem.getName() << "s are being returned? ";
	cin >> input;
	YTitem.setStock(YTitem.getStock() + input);
}
template<class Type> void updateItems(Type &YTitem) {
	int updateChoice;
	bool valid;
	char cont, input;
	do {
		do {
			cout << YTitem.getName() << "\nWhat is being updated?";
			displayUpdateMenu();
			cout << endl << endl;
			cin >> updateChoice;
			valid = true;
			switch (updateChoice)
			{
			case(1): {cout << "New price: ";
				float price;
				cin >> price;
				YTitem.setPrice(price); }
						break;
			case(2): {cout << "New quantity: ";
				int stock;
				cin >> stock;
				YTitem.setStock(stock); }
						break;
			case(3): cout << "cancel\n";
				return;
			default: cout << updateChoice << " is not a valid input\n\n";
				valid = false;
			}
			
		} while (valid == false);

		cout << "Are there more updates with this item?(Y/N): ";
		cin >> cont;
		cout << endl;
		input = toupper(cont);

	} while (input == 'Y');
}

//Update catalog function definition
void updateCatalog(vector<meat> &meatVect, vector<veggie> &veggieVect, vector<fruit> &fruitVect) {
	ofstream fout;
	fout.open("inventory.txt");

	fout << fixed << left;
	fout << setw(15) << "Name:" << setw(15) << "Category:" << setw(15) << "Price:" << setw(15) << "Stock:";
	fout << setw(15) << "Best by:";
	for (unsigned int i = 0; i < meatVect.size(); i++)
	{
		fout << endl;
		meatVect[i].outFile(fout);
	}

	for (unsigned int i = 0; i < veggieVect.size(); i++)
	{
		fout << endl;
		veggieVect[i].outFile(fout);
	}

	for (unsigned int i = 0; i < fruitVect.size(); i++)
	{
		fout << endl;
		fruitVect[i].outFile(fout);
	}
}