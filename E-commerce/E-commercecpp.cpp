#include <iostream>
#include <conio.h>
#include<windows.h>
#include<fstream>
using namespace std;


string** start_menu = new string * [3] {
	new string("Admin"),
		new string("Guest"),
		new string("Exit")
};

string** admin_choice = new string * [4] {
	new string("Show All Products"),
		new string("Add Product"),
		new string("Delete Product"),
		new string("Update Product")};

string** guest_choice = new string * [3] {
	new string("Buy (ID)"),
		new string("Show Detail(ID)"),
		new string("Show Orders")
};

string** update_product = new string * [4] {
	new string("Change product name"),
	new string("Change product type"),
		new string("Change product price"),
		new string("Change product count")};





#include "Classes.h"
#include "Functions.h"

int main() {


	int count = 0;

	Product** products = new Product * [count] {};

	Database data(products, count);
	menu(start_menu, 3,data);

	for (size_t i = 0; i < count; i++)
	{
		delete products[i];
	}
	delete products;
	//Date date(11, 7, 2004);
	//Guest vusal("vusal", "jafarli", "vfffff", "cgggggg", date);
	//vusal.show();



	//Product* a = new Product("UN", "Quru qida", 0.7);
	//Product* b = new Product("Et", "Quru qida", 3.7);
	//Product* c = new Product("Yag", "Quru qida", 1.7);
	//Product* d = new Product("Salam", "Halal qida", 1.7);

	//Product** products = new Product * [3] {a, b, c};

	//Database database(products, 3);

	//database.show_all_products();
	//cout << endl;
	//cout << endl;
	//cout << endl;


	//cout<<database.add_product(d);
	//database.delete_product(a);
	//database.delete_product(d);

	//database.show_all_products();



	return 0;
}
//bVC