#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "tree.h"
#include "../sha256-master/sha256.h"
#include "../sha256-master/sha256.c"
using namespace std;

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
					User* temp_user = new User(login, password);
					temp_tree.insert_with_ptr(temp_user);
					temp_user = nullptr; // ��� ���������� ������ ������
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

//ofstream& operator <<(ofstream& customer_file, const Customer& obj)
//{
//	customer_file << obj.get_login() << ";" << SHA256::hashString(obj.get_password()) << ";" << obj.get_role() << ";\n";
//	return customer_file;
//}