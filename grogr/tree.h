#pragma once
#include "country.h"
#include "customer.h"
#include "user.h"
#include "admin.h"
#include "service.h"
#include "../sha256-master/sha256.h"
#include "../sha256-master/sha256.c"
using namespace std;

template <typename T>
class BinaryTree {
private:
	struct Node {
		T data; //Customer* data; // country* data
		Node* left;
		Node* right;
		int index; // ������ ��������

		Node(const T& value, int _index) : data(value), left(nullptr), right(nullptr), index(_index) {}
		Node() : data(nullptr), left(nullptr), right(nullptr), index(0) {}
	};

	Node* root;

public:
	BinaryTree() : root(nullptr) {}

	//// ����������� �����������
	//BinaryTree(const BinaryTree& tree_to_copy) : root(nullptr) {
	//	root = copy_Node(tree_to_copy.root);
	//}

	// �������� ������������
	BinaryTree& operator =(const BinaryTree& tree_to_save) {
		if (this != &tree_to_save) //this - ������ � ������� ����� ���������, tree_to_save - ������� ����� ���������
		{
			this->clear_tree(); // ������� ������� ������
			root = copy_Node(tree_to_save.root); // ����������� ������ � ������� ������ root
		}
		return *this; // ������� ������ �� ����� ������
	}

	void insert_with_ptr(const T& value)
	{
		int count = count_tree_nodes(root) + 1;
		if (root == nullptr)
		{
			root = new Node(value, count);
		}
		else {
			insertRecursivePtr(root, value, count);
		}
	}

	void insert_for_balance(const T& value)
	{
		int count = count_tree_nodes(root) + 1;
		if (root == nullptr)
		{
			root = new Node(value, count);
		}
		else {
			insert_Recursive_for_balance(root, value, count);
		}
	}

	void printTreePopulationUp()
	{
		printTreePopulation(root);
	}

	// ���������� ������ ��� ������ ����� ��� ��������� ���������, ���� ����� ��� ���������� ���������
	void Print_Tree_For_Continent()
	{
		cout << "\n������� ���������, ������ �������� ����� �������: ";
		cin.ignore();
		string your_continent;
		getline(cin, your_continent);
		int is_continent = 0;
		cout << endl;
		cout << "������ ���������� " << your_continent << " � ���������� �������: " << endl;
		Print_Tree_For_Continent_In_Alfavit(root, your_continent, is_continent);
		if (!is_continent)
		{
			cout << "��� ����� ��� ��������� ����������. \n";
		}
	}

	// ���������������� ������ �� �������� ������ ����� ����� ��� � ���������� �������
	void out_continent_countries_alfavit(BinaryTree<country*> countryTree)
	{
		BinaryTree<country*> new_tree = countryTree.Balance_By_Name(); // ������ new_tree � ���������� ������� �� ������ pre-order
		new_tree.Print_Tree_For_Continent(); // ��� ���� ����� pre-order ������� � ������� ����������� �� ��������
	}

	//�������� ������������ �� ��������� ������, ���� ���������� ������������ �� ������� ������
	void remove_user()
	{
		cout << "\n������� ����� ������������ ��� ��������: ";
		int index_to_delete = 0;
		index_to_delete = input_int(index_to_delete);

		Node* obj_to_delete = get_element_by_index(root, index_to_delete); // ��������� �� ���� � ������, nuppltr � ������ �� ���������� 

		if (obj_to_delete != nullptr && obj_to_delete->data->get_role() == 1) // �������� �� �������� ��������������
		{
			cout << "� ��� ������������ ���� ��� �������� ��������������." << endl;
			return;
		}

		if (obj_to_delete != nullptr)
		{
			root = delele_element(root, obj_to_delete);
			cout << "�������� ������������ ������ �������." << endl;
			rebalanceIndexesPreOrder(); // ���������������� �������� �� ������ ��������� � ������� ����� �������� ��������
		}
		else
		{
			cout << "��� ������������ � ����� �������." << endl;
		}
	}

	//  �������� ������ �� ��������� ������, ���� ���������� ������ � ����� �������
	void remove_country()
	{
		cout << "\n������� ����� ������ ��� ��������: ";
		int index_to_delete = 0;
		index_to_delete = input_int(index_to_delete);

		Node* obj_to_delete = get_element_by_index(root, index_to_delete); // ��������� �� ���� � ������, nuppltr � ������ �� ���������� 

		if (obj_to_delete != nullptr)
		{
			root = delele_element(root, obj_to_delete);
			cout << "�������� ������ ������ �������." << endl;
			rebalanceIndexesPreOrder(); // ���������������� �������� �� ������ ��������� � ������� ����� �������� ��������
		}
		else
		{
			cout << "��� ������ � �������� �������." << endl;
		}
	}

