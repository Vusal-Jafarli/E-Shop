#pragma once

class Date
{
	size_t _day;
	size_t _month;
	size_t _year;

public:
	Date()
	{
		_day = 0;
		_month = 0;
		_year = 0;
	}
	Date(size_t day, size_t month, size_t year)
	{
		_day = day;
		_month = month;
		_year = year;
	}

	void show()
	{
		cout << _day << "." << _month << "." << _year << endl;
	}

	friend ostream& operator<<(ostream& os, Date& date);
};
ostream& operator<<(ostream& os, Date& date)
{
	os << date._day << "." << date._month << "." << date._year << endl;
	return os;
}



class Product
{
	static int _static_id;
	int _id;
	string _name;
	string _type;
	float _price;
	Date _istehsal_tarixi;
	int _count;

public:
	Product(string name, string type, float price, int count, Date date)
		:_name(name), _type(type), _price(price), _count(count), _istehsal_tarixi(date)
	{
		_id = _static_id++;
	}
	Product(const Product& other)
	{
		this->_id = other._id;
		this->_name = other._name;
		this->_type = other._type;
		this->_price = other._price;
		this->_count = other._count;
		this->_istehsal_tarixi = other._istehsal_tarixi;
	}

	int get_id() { return _id; }
	string get_name() { return _name; }
	string get_type() { return _type; }
	float get_price() { return _price; }
	float get_count() { return _count; }
	Date& get_date() { return _istehsal_tarixi; }

	void set_name(string& name) { _name = name; }
	void set_type(string& type) { _type = type; }
	void set_price(float price)
	{
		if (price > 0 && price < 100000)
			_price = price;
	}
	void set_count(float count)
	{
		if (count >= 0 && count <= 100000)
			_count = count;
	}
	void set_date(Date& date) { _istehsal_tarixi = date; }
	void show_details()
	{
		cout << "ID: " << _id << endl
			<< "Name of product: " << _name << endl
			<< "Type of product: " << _type << endl
			<< "Price of product: " << _price << endl
			<< "Count of product: " << _count << endl
			<< "Istehsal tarixi: " << _istehsal_tarixi << endl;
	}
	void show()
	{
		cout << "ID: " << _id << endl
			<< "Name: " << _name << endl;
	}
	friend ostream& operator<<(ostream& os, Product product);

	bool operator==(const Product& other)
	{
		return  (_id == other._id && _name == other._name
			&& _type == other._type && _price == other._price && _count == other._count);
	}


};
int Product::_static_id = 1;
ostream& operator<<(ostream& os, Product product)
{
	os << "ID: " << product._id << endl
		<< "Name of product: " << product._name << endl
		<< "Type of product: " << product._type << endl
		<< "Price of product: " << product._price << endl
		<< "Count of product: " << product._count << endl
		<< "Istehsal tarixi: " << product._istehsal_tarixi << endl;

	return os;

}



class Database
{
	Product** _products;
	int _products_count;

public:
	Database()
	{
		_products = nullptr;
		_products_count = 0;
	}
	Database(Product** products, int products_count)
	{
		Product** new_products = new Product * [products_count] {};

		for (size_t i = 0; i < products_count; i++)
		{
			new_products[i] = new Product(*products[i]);
		}
		_products = new_products;
		_products_count = products_count;

	}

