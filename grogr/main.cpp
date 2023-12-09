#include "country.cpp"
#include "tree.cpp"
#include <fstream>
#include <sstream>

int input_int(int& value)
{
	while (true)
	{
		if (std::cin >> value)
		{
			break;
		}
		else {
			std::cout << "Ошибка! Некорректный ввод.\n";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << std::endl;
		}
	}
	return value;
}

class Admin : public Customer
{
private:
	const int is_admin = 1;
public:
	Admin(const string& _login, const string& _password) : Customer(_login, _password) {}
	Admin() : Customer() {}
	~Admin() {}

	string get_login() const { return login; }
	string get_password() const { return password; }

	/*string to_string() override
	{
		char separator = ';';
		string curr_user = this->get_login() + separator + this->get_password() + separator + "ADMIN" + separator;
		return curr_user;
	}*/

	void show() override
	{
		cout << "Вы администратор!!" << endl;
		cout << login << endl;
		cout << password << endl;
		cout << is_admin << endl;
	}

	int get_role() const override
	{
		return is_admin;
	}
};


class file_database
{
private:
	string customers_file;
	string countries_file;

public:
	file_database(const string& _customers_file, const string& _countries_file) : customers_file(_customers_file), countries_file(_countries_file) {}
	~file_database() {}

	// метод для чтения пользователей из файла в дерево пользователей
	BinaryTree<Customer*> read_customers_from_file()
	{
		BinaryTree<Customer*> temp_tree;
		ifstream file(customers_file);  // создание объекта для чтен0ия из файла

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				stringstream ss(line);
				string login, password;
				int role = 0;

				getline(ss, login, ';');
				getline(ss, password, ';');
				ss >> role;
				
				if (role == 0)
				{
					User* temp_user = new User(login, password);
					temp_tree.insert_with_ptr(temp_user);
					temp_user = nullptr; // для корректной работв дерева
					delete temp_user;
				}
				else if (role == 1)
				{
					Admin* temp_admin = new Admin(login, password);
					temp_tree.insert_with_ptr(temp_admin);
					temp_admin = nullptr;
					delete temp_admin;
				}
			}

			file.close();
		}
		else
		{
			cout << "Ошибка при открытия файла." << customers_file << endl;
		}
		return temp_tree;
	}

	BinaryTree<country> read_countries_from_file()
	{
		BinaryTree<country> temp_tree;
		ifstream file(countries_file);  // создание объекта для чтен0ия из файла

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				stringstream ss(line);
				string name, continent, capital;
				double area = 0;
				double population = 0;

				getline(ss, name, ';');
				getline(ss, continent, ';');

				ss >> area;
				ss.ignore();
				ss >> population;
				ss.ignore();
				getline(ss, capital, ';');

				country temp_country = country(name, continent, area, population, capital);
				temp_tree.insert(temp_country);
				//temp_country = nullptr;
				//delete temp_country;
			}

			file.close();
		}
		else
		{
			cout << "Ошибка при открытия файла." << countries_file << endl;
			temp_tree = BinaryTree<country>();
			return temp_tree; // сделать try catch
		}
		return temp_tree;
	}

	//void write_customers_to_file(BinaryTree<Customer*> customer_tree)
	//{
	//	ofstream file(customers_file); // создание объекта для записи в файо

	//	if (file.is_open())
	//	{
	//		customer_tree.write_customers_to_file_rec(file);
	//	}
	//	else
	//	{
	//		cout << "Ошибка при открытия файла." << customers_file << endl;
	//	}
	//}
	
	template <typename T>
	void write_customers_to_file(BinaryTree<T>& tree) // T - *Customer
	{
		string file_name;
		if (is_same<T, Customer>::value)
		{
			file_name = customers_file;
		}
		else if (is_same<T, country>::value)
		{
			file_name = countries_file;
		}
		ofstream file(file_name); // создание объекта для записи в файл

		if (file.is_open())
		{
			tree.write_data_to_file_(file);
		}
		else
		{
			cout << "Ошибка при открытия файла." << customers_file << endl;
		}
	}

};	

ofstream& operator <<(ofstream& country_file, const country& obj) 
{
	country_file << obj.get_name();
	country_file << obj.get_continent();
	country_file << obj.get_area();
	country_file << obj.get_population();
	country_file << obj.get_capital();
	return country_file;
}