	//������������ ������ �� �������� ������, ���������� ����������������� ������ 
	BinaryTree Balance_By_Name()
	{
		BinaryTree<country*> New_country_tree; // �� ������ 
		Balance_by_name_of_country(root, New_country_tree);
		return New_country_tree;
	}

	// ����� �� ������� �� ��������� ���������
	void search()
	{
		cout << "\n������� ����������� ����� �������: ";
		double min_area = 0;
		min_area = input_area_population(min_area);
		cout << "������� ������������ ����� �������: ";
		double max_area = 0;
		max_area = input_area_population(max_area);
		int count = 0;
		Node* search_arr = nullptr; // ������ �� ��������� ������
		Search_By_Area_Range(root, min_area, max_area, count, search_arr);
		if (search_arr == nullptr)
		{
			cout << "\n��� ����� � �������� ���������� �������.\n";
		}
		else
		{
			cout << "\n������ � �������� � ��������� �� " << min_area << " �� " << max_area << ": " << endl;
			cout << "-------------------------------------------------------------------------------------------\n";
			cout << "| " << "�" << " |  " << "��������" << "  |    " << "���������" << "    | "
				<< "�������(���.��.��)" << " | " << "���������(���.���)" << " |  " << "�������" << "   |\n";
			cout << "-------------------------------------------------------------------------------------------\n";
			for (int i = 0; i < count; i++)
			{
				cout << "| " << search_arr[i].index << " ";
				search_arr[i].data->show();
			}

			delete[] search_arr; // ������������ ������ ������� ���
		}
	}

	// ������ � ��������������
	Customer* check_customer_to_login_in(Customer* guest)
	{
		Customer* check = check_customers_rec(root, *(guest));
		return check;
	}

	void write_data_to_file_(ofstream& file)
	{
		write_to_file_recursive(root, file);
	}

	// ������ ����� ��� ���������������� �������� � ������� pre-order (� ������ ��������� ����� � ����� ������ ���������)
	void rebalanceIndexesPreOrder() {
		int current_index = 0;
		rebalanceRecPreOrder(root, current_index);
	}

	// ������ ����� ��� ���������������� �������� � ������� in-order (������ ���� ����� ��������� ����� ������ ���������)
	void rebalanceIndexesInOrder() {
		int current_index = 0;
		rebalanceRecInOrder(root, current_index);
	}

	void print_customers()
	{
		print_customers_rec(root);
	}

	// ����� ��� ������� ������
	void clear_tree() {
		clear(root);
		root = nullptr;
	}

	// ��������������� ����� ��� �������� �� ���������� �������� � �������� 
	template <typename T> bool is_same(const T& value)
	{
		return is_same_obj(root, value);
	}

	// ���������� ������ � ������ �����, ���� ����� ������ �� ���� �����
	void add_country()
	{
		cin.ignore();
		cout << "\n������� �������� ������: ";
		string your_name;
		getline(cin, your_name);

		cout << "������� ��������� ������: ";
		string your_continent;
		getline(cin, your_continent);

		cout << "������� ������� ������: ";
		double your_area = 0;
		your_area = input_area_population(your_area);

		cout << "������� ���������� ��������� ������: ";
		double your_population = 0;
		your_population = input_area_population(your_population);

		cin.ignore();
		cout << "������� �������� ������� ������: ";
		string your_capital;
		getline(cin, your_capital);

		country* temp_country = new country(your_name, your_continent, your_area, your_population, your_capital);

		if (is_same(temp_country))
		{
			cout << "\n����� ������ ��� ����������." << endl;
		}
		else
		{
			insert_with_ptr(temp_country);
			rebalanceIndexesPreOrder(); // ������������ �������� ����� ���������� ������
			cout << "\n������ ������� ���������." << endl;
		}

		temp_country = nullptr;
		delete temp_country;
	}

