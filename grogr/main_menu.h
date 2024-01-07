#pragma once
#include "tree.h"
#include "file_database.h"
#include "admin_interface.h"

class MENU
{
public:
	MENU() {}
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

				string hesh_pass = SHA256::hashString(password);
				guest = new Customer(login, hesh_pass);
				guest = customer_tree.check_customer_to_login_in(guest);
				if (guest == nullptr)
				{
					system("cls");
					cout << "��� ������ ������������." << endl;
				}
				else if (guest->get_role() == 0)
				{
					system("cls");
					cout << "����� ����������, " << login << " !!" << endl;
					is_come = true;
					User_interface ui(country_tree, database);
					ui.user_screen();
				}
				else if (guest->get_role() == 1)
				{
					system("cls");
					cout << "����� ����������, " << login << " !!" << endl;
					cout << "� ��� ���� ����� ��������������." << endl;

					is_come = true;
					Admin_interface ai(country_tree, customer_tree, database);
					ai.admin_screen();
				}
				country_tree.clear_tree();
				customer_tree.clear_tree();
			}
			else if (choice == 2)
			{
				customer_tree = database.read_customers_from_file();
				cout << "\n������� �����: " << endl;
				cin.ignore();
				getline(cin, login);
				cout << "������� ������: " << endl;
				getline(cin, password);
				string hesh_pass = SHA256::hashString(password);

				guest = new User(login, hesh_pass);

				while (customer_tree.is_same(guest))
				{
					cout << "\n������������ � ������� " << login << " ��� ����������" << endl;
					cout << "���������� ������ �����: ";
					getline(cin, login);
					guest->set_login(login);
				}

				customer_tree.insert_with_ptr(guest);

				// ������ ������ � ����
				database.write_tree_to_file(customer_tree);

				cout << "�� ������� ����������������!" << endl;
				customer_tree.clear_tree();
			}
			else
			{
				cout << "\n��� ������ ������." << endl;
			}
		} while (!is_come);

		guest = nullptr;
		delete guest;
	}
};