ofstream& operator <<(ofstream& customer_file, const Customer& obj)
{
	customer_file << obj.get_login() << ";" << obj.get_password() << ";" << obj.get_role() << ";\n";
	return customer_file;
}

class User_interface
{
protected:
	BinaryTree<country> country_tree;
	file_database database;
public:
	User_interface(BinaryTree<country> _country_tree, file_database _database) : country_tree(_country_tree), database(_database) {}
	~User_interface() {}
	void Print_tree_population()
	{
		country_tree.printTreePopulationUp();
	}
	void Print_countries_for_continent()
	{
		country_tree.out_continent_countries_alfavit(country_tree);
	}
	void search_for_interval()
	{
		country_tree.search();
	}

	void show_menu() const
	{
		cout << "\n1. Вывод информации о странах, отсортированную по численности населения." << endl;
		cout << "2. Вывод стран для заданного континента в алфавитном порядке." << endl;
		cout << "3. Поиск информации по площади в заданном диапазоне. " << endl;
	}

	void user_screen()
	{
		while(true)
		{
			show_menu();
			cout << "0. Выход." << endl;
			cout << "Сделайте выбор: ";
			int choice = input_int(choice);
			switch (choice)
			{
			case 1:
				country_tree = database.read_countries_from_file();
				Print_tree_population();
				break;
			case 2:
				country_tree = database.read_countries_from_file();
				Print_countries_for_continent();
				break;
			case 3:
				country_tree = database.read_countries_from_file();
				search_for_interval();
				break;
			case 0:
				cout << "\nПока" << endl;
				return;

			default:
				cout << "Нет такого пункта меню." << endl;
				break;
			}
		}
	}
};

class Admin_interface : public User_interface
{
private:
	BinaryTree<Customer*> customer_tree;
	
public:
	Admin_interface(BinaryTree<country> _country_tree, BinaryTree<Customer*> _customer_tree, file_database _database) : User_interface(_country_tree, _database)
	{
		customer_tree = _customer_tree;
	}
	~Admin_interface() {}

	void add_country()
	{
		country_tree.add_country_();
	}

	void add_customer()
	{
		customer_tree.add_customer_();
	}

	void admin_screen()
	{
		while (true)
		{
			show_menu();
			cout << "4. Вставка новой страны." << endl;	
			cout << "5. Вставка нового пользователя. " << endl;
			cout << "6. Удаление заданной страны." << endl;
			cout << "7. Удаление заданного пользователя." << endl;
			cout << "8. Редактирование заданной страны." << endl;
			cout << "9. Редактирование заданного пользователя." << endl;
			cout << "10. Сохранение изменений в файл" << endl;
			cout << "11. Отмена изменений" << endl;
			cout << "0. Выход." << endl;
			cout << "Сделайте выбор: ";
			int choice = input_int(choice);
			switch (choice)
			{
			case 1:
				country_tree = database.read_countries_from_file();
				Print_tree_population();
				break;
			case 2:
				country_tree = database.read_countries_from_file();
				Print_countries_for_continent();
				break;
			case 3:
				country_tree = database.read_countries_from_file();
				search_for_interval();
				break;
			case 4:
				country_tree = database.read_countries_from_file();
				add_country();
				// добавить в файл изменения 
				break;
			
			case 5:
				customer_tree = database.read_customers_from_file();
				add_customer();
				break;

			case 6:
				break;

			case 7:
				break;

			case 8:
				break;
			case 9:
				break;
			case 10:
				database.write_customers_to_file(country_tree);
				break;

			case 0:
				cout << "\nПока" << endl;
				return;

			default:
				cout << "Нет такого пункта меню." << endl;
				break;
			}

		}
	}
};

