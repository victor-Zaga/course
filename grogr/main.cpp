#include "country.cpp"
#include "tree.cpp"
#include <fstream>
#include <type_traits>

int input_int(int& value)
{
	while (true)
	{
		if (std::cin >> value)
		{
			break;
		}
		else {
			std::cout << "������! ������������ ����.\n";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << std::endl;
		}
	}
	return value;
}

class file_database
{
private:
	string customers_file;
	string countries_file;

public:
	file_database(const string& _customers_file, const string& _countries_file) : customers_file(_customers_file), countries_file(_countries_file) {}
	~file_database() {}

	// ����� ��� ������ ������������� �� ����� � ������ �������������
	BinaryTree<Customer*> read_customers_from_file()
	{
		BinaryTree<Customer*> temp_tree;
		ifstream file(customers_file);  // �������� ������� ��� ����0�� �� �����

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
					User* temp_user = new User(login, password, 0);
					temp_tree.insert_with_ptr(temp_user);
					temp_user = nullptr; // ��� ���������� ������ ������
					delete temp_user;
				}
				else if (role == 1)
				{
					Admin* temp_admin = new Admin(login, password, 1);
					temp_tree.insert_with_ptr(temp_admin);
					temp_admin = nullptr;
					delete temp_admin;
				}
			}

			file.close();
			temp_tree.rebalanceIndexesPreOrder();
		}
		else
		{
			cout << "������ ��� �������� �����." << customers_file << endl;
		}
		return temp_tree;
	}

	BinaryTree<country*> read_countries_from_file()
	{
		BinaryTree<country*> temp_tree;
		ifstream file(countries_file);  // �������� ������� ��� ����0�� �� �����

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

				country* temp_country = new country(name, continent, area, population, capital);
				temp_tree.insert_with_ptr(temp_country);
				temp_country = nullptr;
				delete temp_country;
			}

			file.close();
			temp_tree.rebalanceIndexesPreOrder(); // ������ ������� � ������� pre-order
		}
		else
		{
			cout << "������ ��� �������� �����." << countries_file << endl;
			temp_tree = BinaryTree<country*>();
			return temp_tree; // ������� try catch
		}
		return temp_tree;
	}
	
	template <typename T>
	void write_tree_to_file(BinaryTree<T>& tree) // T - *Customer
	{
		string file_name;
		// ������� ��������� BaseType ��� Customer, ���� country
		using BaseType = typename remove_pointer<T>::type; // remove_pointer - ��� ��������� ����� �� <type_traits>, ������� ��������� ��� ��������� � ���������� ��� �������, �� ������� ��������� ���� ���������.

		if (is_same<BaseType, Customer>::value)  // is_same - ��� ��������� ����� �� <type_traits>, ������� ������������� ����������� ��������� value, ������ true, ���� ��� ��� ��������� ����� ���������� ���, � false � ��������� ������.
		{
			file_name = customers_file;
		}
		else if (is_same<BaseType, country>::value) 
		{
			file_name = countries_file;
		}
		
		ofstream file(file_name); // �������� ������� ��� ������ � ����

		if (file.is_open())
		{
			tree.write_data_to_file_(file);
			file.close();
		}
		else
		{
			cout << "������ ��� �������� �����." << customers_file << endl;
		}
	}

};	