	// ����� ��� ���������� ������������ � ������ �������������, ���� ������ ������������ ��� ��� � ������
	void add_user()
	{
		string your_login, your_pass;
		Customer* new_user = nullptr;

		cin.ignore();
		cout << "\n������� ����� ������ ������������: ";
		getline(cin, your_login);

		cout << "������� ������ ������ ������������: ";
		getline(cin, your_pass);
		string hesh_pass = SHA256::hashString(your_pass);
		new_user = new User(your_login, hesh_pass);

		if (is_same(new_user))
		{
			cout << "\n������������ � ������� " << your_login << " ��� ����������." << endl;
		}
		else
		{
			insert_with_ptr(new_user);
			rebalanceIndexesPreOrder();  // ������������ �������� ����� ���������� ������������
			cout << "\n������������ ������� ��������." << endl;
		}
		new_user = nullptr;
		delete new_user;
	}

	// ����� ��� �������������� ������ �� ��������� �������
	void changing_country_info()
	{
		if (root == nullptr) {
			return;
		}

		cout << "\n������� ����� ������ ��� ��������������: ";
		int ind_to_chage = 0;
		ind_to_chage = input_int(ind_to_chage);

		Node* country_to_change = get_element_by_index(root, ind_to_chage);

		if (country_to_change == nullptr)
		{
			cout << "��� ������ � ����� �������." << endl;
			return;
		}

		country* temp_country = new country(country_to_change->data->get_name(), country_to_change->data->get_continent(),
			country_to_change->data->get_area(), country_to_change->data->get_population(),
			country_to_change->data->get_capital());

		root = delele_element(root, country_to_change);  // �������� 
		rebalanceIndexesPreOrder();

		int choice_to_change = 0;
		bool is_leave = false;

		string save_name = temp_country->get_name();
		string save_capital = temp_country->get_capital(); // ���������� ���� �������������� �������
		double save_area = temp_country->get_area();
		double save_population = temp_country->get_population();
		do
		{
			// ����� ���� ��� �������������� ������
			cout << "\n1. ������������� �������� ������\n"
				<< "2. ������������� ���������\n"
				<< "3. ������������� ������� ���������� ������\n"
				<< "4. ������������� ����������� ��������� ������\n"
				<< "5. ������������� ������� ������\n"
				<< "0. ��������� ��������������\n";

			cout << "�������� ��������: ";
			choice_to_change = input_int(choice_to_change);

			string new_name, new_continent, new_capital;
			double new_area = 0;
			double new_population = 0;

			switch (choice_to_change)
			{
			case 1:
				cin.ignore();
				cout << "\n������� ����� �������� ������: ";
				getline(cin, new_name);
				temp_country->set_name(new_name);
				if (is_same(temp_country))
				{
					cout << "\n������ � ����� ��������� ��� ����������." << endl;
					temp_country->set_name(save_name); // ���������� ����������� �������� �������� ������
				}
				else
				{
					cout << "�������� ������ ���������������." << endl;
				}
				break;

			case 2:
				cin.ignore();
				cout << "\n������� ����� ��������� ������: ";
				getline(cin, new_continent);
				temp_country->set_continent(new_continent);
				cout << "��������� ������ ��������������." << endl;
				break;

			case 3:
				cin.ignore();
				cout << "\n������� ����� ������� ���������� ������: ";
				new_area = input_area_population(new_area);
				temp_country->set_area(new_area);
				if (is_same(temp_country))
				{
					cout << "\n������ � ����� �������� ��� ����������." << endl;
					temp_country->set_area(save_area);
				}
				else
				{
					cout << "������� ���������� ������ ���������������." << endl;
				}
				break;

			case 4:
				cin.ignore();
				cout << "\n������� ����� ����������� ���������: ";
				new_population = input_area_population(new_population);
				temp_country->set_population(new_population);
				if (is_same(temp_country))
				{
					cout << "\n������ � ����� ������������ ��������� ��� ����������." << endl;
					temp_country->set_population(save_population);
				}
				else
				{
					cout << "����������� ��������� ������ ���������������." << endl;
				}
				break;

			case 5:
				cin.ignore();
				cout << "\n������� ����� ������� ������: ";
				getline(cin, new_capital);
				temp_country->set_capital(new_capital);
				if (is_same(temp_country))
				{
					cout << "\n������ � ����� �������� ��� ����������." << endl;
					temp_country->set_capital(save_capital);
				}
				else
				{
					cout << "������� ������ ���������������." << endl;
				}
				break;

			case 0:
				cout << "\n�������������� ������ ��������� �������." << endl;
				is_leave = true;
				break;
			default:
				cout << "\n��� ������ ����� ��� ��������������." << endl;
				break;
			}
		} while (!is_leave);


		insert_with_ptr(temp_country);
		rebalanceIndexesPreOrder(); // ������������ �������� ����� ���������� ������
		country_to_change = nullptr;
		delete country_to_change;
	}

