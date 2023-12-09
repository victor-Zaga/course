#include "country.cpp"

class Customer
{
protected:
	string login;
	string password;

public:
	Customer(const string& _login, const string& _password) : login(_login), password(_password) {}
	Customer()
	{
		login = "";
		password = "";
	}
	~Customer() {}

	string get_login() const
	{
		return login;
	}
	string get_password() const
	{
		return password;
	}

	bool operator <(const Customer& customer) const
	{
		return login < customer.login;
	}

	bool operator >(const Customer& customer) const
	{
		return login > customer.login;
	}

	bool operator ==(const Customer& customer) const
	{
		return login == customer.login;
	}

	//virtual string to_string() { return ""; }
	virtual int get_role() const
	{
		return -1;
	}

	virtual void show()
	{
		cout << "������� �����" << endl;
		cout << login << endl;
		cout << password;
	}
};

class User : public Customer
{
private:
	const int is_admin = 0;

public:
	User(const string& _login, const string& _password) : Customer(_login, _password)
	{
		//login = _login;
		//password = _password;
	}
	User() : Customer() {}
	~User() {}

	string get_login() const { return login; }
	string get_password() const { return password; }

	void set_login(const string& _login) { login = _login; }
	void set_password(const string& _password) { password = _password; }

	//string to_string() override
	//{
	//	char separator = ';';
	//	string curr_user = this->get_login() + separator + this->get_password() + separator;
	//	return curr_user;
	//}

	void show() override
	{
		cout << "�� ������������" << endl;
		cout << login << endl;
		cout << password << endl;
		cout << is_admin << endl;
	}

	int get_role() const override
	{
		return is_admin;
	}
};

template <typename T>
class BinaryTree {
private:
	struct Node {
		T data; //Customer* data;
		Node* left;
		Node* right;
		int index; // ������ ��������

		Node(const T& value, int _index) : data(value), left(nullptr), right(nullptr), index(_index) {}
		Node() : left(nullptr), right(nullptr), index(0) {}
	};

	Node* root;

public:
	BinaryTree() : root(nullptr) { }

	Node* get_root() const
	{
		return root;
	}

