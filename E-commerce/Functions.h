#pragma once







void write_txt(string text, string source) {
	ofstream file(source, ios::app);

	if (file.is_open()) {

		file << text << endl;
		file.close();

	}
	else {
		cout << "File did not open!" << endl;
	}
}
void print(int row, string** arr, int size) {
	for (size_t i = 0; i < size; i++)
	{

		cout << "\t\t\t\t\t\t\t\t\t";
		HANDLE  console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (i == row)
			SetConsoleTextAttribute(console, 168);

		cout << *arr[i] << endl;

		SetConsoleTextAttribute(console, 7);
	}
}
bool check_data(string text, string source) {
	FILE* f;
	fopen_s(&f, source.c_str(), "r");

	if (f != nullptr) {


		int row = 0;
		int index = 0;
		char symbol;


		symbol = getc(f);
	start:
		while (symbol != EOF)
		{
			char* checking = new char[255] {};

			while (symbol != '\n') {
				checking[index++] = symbol;
				symbol = getc(f);

			}
			checking[index] = '\r';

			const char* a = text.c_str();

			if (strcmp(a, checking) == 0)
				return true;


			index = 0;
			symbol = getc(f);
			delete checking;
			goto start;
		}
		return false;
	}
	return false;
}
void guest_menu(Database& data, Guest& guest)
{

	float balance;
	cout << "Balans: "; cin >> balance;

	guest.set_balance(balance);
	system("cls");
	data.show_all_products();
	system("pause");

guest_menu:
	int row = 0;
	int size = 3;
	while (true)
	{
		system("cls");
		print(row, guest_choice, size);
		cout << endl << "Balance: " << guest.get_balance();
		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}
		else if (temp == 13)
		{
			if (row == 0)
			{
				//Buy Product with ID
				int id;
				system("cls");
				cout << "ID daxil edin: "; cin >> id;
				if (!data.get_product_with_id_bool(id))
				{
					system("cls");
					cout << "Bu ID ile product tapilmadi." << endl;
					system("pause");
				}
				else
				{
					system("cls");
					Product* product = data.get_product_with_id(id);
					if (balance >= product->get_price()) {
						guest.buy_product(product);
						guest.set_balance(guest.get_balance() - product->get_price());
						system("Color 2");
						cout << "Product alindi." << endl;
						system("pause");

					}
					else {
						cout << "Yetersiz vesait." << endl;
						system("pause");
					}


				}

			}
			else if (row == 1)
			{
				//Show Details of Product with ID
				int id;
				system("cls");
				cout << "ID daxil edin: "; cin >> id;
				if (!data.get_product_with_id_bool(id))
				{
					system("cls");
					cout << "Bu ID ile product tapilmadi." << endl;
					system("pause");
				}
				else
				{
					system("cls");
					cout << *(data.get_product_with_id(id));
					system("pause");

				}
			}
			else if (row == 2)
			{
				//show orders
				system("cls");
				guest.show_orders();
				system("pause");
			}

		}
		else if (temp == 27) { return; }
	}
}
void admin_menu(Database& data)
{

	int row = 0;
	int size = 4;
	while (true)
	{
	start:
		system("cls");
		print(row, admin_choice, size);

		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}
		else if (temp == 13)
		{
			if (row == 0)
			{
				if (data.size() == 0)
				{
					system("cls");
					cout << "Hec bir product yoxdur." << endl;
					system("pause");

				}
				for (size_t i = 0; i < data.size(); i++)
				{
					cout << *data.get_data()[i] << endl;
				}
				system("pause");
				//Show ALL Products
			}
			else if (row == 1)
			{
				system("cls");
				//Add Product
				string name, type;
				float price;
				int count;
				int day, month, year;


				cout << "New product name: "; cin >> name;
				cout << endl << "New product type: "; cin >> type;
				cout << endl << "New product price: "; cin >> price;
				cout << endl << "New product count: "; cin >> count;
				cout << "Product istehsal tarixi(xx xx xxxx): "; cin >> day; cin >> month; cin >> year;

				Date date(day, month, year);

				Product* new_product = new Product(name, type, price, count,date);
				data.add_product(new_product);
				system("cls");
				system("Color 2");
				cout << *new_product << endl;
				cout << "Product added succesfully";
				system("pause");
				//system("Color 2");
			}
			else if (row == 2)
			{
				if (data.size() == 0)
				{
					system("cls");
					cout << "Hec bir product yoxdur." << endl;
					system("pause");

				}
				else {
					int id;
					data.show_all_products();
					system("pause");
					system("cls");
					cout << "Delete Product ID: "; cin >> id;
					data.delete_product(id);
					system("cls");
					system("Color 2");
					cout << "Product deleted succesfully";
					system("pause");

				}
				//Delete Product
			}
			else if (row == 3)
			{
				//Update Product
				int id;
				cout << "Update product-in ID daxil edin: "; cin >> id;

				system("cls");
				cout << *data.get_product_with_id(id) << endl;
				system("pause");
				int row = 0;
				int size = 4;
				while (true)
				{
					system("cls");
					print(row, update_product, size);

					int temp = _getch();

					if (temp == 224)
					{
						temp = _getch();

						if (temp == 72)//up
						{
							if (row == 0)
								row = size - 1;
							else
								row--;

						}
						else if (temp == 80)//down
						{
							if (row == size - 1)
								row = 0;
							else
								row++;
						}
					}
					else if (temp == 13)
					{
						if (row == 0)
						{
							string name;
							cout << "New name: "; cin >> name;
							data.get_product_with_id(id)->set_name(name);
							cout << "Changed succesfully" << endl;
							system("pause");
							goto start;
						}
						else if (row == 1)
						{

							string type;
							cout << "New type: "; cin >> type;
							data.get_product_with_id(id)->set_type(type);
							cout << "Changed succesfully" << endl;
							system("pause");
							goto start;
						}
						else if (row == 2)
						{
							float price;
							cout << "New price: "; cin >> price;
							data.get_product_with_id(id)->set_price(price);
							cout << "Changed succesfully" << endl;
							system("pause");
							goto start;
						}
						else if (row == 3)
						{
							int count;
							cout << "New count: "; cin >> count;
							data.get_product_with_id(id)->set_count(count);
							cout << "Changed succesfully" << endl;
							system("pause");
							goto start;
						}
					}
					else if (temp == 27)
					{
						goto start;
					}
				}
			}

			//Update Product
		}
		else if (temp == 27)
		{
			return;
		}
	}
}