ofstream& operator <<(ofstream& country_file, const country& obj) 
{
	country_file << obj.to_string();
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
	BinaryTree<country*> country_tree;
	file_database database;
public:
	User_interface(BinaryTree<country*> _country_tree, file_database _database) : country_tree(_country_tree), database(_database) {}
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
		cout << "\n1. ����� ���������� � �������, ��������������� �� ����������� ���������." << endl;
		cout << "2. ����� ����� ��� ��������� ���������� � ���������� �������." << endl;
		cout << "3. ����� ���������� �� ������� � �������� ���������. " << endl;
	}

	void user_screen()
	{
		while(true)
		{
			show_menu();
			cout << "0. �����." << endl;
			cout << "�������� �����: ";
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
				cout << "\n����" << endl;
				return;

			default:
				cout << "��� ������ ������ ����." << endl;
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
	Admin_interface(BinaryTree<country*> _country_tree, BinaryTree<Customer*> _customer_tree, file_database _database) : User_interface(_country_tree, _database)
	{
		customer_tree = _customer_tree;
	}
	~Admin_interface() { }

	void add_country()
	{	
		country_tree.add_country_();
		country_tree.rebalanceIndexesPreOrder(); // ������������ �������� ����� ����������
	}

	void add_customer()
	{
		customer_tree.add_customer_();
		customer_tree.rebalanceIndexesPreOrder();
	}

	void admin_screen()
	{
		BinaryTree<country*> original_country_tree;
		BinaryTree<Customer*> original_customer_tree;
		BinaryTree<country*> last_saved_country_tree;
		BinaryTree<Customer*> last_saved_customer_tree;

		BinaryTree<country*> country_tree_to_view;
		BinaryTree<Customer*> customer_tree_to_view;

		original_country_tree = country_tree;
		original_customer_tree = customer_tree;

		bool check_chenges = false;
		bool is_save = false;
		bool is_becup = false;
		while (true)
		{
			show_menu(); // 1 2 3 
			cout << "4. ������� ����� ������." << endl;	
			cout << "5. ������� ������ ������������. " << endl;
			cout << "6. ����� �������������." << endl;
			cout << "7. �������� �������� ������." << endl;
			cout << "8. �������� ��������� ������������." << endl;
			cout << "9. �������������� �������� ������." << endl;
			cout << "10. �������������� ��������� ������������." << endl;
			cout << "11. ���������� ��������� � ����" << endl;
			cout << "12. ������ ���������" << endl;
			cout << "0. �����." << endl;
			cout << "�������� �����: ";
			int choice = input_int(choice);
			switch (choice)
			{
			case 1:
				country_tree_to_view = database.read_countries_from_file();
				country_tree_to_view.printTreePopulationUp();
				break;
			case 2:
				country_tree_to_view = database.read_countries_from_file();
				country_tree_to_view.out_continent_countries_alfavit(country_tree_to_view);
				break;
			case 3:
				/*country_tree = database.read_countries_from_file();
				search_for_interval();*/
				country_tree_to_view = database.read_countries_from_file();
				country_tree_to_view.search();
				break;
			case 4:
				add_country();
				is_becup = false;
				break;
			case 5:
				add_customer();
				is_becup = false;
				break;

			case 6:
				customer_tree_to_view = database.read_customers_from_file();
				customer_tree_to_view.print_customers();
				//customer_tree.print_customers();
				break;

			case 7:
				country_tree.remove();
				break;

			case 8:
				customer_tree.remove();
				break;

			case 9:
				country_tree.changing_country_info();
				break;

			case 10:
				customer_tree.changing_customer_info();
				break;

			case 11:
				// ���������� ��������� � ����
				database.write_tree_to_file(country_tree);
				database.write_tree_to_file(customer_tree);
				// ���������� ��������� ����� ������������
				if (is_save)
				{
					original_country_tree = last_saved_country_tree;
					original_customer_tree = last_saved_customer_tree;
				}
				last_saved_country_tree = country_tree; // ���������� ������ ������� ��� ������
				last_saved_customer_tree = customer_tree;
				cout << "\n���������� ���� �������� � ����." << endl;
				is_save = true;
				is_becup = false;
				break;

			case 12:
				// ������ ���������
				if (is_save && !is_becup)  // ����� 10 ������ ����� ��������� ���� ��������
				{ // �� 2 ���� ������
					country_tree = original_country_tree;
					customer_tree = original_customer_tree;
					database.write_tree_to_file(country_tree);
					database.write_tree_to_file(customer_tree);
					cout << "\n��������� ���� ��������." << endl;
					last_saved_country_tree = country_tree; // ��� �� ����� ���������� ���������� �������, �.�. �������� ���������
					last_saved_customer_tree = customer_tree;
					is_becup = true;
				}
				else
				{
					cout << "\n��������� ��� �� ���� �������." << endl;
				}
				break;

			case 0:
				original_country_tree.clear_tree();
				original_customer_tree.clear_tree();

				last_saved_country_tree.clear_tree();
				last_saved_customer_tree.clear_tree();

				country_tree_to_view.clear_tree();
				customer_tree_to_view.clear_tree();
				cout << "\n����" << endl;
				return;

			default:
				cout << "��� ������ ������ ����." << endl;
				break;
			}

		} 
	}
};

class MENU
{
private:
	//file_database database; //�� & - �������� � (���� �������) ������������� ���������, ������� ��������� � ����, � �� � �� �������
	//BinaryTree<Customer*>& customer_tree; // ����� ��������� ����������� �� � ���� �����, � �� � ������������ �������
	//BinaryTree<country> country_tree;

public:	
	//MENU(file_database _database, BinaryTree<Customer*>& _customer_tree, BinaryTree<country> _country_tree) : database(_database), customer_tree(_customer_tree), country_tree(_country_tree) {}
	MENU() {}
	~MENU() {}
	void main_menu()
	{
		BinaryTree<country*> country_tree; // �������� ������ �����
		BinaryTree<Customer*> customer_tree; // ������ �������������
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
			cout << "\n1. �����" << endl;
			cout << "2. ������������������" << endl;
			cout << "�������� �����: ";
			choice = input_int(choice);
			if (choice == 1)
			{
				customer_tree = database.read_customers_from_file();
				country_tree = database.read_countries_from_file();
				cout << "\n������� �����: " << endl;
				cin.ignore();
				getline(cin, login);
				cout << "������� ������: " << endl;
				getline(cin, password);

				guest = new Customer(login, password);
				guest = customer_tree.check_customer_to_login_in(guest);
				if (guest == nullptr)
				{
					system("cls");
					cout << "��� ������ ������������." << endl;
				}
				else if (guest->get_role() == 0)
				{
					system("cls");
					cout << "����� ����������!!" << endl;

					cout << "��� �����: " << login << endl;
					cout << "��� ������: " << password << endl;
					is_come = true;
					User_interface ui(country_tree, database);
					ui.user_screen();
				}
				else if (guest->get_role() == 1)
				{
					system("cls");
					cout << "����� ����������!!" << endl;
					cout << "� ��� ���� ����� ��������������" << endl;

					cout << "��� �����: " << login << endl;
					cout << "��� ������: " << password << endl;
					is_come = true;
					Admin_interface ai(country_tree, customer_tree, database);
					ai.admin_screen();
				}
			}
			else if (choice == 2)
			{
				customer_tree = database.read_customers_from_file();
				cout << "\n������� �����: " << endl;
				cin.ignore();
				getline(cin, login);
				cout << "������� ������: " << endl;
				getline(cin, password);

				guest = new User(login, password, 0);

				while(customer_tree.is_same(guest))
				{
					cout << "\n������������ � ������� " << login << " ��� ����������" << endl;
					cout << "���������� ������ �����: " << endl;
					getline(cin, login);
					guest->set_login(login);
				}

				customer_tree.insert_with_ptr(guest);

				// ������ ������ � ����
				database.write_tree_to_file(customer_tree);

				cout << "�� ������� ����������������!" << endl;
			}
			else
			{
				cout << "��� ������ ������." << endl;
			}
		} while (!is_come);

		guest = nullptr;
		delete guest;
		country_tree.clear_tree();
		customer_tree.clear_tree();
	}
};

int main()
{
	system("chcp 1251\n");
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

	//cout << "������ � ������� ����������� �� ���������: \n" << endl;
	//countryTree.printInOrder();

	//�������� ����
	//countryTree.remove();
	//����� ����� ��������
	//countryTree.printTreePopulation();
	//cout << "--------------------------------" << endl;

	// ������������ ������ �� �������� ������ � �����
	//countryTree.out_continent_countries_alfavit(countryTree);

	// ����� �� ��������� ������� 
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
	ui.main_menu();

	return 0;
}