	void insert(const T& value)
	{
		int count = count_tree_nodes(root) + 1;
		if (root == nullptr)
		{
			root = new Node(value, count);
		}
		else {
			insertRecursive(root, value, count);
		}
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

	// ��� ������
	void printInOrder()
	{
		printInOrderRec(root);
	}

	void printTreePopulationUp()
	{
		printTreePopulation(root);
	}

	// ���������� ������ ��� ������ ����� ��� ��������� ���������, ���� ����� ��� ���������� ���������
	void Print_Tree_For_Continent()
	{
		cout << "\n������� ���������, ������ �������� ����� �������: " << endl;
		cin.ignore();
		string your_continent;
		getline(cin, your_continent);
		int is_continent = 0;
		cout << endl;
		cout << "������ ���������� " << your_continent << " � ���������� �������: " << endl;
		Print_Tree_For_Continent_In_Alfavit(root, your_continent, is_continent);
		if (!is_continent)
		{
			cout << "��� ������ ����������. \n\n";
		}
	}

	// ���������������� ������ �� �������� ������ ����� ����� ��� � ���������� �������
	void out_continent_countries_alfavit(BinaryTree<country> countryTree)
	{
		BinaryTree<country> new_tree = countryTree.Balance_By_Name();
		new_tree.Print_Tree_For_Continent();
	}

	//�������� ��������
	void remove()
	{
		cout << "������� ��������� ������, ������� ����� �������: " << endl;
		double your_population = 0;
		int flag = 0;
		your_population = input_double(your_population);
		root = delele_element(root, your_population, flag);
		if (flag == 1)
		{
			cout << "\n������� ������ � ����������: " << your_population << endl;
			cout << std::endl;
		}
		else
		{
			cout << "������� �������� ��� � ������\n" << endl;
		}
	}

	//������������ ������ �� �������� ������, ���������� ����������������� ������ 
	BinaryTree Balance_By_Name()
	{
		BinaryTree<country> New_country_tree; // �� ������ 
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
			cout << "\n��� ����� � �������� ���������� �������.";
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
				search_arr[i].data.show();
			}

			delete[] search_arr; // ������������ ������ ������� ���
		}
	}

	//void create_country_tree()
	//{
	//	create_tree_of_countries(root);
	//}

	double input_double(double value)
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
	double input_area_population(double value)
	{
		while (true)
		{
			if ((std::cin >> value) && value >= 0)
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
	int input_int(int value)
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
	int input_countries(int value)
	{
		while (true)
		{
			if ((std::cin >> value) && value > 0)
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

	//������ � ��������������
	Customer* check_customer_to_login_in(Customer* guest)
	{
		Customer* check = check_customers_rec(root, *(guest));
		return check;
	}

	void write_data_to_file_(ofstream& file)
	{
		write_customers_to_file_recursive(root, file);
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

	void add_country_()
	{
		add_country_rec(root);
	}

	void add_customer_()
	{
		add_customer_rec(root);
	}

private:

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

	void insertRecursive(Node* root, const T& value, int index)
	{
		if (value < root->data) //country 
		{
			if (root->left == nullptr)
			{
				root->left = new Node(value, index);
			}
			else {
				insertRecursive(root->left, value, index);
			}
		}
		else
		{
			if (root->right == nullptr)
			{
				root->right = new Node(value, index);
			}
			else {
				insertRecursive(root->right, value, index);
			}
		}
	}

	// ������� �������� ������ ����� ���������
	void insertRecursivePtr(Node* root, const T& value, int index)  //const Customer*& value, Customer*
	{
		if (*(value) < *(root->data))  //Customer	
		{
			if (root->left == nullptr)
			{
				root->left = new Node(value, index);
			}
			else {
				insertRecursivePtr(root->left, value,index);
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

	//������ ������ ��� ������ �������� 
	void printInOrderRec(Node* root)
	{
		if (root != nullptr)
		{
			cout << root->index;
			cout << ". ";
			(root->data).show(); // -> ��� ��������� , ��� ������ �����.
			printInOrderRec(root->left); // �� ������� ����� ����� ��������� ����� ����� � ����� ������ ���������
			printInOrderRec(root->right);
		}
	}

	// ����� ������ � ������� ����������� ��������� ����� ��� ����������� �� ���������
	void printTreePopulation(Node* root, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				rebalanceIndexesPreOrder();
				cout << "\n������ �� ����������� ����������� ���������: " << endl;
				cout << "-------------------------------------------------------------------------------------------\n";
				cout << "| " << "�" << " |  " << "��������" << "  |    " << "���������" << "    | "
					<< "�������(���.��.��)" << " | " << "���������(���.���)" << " |  " << "�������" << "   |\n";
				cout << "-------------------------------------------------------------------------------------------\n";
			}
			printTreePopulation(root->left, false);
			cout << "| " << root->index << " ";
			root->data.show();
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
			if (root->data.get_continent() == your_continent)
			{
				flag = 1;
				cout << "| " << root->index << " ";
				root->data.show();
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

	// �������� �������� ������ �� ��������� ��������� ������
	Node* delele_element(Node* root, double key_population, int& flag)
	{
		if (root == NULL) {
			return root;
		}
		if (root->data.get_population() == key_population)
		{ // ������� �������
			if (root->left == nullptr && root->right == nullptr) // ������� ������, ������� nullptr
			{
				delete root; //� ���������� ��� �������� 
				flag = 1;
				return nullptr;
			}
			Node* temp; //�������� ������ �� ����� ������ ��������� ����� �������� �������� �����
			if (root->right == NULL) //���� ����� �������
			{
				temp = root->left; //���� ��� ������� �������
				delete root;
				flag = 1;
				return temp;
			}
			else if (root->left == NULL)
			{
				temp = root->right; //���� ��� ������ �������
				delete root;
				flag = 1;
				return temp;
			}
			else //� ���������� 2 �������
			{
				Node* min = findMin(root->right);
				root->data.set_name(min->data.get_name());
				root->data.set_continent(min->data.get_continent());
				root->data.set_area(min->data.get_area());
				root->data.set_population(min->data.get_population());
				root->data.set_capital(min->data.get_capital());
				root->right = delele_element(root->right, min->data.get_population(), flag);
			}
		}
		else if (key_population < root->data.get_population())
			root->left = delele_element(root->left, key_population, flag);
		else
			root->right = delele_element(root->right, key_population, flag);
		return root;
	}

	//// ������������ ������ � ���������� 
	//void create_tree_of_countries(Node*& root)
	//{
	//	cout << "������� ���������� �����: " << endl;
	//	int size = 0;
	//	size = input_countries(size);
	//	cin.ignore(); // ������� \n ����� ���������� ����� 
	//	for (int i = 0; i < size; i++)
	//	{
	//		cout << "\n������� �������� ������: " << endl;
	//		string your_name;
	//		getline(cin, your_name);

	//		cout << "������� ��������� ������: " << endl;
	//		string your_continent;
	//		getline(cin, your_continent);

	//		cout << "������� ������� ������: " << endl;
	//		double your_area = 0;
	//		your_area = input_area_population(your_area);

	//		cout << "������� ���������� ��������� ������: " << endl;
	//		double your_population = 0;
	//		your_population = input_area_population(your_population);

	//		cin.ignore();
	//		cout << "������� �������� ������� ������: " << endl;
	//		string your_capital;
	//		getline(cin, your_capital);

	//		T temp(your_name, your_continent, your_area, your_population, your_capital);

	//		cout << endl;
	//		insert(temp);
	//	}
	//}

	// ���������� ������ � ������ ����� 
	void add_country_rec(Node*& root)
	{
		cin.ignore();
		cout << "\n������� �������� ������: " << endl;
		string your_name;
		getline(cin, your_name);

		cout << "������� ��������� ������: " << endl;
		string your_continent;
		getline(cin, your_continent);

		cout << "������� ������� ������: " << endl;
		double your_area = 0;
		your_area = input_area_population(your_area);

		cout << "������� ���������� ��������� ������: " << endl;
		double your_population = 0;
		your_population = input_area_population(your_population);

		cin.ignore();
		cout << "������� �������� ������� ������: " << endl;
		string your_capital;
		getline(cin, your_capital);

		T temp(your_name, your_continent, your_area, your_population, your_capital);

		insert(temp);
	}

	
	void add_customer_rec(Node*& root)
	{
		// if () ������� ����� � ���������� ������ if ()
		cin.ignore();
		cout << "\n������� ����� ������������: " << endl;
		string your_login;
		getline(cin, your_login);

		cout << "������� ������ ������������: " << endl;
		string your_pass;
		getline(cin, your_pass);

		//Customer* guest;
		T guest = new User(your_login, your_pass);

		insert_with_ptr(guest);
	}

	// ���������������� ������ �� �������� ������ 

	void Balance_by_name_of_country(Node* root, BinaryTree& New_countryTree)
	{
		if (root) {
			Balance_by_name_of_country(root->left, New_countryTree);

			// ������� ����� �������, ��������� ����� ���� (��������, name)
			// � ��������� ��� � ����� ������
			country temp_tree_elem(root->data.get_name(), root->data.get_continent(), root->data.get_area(), root->data.get_population(), root->data.get_capital());
			New_countryTree.insert_for_balance(temp_tree_elem);

			Balance_by_name_of_country(root->right, New_countryTree);
		}
	}

	void insert_Recursive_for_balance(Node* root, const T& value, int index)
	{
		if (value.get_name() < root->data.get_name())
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

		// ���������, ��������� �� ������� ���� � �������� ��������� �������
		if (root->data.get_area() >= min_area && root->data.get_area() <= max_area)
		{
			Node* temp = new Node[count + 1]; //������ �� ����
			for (int i = 0; i < count; ++i) {
				temp[i] = search_arr[i];
			}
			temp[count] = *root; //Node     *Node

			search_arr = temp; // ��� ������� ����� ���������� ������ � ������, ��� ������� temp ��������� search_arr
			temp = nullptr;
			delete[] temp;
			++count;
		}

		// ���������� ���� � ����� ���������
		Search_By_Area_Range(root->left, min_area, max_area, count, search_arr);
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

	// ����������� ����� ������ � ������ ������������� � ����
	//void write_customers_to_file_recursive(Node* root, ofstream& file)
	//{
	//	if (root != nullptr)
	//	{
	//		// ���������� ������ � ������������ � ����
	//		file << (*(root->data)).get_login() << ";" << (*(root->data)).get_password() << ";"
	//			<< (*(root->data)).get_role() << ";\n";
	//		write_customers_to_file_recursive(root->left, file);
	//		write_customers_to_file_recursive(root->right, file);
	//	}
	//}

	void write_customers_to_file_recursive(Node* root, ofstream& file)
	{
		if (root != nullptr)
		{
			// ���������� ������ � ������������ � ����
			/*file << (*(root->data)).get_login() << ";" << (*(root->data)).get_password() << ";"
				<< (*(root->data)).get_role() << ";\n";*/
			file << *(root->data); //*customer => customer
			write_customers_to_file_recursive(root->left, file);
			write_customers_to_file_recursive(root->right, file);
		}
	}
};