	// ����� ��� �������������� ������������ �� ��������� ������� 
	void changing_user_info()
	{
		if (root == nullptr) {
			return;
		}

		cout << "\n������� ����� ������������ ��� ��������������: ";
		int ind_to_change = 0;
		ind_to_change = input_int(ind_to_change);

		Node* customer_to_change = get_element_by_index(root, ind_to_change);

		if (customer_to_change == nullptr)
		{
			cout << "��� ������������ � ����� �������." << endl;
			return;
		}

		if (customer_to_change->data->get_role() == 1)
		{
			cout << "� ��� ������������ ���� ��� �������������� ��������������." << endl;
			return;
		}

		Customer* temp_user = nullptr;

		temp_user = new User(customer_to_change->data->get_login(), customer_to_change->data->get_password());

		root = delele_element(root, customer_to_change);
		rebalanceIndexesPreOrder();

		int choice_to_change = 0;
		bool is_leave = false;
		do
		{
			// ����� ���� ��� �������������� �������������
			cout << "\n1. ������������� ����� ������������\n"
				<< "2. ������������� ������ ������������\n"
				<< "3. ��������� ������������ ���������������\n"
				<< "0. ��������� ��������������\n";

			cout << "�������� ��������: ";
			choice_to_change = input_int(choice_to_change);

			string new_login, new_password, hesh_pass;

			switch (choice_to_change)
			{
			case 1:
				cin.ignore();
				cout << "\n������� ����� ����� ������������: ";
				getline(cin, new_login);
				temp_user->set_login(new_login);
				cout << "����� ��������������." << endl;
				break;

			case 2:
				cin.ignore();
				cout << "\n������� ����� ������ ������������: ";
				getline(cin, new_password);
				hesh_pass = SHA256::hashString(new_password);
				temp_user->set_password(hesh_pass);
				cout << "������ ��������������." << endl;
				break;

			case 3:
				if (temp_user->get_role() == 1) // ���� ������������ ��� ���� ��������� �� ��������������
				{
					cout << "\n������������ ��� ����� ����� ��������������." << endl;
					break;
				}

				cin.ignore();
				
				// ��������� ���� ������������
				temp_user = new Admin(temp_user->get_login(), temp_user->get_password());
				cout << "\n���� ���������������. ������������ ����� ����� ��������������!" << endl;
				break;

			case 0:
				if (is_same(temp_user))
				{
					cout << "\n��� ���������� ������������ � �������� �������!" << endl;
					cout << "���������� ����� ������������ ������." << endl;
				}
				else
				{
					cout << "\n�������������� ������������ ��������� �������." << endl;
					is_leave = true;
				}
				break;

			default:
				cout << "\n��� ������ ����� ��� ��������������." << endl;
				break;
			}
		} while (!is_leave);

		insert_with_ptr(temp_user);
		rebalanceIndexesPreOrder();
		customer_to_change = nullptr;
		delete customer_to_change;
	}

private:

	// ��������������� ����� ��� ������������ ������ ���� �� ������� - ���������� ����, ���� ���� ���� � ���������� ��������, ����� nullptr
	Node* get_element_by_index(Node* root, const int target_index)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		// ����� � ������� ����������� in-order
		Node* left_result = get_element_by_index(root->left, target_index);

		// ��������, �������� �� �� ������� �������
		if (root->index == target_index)
		{
			return root;
		}

		// ��������, ������ �� ������� � ����� ���������
		if (left_result != nullptr)
		{
			return left_result;
		}