void menu(string** arr, int size, Database data) {
menu:

	int row = 0;

	while (true)
	{
		system("cls");
		print(row, arr, size);

		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}

		else if (temp == 13) {//ENTER
		first_part:
			if (row == 2)//EXIT
				return;
			
			system("Color 7");
			string username;
			system("cls");
			cout << "\t\t\t\t\t\t\t\t\t" << "Username: "; cin >> username;
			cout << "\t\t\t\t\t\t\t\t\t" << "Password: ";
			char password_chr[50]{};
			int index = 0;
			while (true)
			{
				temp = _getch();

				if (index < 48)
					password_chr[index++] = char(temp);

				cout << "*";
				if (temp == 13)//ENTER 
				{

					system("cls");
					string sign;
					sign = username + " " + string(password_chr);
					if (row == 0)
					{
						if (check_data(sign, "Admins.txt"))
						{
							system("cls");
							admin_menu(data);
							goto menu;
						}
						else
						{
							system("cls");
							system("Color 4");
							cout << "Parol yanlisdir." << endl;
							system("pause");
							goto menu;
						}

					}
					else if (row == 1)
					{
						if (check_data(sign, "Guest.txt"))
						{
							system("cls");
							Guest guest(username, string(password_chr));
							guest_menu(data, guest);
							goto menu;
						}
						else
						{
							system("cls");
							system("Color 4");
							cout << "Parol yanlisdir." << endl;
							system("pause");
							goto menu;
						}
					}
					
				}
				else if (temp == 27)
				{
					goto menu;
				}

			}
			system("cls");

		}
	}


}
void sign_in();