class MENU
{
private:
	//file_database database; //по & - работаем с (ориг деревом) оригинальными объектами, которые объявлены в мейн, а не с их копиями
	//BinaryTree<Customer*>& customer_tree; // чтобы изменения происходили не в этой копии, а не в оригинальном объекте
	//BinaryTree<country> country_tree;

public:	
	//MENU(file_database _database, BinaryTree<Customer*>& _customer_tree, BinaryTree<country> _country_tree) : database(_database), customer_tree(_customer_tree), country_tree(_country_tree) {}
	MENU() {}
	~MENU() {}
	void menu()
	{
		BinaryTree<country> country_tree; // создание дерева стран
		BinaryTree<Customer*> customer_tree; // дерева пользователей
		string customers_file = "Users.txt";
		string countries_file = "Countries.txt";
		file_database database(customers_file, countries_file);
		int choice = 0;
		string login;
		string password;
		Customer* guest = nullptr;
		bool is_come = false;
		do
		{
			cout << "\n1. Войти" << endl;
			cout << "2. Зарегистрироваться" << endl;
			cout << "Сделайте выбор: ";
			choice = input_int(choice);
			if (choice == 1)
			{
				customer_tree = database.read_customers_from_file();
				cout << "\nВведите логин: " << endl;
				cin.ignore();
				getline(cin, login);
				cout << "Введите пароль: " << endl;
				getline(cin, password);

				guest = new Customer(login, password);
				guest = customer_tree.check_customer_to_login_in(guest);
				if (guest == nullptr)
				{
					system("cls");
					cout << "\nНет такого пользователя." << endl;
				}
				else if (guest->get_role() == 0)
				{
					system("cls");
					cout << "\nДобро пожаловать!!" << endl;

					cout << "Ваш логин: " << login << endl;
					cout << "Ваш пароль: " << password << endl;
					is_come = true;
					User_interface ui(country_tree, database);
					ui.user_screen();
				}
				else if (guest->get_role() == 1)
				{
					system("cls");
					cout << "\nДобро пожаловать!!" << endl;
					cout << "У вас есть права администратора" << endl;

					cout << "Ваш логин: " << login << endl;
					cout << "Ваш пароль: " << password << endl;
					is_come = true;
					Admin_interface ai(country_tree, customer_tree, database);
					ai.admin_screen();
				}
			}
			else if (choice == 2)
			{
				customer_tree = database.read_customers_from_file();
				cout << "\nВведите логин: " << endl;
				cin.ignore();
				getline(cin, login);
				cout << "Введите пароль: " << endl;
				getline(cin, password);

				guest = new User(login, password);
				customer_tree.insert_with_ptr(guest);

				// запись дерева в файл
				database.write_customers_to_file(customer_tree);

				cout << "Вы успешно зарегистрированы!" << endl;
			}
			else
			{
				cout << "Нет такого пункта." << endl;
			}
		} while (!is_come);

		guest = nullptr;
		delete guest;
	}
};

int main()
{
	system("chcp 1251\n");
	cout << "\n";
	//BinaryTree<country> countryTree;
	
	//countryTree.create_country_tree();
	//country obj1 = country("Russia", "North America", 17.1, 144.4, "Moscow");
	//country obj2 = country("China", "Asia", 9.6, 140.0, "Beijing");
	//country obj3 = country("MSA", "North America", 9.8, 331.0, "Washington, D.C.");
	//country obj4 = country("Huilo", "North America", 20, 200, "Hihihiha");
	//country obj5 = country("Kucushka", "North America", 15, 500, "hihihahi");

		//countryTree.insert(obj1);
		//countryTree.insert(obj2);
		//countryTree.insert(obj3);
		//countryTree.insert(obj4);	
		//countryTree.insert(obj5);

	//cout << "Страны в порядке возрастания их населения: \n" << endl;
	//countryTree.printInOrder();

	//удаление тест
	//countryTree.remove();
	//вывод после удаления
	//countryTree.printTreePopulation();
	//cout << "--------------------------------" << endl;

	// балансировка дерева по названию страны и вывод
	//countryTree.out_continent_countries_alfavit(countryTree);

	// поиск по диапазону площади 
	//countryTree.search();

	//BinaryTree<Customer*> Customer_tree;
	//string customers_file = "Users.txt";
	//string countries_file = "Countries.txt";
	
	//User obj1("fufel", "North");
	//Admin obj2("alice_smith", "Asia");
	//Admin obj3("dmitriy", "North Am");
	//Customer_tree.insert_with_ptr(&obj1);
	//Customer_tree.insert_with_ptr(&obj2);
	//Customer_tree.insert_with_ptr(&obj3);

	//file_database database(customers_file, countries_file);
	//database.read_customers_from_file();

	MENU ui;
	ui.menu();

	return 0;
}