		// ����� � ������ ���������
		return get_element_by_index(root->right, target_index);
	}

	// �������� ������������ ��� ����� 
	Customer* check_customers_rec(Node* root, const Customer& guest)
	{
		if (root == nullptr) {
			return nullptr;
		}
		if ((*(root->data)).get_login() == guest.get_login() && (*(root->data)).get_password() == guest.get_password())
		{
			return root->data;
		}

		// ���������� ��������� ����� � ������ ����������
		Customer* left_result = check_customers_rec(root->left, guest);
		if (left_result != nullptr)
		{
			return left_result; // ���� ����� ������ � ��� ���������
		}

		Customer* right_result = check_customers_rec(root->right, guest);
		return right_result;
	}

	// ����������� ������� �������� ������ ����� ���������
	void insertRecursivePtr(Node* root, const T& value, int index)  //const Customer*& value, Customer*
	{
		if (*(value) < *(root->data))  //Customer	
		{
			if (root->left == nullptr)
			{
				root->left = new Node(value, index);
			}
			else {
				insertRecursivePtr(root->left, value, index);
			}
		}
		else
		{
			if (root->right == nullptr)
			{
				root->right = new Node(value, index);
			}
			else {
				insertRecursivePtr(root->right, value, index);
			}
		}
	}

	// ����� ������ � ������� ����������� ��������� ����� ��� ����������� �� ���������
	void printTreePopulation(Node* root, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				cout << "\n������ �� ����������� ����������� ���������: " << endl;
				cout << "-------------------------------------------------------------------------------------------\n";
				cout << "| " << "�" << " |  " << "��������" << "  |    " << "���������" << "    | "
					<< "�������(���.��.��)" << " | " << "���������(���.���)" << " |  " << "�������" << "   |\n";
				cout << "-------------------------------------------------------------------------------------------\n";
			}
			printTreePopulation(root->left, false);
			cout << "| " << root->index << " ";
			root->data->show();
			printTreePopulation(root->right, false);
		}
	}

	// ������ ������ ��� ��������� ����������
	void Print_Tree_For_Continent_In_Alfavit(Node* root, string your_continent, int& flag, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				cout << "-------------------------------------------------------------------------------------------\n";
				cout << "| " << "�" << " |  " << "��������" << "  |    " << "���������" << "    | "
					<< "�������(���.��.��)" << " | " << "���������(���.���)" << " |  " << "�������" << "   |\n";
				cout << "-------------------------------------------------------------------------------------------\n";
			}
			Print_Tree_For_Continent_In_Alfavit(root->left, your_continent, flag, false);
			if (root->data->get_continent() == your_continent)
			{
				flag = 1;
				cout << "| " << root->index << " ";
				root->data->show();
			}
			Print_Tree_For_Continent_In_Alfavit(root->right, your_continent, flag, false);
		}
	}

	// ����������� ������� �� ��������� ������
	Node* findMin(Node* root)
	{
		while (root->left != nullptr)
		{
			root = root->left;
		}
		return root;
	}

	// ����������� �������� ����������� �������� ������ (�� ��������� �������)
	Node* delele_element(Node* root, Node* key_object)
	{
		if (root == NULL) {
			return root;
		}
		if (root->index == key_object->index)
		{ // ������� �������
			if (root->left == nullptr && root->right == nullptr) // ������� ������, ������� nullptr
			{
				delete root; //� ���������� ��� �������� 
				return nullptr;
			}
			Node* temp; //�������� ������ �� ����� ������ ��������� ����� �������� �������� �����
			if (root->right == NULL) //���� ����� �������
			{
				temp = root->left; //���� ��� ������� �������
				delete root;
				return temp;
			}
			else if (root->left == NULL)
			{
				temp = root->right; //���� ��� ������ �������
				delete root;
				return temp;
			}
			else //� ���������� 2 �������
			{
				Node* min = findMin(root->right);
				root->data = min->data; // ��������� ������� ����� ��������� �� ����������� � ���� ���������
				root->right = delele_element(root->right, min); // �������� ������������ � ������ ��������� 
			}
		}
		else if (*(key_object->data) < *(root->data))
			root->left = delele_element(root->left, key_object);
		else
			root->right = delele_element(root->right, key_object);
		return root;
	}

	// ���������������� ������ �� �������� ������ 

	void Balance_by_name_of_country(Node* root, BinaryTree& New_countryTree)
	{
		if (root) {
			Balance_by_name_of_country(root->left, New_countryTree);

			// ������� ����� �������, ��������� ����� ���� (��������, name)
			// � ��������� ��� � ����� ������
			country* temp_tree_elem = new country(root->data->get_name(), root->data->get_continent(), root->data->get_area(), root->data->get_population(), root->data->get_capital());
			New_countryTree.insert_for_balance(temp_tree_elem);
			temp_tree_elem = nullptr;
			delete temp_tree_elem;

			Balance_by_name_of_country(root->right, New_countryTree);
		}
	}

	void insert_Recursive_for_balance(Node* root, const T& value, int index)
	{
		if (value->get_name() < root->data->get_name())  //if (*(value) < *(root->data))
		{
			if (root->left == nullptr)
			{
				root->left = new Node(value, index);
			}
			else {
				insert_Recursive_for_balance(root->left, value, index);
			}
		}
		else
		{
			if (root->right == nullptr)
			{
				root->right = new Node(value, index);
			}
			else {
				insert_Recursive_for_balance(root->right, value, index);
			}
		}
	}

	// ����� ������ �� ��������� ��������� ������� 
	void Search_By_Area_Range(Node* root, double min_area, double max_area, int& count, Node*& search_arr)
	{
		if (root == nullptr) {
			return; // ������ �����
		}

		// ���������� ���� � ����� ���������
		Search_By_Area_Range(root->left, min_area, max_area, count, search_arr);

		// ���������, ��������� �� ������� ���� � �������� ��������� �������
		if (root->data->get_area() >= min_area && root->data->get_area() <= max_area)
		{
			Node* temp = new Node[count + 1]; //������ �� ���
			for (int i = 0; i < count; ++i) {
				temp[i] = search_arr[i]; // �������� ���������� ���������
			}
			temp[count] = *root; //Node  *Node  // ��������� ������� ��������� �������

			search_arr = temp; // ��� ������� ����� ���������� ������ � ������, ��� ������� temp ��������� search_arr
			temp = nullptr;
			delete[] temp;
			++count;
		}

		// ���������� ���� � ������ ���������
		Search_By_Area_Range(root->right, min_area, max_area, count, search_arr);
	}

	// ���������� ����� ������
	int count_tree_nodes(Node* root)
	{
		if (root == nullptr) {
			return 0;
		}
		return 1 + count_tree_nodes(root->left) + count_tree_nodes(root->right);
	}

	// ��������������� ����� ��� ���������������� �������� � ������� pre-order
	void rebalanceRecPreOrder(Node* root, int& current_index)
	{
		if (root != nullptr)
		{
			rebalanceRecPreOrder(root->left, current_index);
			// ����������� ������ �������� ��������
			root->index = ++current_index;
			rebalanceRecPreOrder(root->right, current_index);
		}
	}

	// ��������������� ����� ��� ���������������� �������� � ������� in-order
	void rebalanceRecInOrder(Node* root, int& current_index)
	{
		if (root != nullptr)
		{
			root->index = current_index++;
			rebalanceRecInOrder(root->left, current_index);
			rebalanceRecInOrder(root->right, current_index);
		}
	}

	void write_to_file_recursive(Node* root, ofstream& file)
	{
		if (root != nullptr)
		{
			file << *(root->data); //*customer => customer
			write_to_file_recursive(root->left, file);
			write_to_file_recursive(root->right, file);
		}
	}

	// ������� ����� ��� ������� ������ ��� ������
	void clear(Node* node)
	{
		if (node != nullptr) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	// ��������� ����� ��� ������������ ����������� �����
	Node* copy_Node(const Node* root_tree_to_copy)
	{
		if (root_tree_to_copy == nullptr)
			return nullptr;

		Node* new_root = new Node(root_tree_to_copy->data, root_tree_to_copy->index);
		new_root->left = copy_Node(root_tree_to_copy->left);
		new_root->right = copy_Node(root_tree_to_copy->right);

		return new_root;
	}

	void print_customers_rec(Node* root, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				cout << "\n������ �������������: " << endl;
				cout << "------------------------------------------------------------------------------------------------------\n";
				cout << "| " << "�" << " |   " << "�����" << "    |                             " << "������" << "                               |     "
					<< "������" << "     | " << "\n";
				cout << "------------------------------------------------------------------------------------------------------\n";
			}
			print_customers_rec(root->left, false);
			cout << "| " << root->index << " ";
			root->data->show();
			print_customers_rec(root->right, false);
		}
	}

	// ����� ��� �������� �� ���������� �������� � ��������
	template <typename T> bool is_same_obj(Node* root, const T& value)
	{
		if (root == nullptr)
		{
			return false; // ������� �� ������
		}


		bool current_node = (*(root->data) == *value);  // ������� ������ � ������� ����

		bool left_tree = is_same_obj(root->left, value);
		bool right_tree = is_same_obj(root->right, value);

		return current_node || left_tree || right_tree;
	}
};