	int size() { return _products_count; }
	Product** get_data() { return _products; }
	Product* get_product_with_id(int id)
	{
		for (size_t i = 0; i < _products_count; i++)
		{
			if (_products[i]->get_id() == id)
			{
				return _products[i];
			}
		}
	}
	bool get_product_with_id_bool(int id)
	{
		for (size_t i = 0; i < _products_count; i++)
		{
			if (_products[i]->get_id() == id)
			{
				return true;
			}
		}
		return false;
	}
	bool add_product(Product* other)
	{
		if (other == nullptr) { return false; }

		Product** new_products = new Product * [_products_count + 1] {};

		for (size_t i = 0; i < _products_count; i++)
			new_products[i] = new Product(*_products[i]);

		new_products[_products_count] = new Product(*other);

		for (size_t i = 0; i < _products_count; i++)
			delete _products[i];
		delete _products;

		_products = new_products;
		_products_count++;
		return true;
	}
	void show_all_products()
	{
		for (size_t i = 0; i < _products_count; i++)
		{
			_products[i]->show();
			cout << "------------------------" << endl;
		}
	}
	bool delete_product(Product* other)
	{
		int index = -1;
		for (size_t i = 0; i < _products_count; i++)
		{
			if (*(_products[i]) == *other)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
		{
			return false;
		}

		Product** new_products = new Product * [_products_count - 1] {};

		for (size_t i = 0; i < index; i++)
			new_products[i] = new Product(*_products[i]);


		for (size_t i = index + 1; i < _products_count; i++)
			new_products[i - 1] = new Product(*_products[i]);

		for (size_t i = 0; i < _products_count; i++)
			delete _products[i];
		delete _products;

		_products = new_products;
		_products_count--;

		return true;
	}
	bool delete_product(int id)
	{
		int index = -1;
		for (size_t i = 0; i < _products_count; i++)
		{
			if (_products[i]->get_id() == id)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
		{
			return false;
		}

		Product** new_products = new Product * [_products_count - 1] {};

		for (size_t i = 0; i < index; i++)
			new_products[i] = new Product(*_products[i]);


		for (size_t i = index + 1; i < _products_count; i++)
			new_products[i - 1] = new Product(*_products[i]);

		for (size_t i = 0; i < _products_count; i++)
			delete _products[i];
		delete _products;

		_products = new_products;
		_products_count--;

		return true;
	}
	//void update_product(Product* other);
};

class Admin
{
	string _name;
	string _surname;
	string _username;
	string _password;


public:
	Admin(string username, string password)
	{
		set_username(username);
		set_password(password);
		_name = "";
		_surname = "";
	}
	Admin(string name, string surname, string username, string password)
		:_name(name), _surname(surname), _username(username), _password(password) {}

	string get_name() { return _name; }
	string get_surname() { return _surname; }
	string get_username() { return _username; }
	string get_password() { return _password; }


	void set_name(string name)
	{
		if (name != "")
		{
			if (name.size() > 3 && name.size() < 50)
			{
				_name = name;
			}
			else
				throw invalid_argument("Name size yanlisdir.");
		}
		else
			throw invalid_argument("Name yanlisdir.");
	}
	void set_surname(string surname)
	{
		if (surname != "")
		{
			if (surname.size() > 3 && surname.size() < 50)
			{
				_surname = surname;
			}
			else
				throw invalid_argument("Surname size yanlisdir.");
		}
		else
			throw invalid_argument("Surname yanlisdir.");
	}
	void set_username(string username)
	{
		if (username != "")
		{
			if (username.size() > 4 && username.size() < 100)
			{
				_username = username;
			}
			else
				throw invalid_argument("Username size yanlisdir.");
		}
		else
			throw invalid_argument("Username yanlisdir.");
	}
	void set_password(string password)
	{
		if (password != "")
		{
			if (password.size() > 5 && password.size() < 100)
			{
				_password = password;
			}
			else
				throw invalid_argument("Password size yanlisdir.");
		}
		else
			throw invalid_argument("Password yanlisdir.");
	}



	void show()
	{
		cout << "Name(Admin): " << _name << endl
			<< "Surname: " << _surname << endl
			<< "Username: " << _username << endl
			<< "Password: " << _password << endl;

	}
	friend ostream& operator<<(ostream& os, Admin& admin);
};
ostream& operator<<(ostream& os, Admin& admin)
{
	os << "Name(Admin): " << admin._name << endl
		<< "Surname: " << admin._surname << endl
		<< "Username: " << admin._username << endl
		<< "Password: " << admin._password << endl;

	return os;
}

class Guest
{
	string _name = "";
	string _surname = "";
	string _username = "";
	string _password = "";
	float _balance = 0;
	Date _connected_date;
	Product** _orders = nullptr;
	int _orders_count = 0;
public:
	Guest(string name, string surname, string username, string password, Date date, float balance)
	{

		set_name(name);
		set_surname(surname);
		set_username(username);
		set_password(password);
		set_connected_date(date);
		set_balance(balance);

	}
	Guest(string username, string password)
	{
		set_username(username);
		set_password(password);
	}
	string get_name() { return _name; }
	string get_surname() { return _surname; }
	string get_username() { return _username; }
	string get_password() { return _password; }
	float get_balance() { return _balance; }
	Date& get_connected_date() { return _connected_date; }

	void set_name(string name)
	{
		if (name != "")
		{
			if (name.size() > 3 && name.size() < 50)
			{
				_name = name;
			}
			else
				throw invalid_argument("Name size yanlisdir.");
		}
		else
			throw invalid_argument("Name yanlisdir.");
	}
	void set_surname(string surname)
	{
		if (surname != "")
		{
			if (surname.size() > 3 && surname.size() < 50)
			{
				_surname = surname;
			}
			else
				throw invalid_argument("Surname size yanlisdir.");
		}
		else
			throw invalid_argument("Surname yanlisdir.");
	}
	void set_username(string username)
	{
		if (username != "")
		{
			if (username.size() > 3 && username.size() < 100)
			{
				_username = username;
			}
			else
				throw invalid_argument("Username size yanlisdir.");
		}
		else
			throw invalid_argument("Username yanlisdir.");
	}
	void set_password(string password)
	{
		if (password != "")
		{
			if (password.size() > 3 && password.size() < 100)
			{
				_password = password;
			}
			else
				throw invalid_argument("Password size yanlisdir.");
		}
		else
			throw invalid_argument("Password yanlisdir.");
	}
	void set_connected_date(Date date)
	{
		_connected_date = date;
	}
	void set_balance(float balance)
	{
		if (balance >= 0)
		{
			_balance = balance;

		}
	}

	void buy_product(Product* other)
	{
		if (other == nullptr) { return; }

		Product** new_products = new Product * [_orders_count + 1] {};

		for (size_t i = 0; i < _orders_count; i++)
			new_products[i] = new Product(*_orders[i]);

		new_products[_orders_count] = new Product(*other);

		for (size_t i = 0; i < _orders_count; i++)
			delete _orders[i];
		delete _orders;

		_orders = new_products;
		_orders_count++;
		other->set_count(other->get_count() - 1);
	}
	void show_orders()
	{
		for (size_t i = 0; i < _orders_count; i++)
		{
			_orders[i]->show();
			cout << "------------------------" << endl;
		}
	}


	void show()
	{
		cout << "Name(Guest): " << _name << endl
			<< "Surname: " << _surname << endl
			<< "Username: " << _username << endl
			<< "Password: " << _password << endl
			<< "Balance: " << _balance << endl
			<< "Connected Date: " << _connected_date << endl;

	}

	friend ostream& operator<<(ostream& os, Guest& guest);

};
ostream& operator<<(ostream& os, Guest& guest)
{
	os << "Name(Guest): " << guest._name << endl
		<< "Surname: " << guest._surname << endl
		<< "Username: " << guest._username << endl
		<< "Password: " << guest._password << endl
		<< "Balance: " << guest._balance << endl
		<< "Connected Date: " << guest._connected_date << endl;

	return os;
}

