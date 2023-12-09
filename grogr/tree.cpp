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
		cout << "Базовый класс" << endl;
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
		cout << "Вы пользователь" << endl;
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
		int index; // индекс элемента

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

	// как удобно
	void printInOrder()
	{
		printInOrderRec(root);
	}

	void printTreePopulationUp()
	{
		printTreePopulation(root);
	}

	// обработчик метода для вывода стран для заданного континент, если таких нет выводиться сообщение
	void Print_Tree_For_Continent()
	{
		cout << "\nВведите континент, страны которого нужно вывести: " << endl;
		cin.ignore();
		string your_continent;
		getline(cin, your_continent);
		int is_continent = 0;
		cout << endl;
		cout << "Страны континента " << your_continent << " в алфавитном порядке: " << endl;
		Print_Tree_For_Continent_In_Alfavit(root, your_continent, is_continent);
		if (!is_continent)
		{
			cout << "Нет такого континента. \n\n";
		}
	}

	// перебалансировка дерева по названию страны вывод стран уже в алфавитним порядке
	void out_continent_countries_alfavit(BinaryTree<country> countryTree)
	{
		BinaryTree<country> new_tree = countryTree.Balance_By_Name();
		new_tree.Print_Tree_For_Continent();
	}

	//удаление элемента
	void remove()
	{
		cout << "Введите население страны, которую нужно удалить: " << endl;
		double your_population = 0;
		int flag = 0;
		your_population = input_double(your_population);
		root = delele_element(root, your_population, flag);
		if (flag == 1)
		{
			cout << "\nУдалена страна с населением: " << your_population << endl;
			cout << std::endl;
		}
		else
		{
			cout << "Данного элемента нет в дереве\n" << endl;
		}
	}

	//балансировка дерева по названию страны, возвращает отбалансированное дерево 
	BinaryTree Balance_By_Name()
	{
		BinaryTree<country> New_country_tree; // по ссылке 
		Balance_by_name_of_country(root, New_country_tree);
		return New_country_tree;
	}

	// поиск по площади из заданного диапазона
	void search()
	{
		cout << "\nВведите минимальный порог площади: ";
		double min_area = 0;
		min_area = input_area_population(min_area);
		cout << "Введите максимальный порог площади: ";
		double max_area = 0;
		max_area = input_area_population(max_area);
		int count = 0;
		Node* search_arr = nullptr; // массив из элементов дерева
		Search_By_Area_Range(root, min_area, max_area, count, search_arr);
		if (search_arr == nullptr)
		{
			cout << "\nНет стран с заданным диапазоном площади.";
		}
		else
		{
			cout << "\nСтраны с площадью в диапазоне от " << min_area << " до " << max_area << ": " << endl;
			cout << "-------------------------------------------------------------------------------------------\n";
			cout << "| " << "№" << " |  " << "Название" << "  |    " << "Континент" << "    | "
				<< "Площадь(млн.кв.км)" << " | " << "Население(млн.чел)" << " |  " << "Столица" << "   |\n";
			cout << "-------------------------------------------------------------------------------------------\n";
			for (int i = 0; i < count; i++)
			{
				cout << "| " << search_arr[i].index << " ";
				search_arr[i].data.show();
			}

			delete[] search_arr; // освобождение памями массива нод
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
				std::cout << "Ошибка! Некорректный ввод.\n";
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
				std::cout << "Ошибка! Некорректный ввод.\n";
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
				std::cout << "Ошибка! Некорректный ввод.\n";
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
				std::cout << "Ошибка! Некорректный ввод.\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << std::endl;
			}
		}
		return value;
	}

	//Работа с пользователями
	Customer* check_customer_to_login_in(Customer* guest)
	{
		Customer* check = check_customers_rec(root, *(guest));
		return check;
	}

	void write_data_to_file_(ofstream& file)
	{
		write_customers_to_file_recursive(root, file);
	}

	// паблик метод для перебалансировки индексов в порядке pre-order (с левого поддерева вверх и потом правое поддерево)
	void rebalanceIndexesPreOrder() {
		int current_index = 0;
		rebalanceRecPreOrder(root, current_index);
	}

	// паблик метод для перебалансировки индексов в порядке in-order (сверху вниз левое поддерево потом правое поддерево)
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

	// проверка пользователя для входа 
	Customer* check_customers_rec(Node* root, const Customer& guest)
	{
		if (root == nullptr) {
			return nullptr;
		}
		if ((*(root->data)).get_login() == guest.get_login() && (*(root->data)).get_password() == guest.get_password())
		{
			return root->data;
		}

		// Рекурсивно проверяем левое и правое поддеревья
		Customer* left_result = check_customers_rec(root->left, guest);
		if (left_result != nullptr)
		{
			return left_result; // если польз найден в лев поддереве
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

	// вставка элемента дерева через указатель
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

	//печать дерева как удобно смотреть 
	void printInOrderRec(Node* root)
	{
		if (root != nullptr)
		{
			cout << root->index;
			cout << ". ";
			(root->data).show(); // -> для укащателя , для страны будет.
			printInOrderRec(root->left); // по другому сразу левое поддерево потом вывод а потом правое поддерево
			printInOrderRec(root->right);
		}
	}

	// вывод дерева в порядке возрастания населений стран при балансороке по населению
	void printTreePopulation(Node* root, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				rebalanceIndexesPreOrder();
				cout << "\nСтраны по возрастанию численности населения: " << endl;
				cout << "-------------------------------------------------------------------------------------------\n";
				cout << "| " << "№" << " |  " << "Название" << "  |    " << "Континент" << "    | "
					<< "Площадь(млн.кв.км)" << " | " << "Население(млн.чел)" << " |  " << "Столица" << "   |\n";
				cout << "-------------------------------------------------------------------------------------------\n";
			}
			printTreePopulation(root->left, false);
			cout << "| " << root->index << " ";
			root->data.show();
			printTreePopulation(root->right, false);
		}
	}

	// печать дерева для задданого континента
	void Print_Tree_For_Continent_In_Alfavit(Node* root, string your_continent, int& flag, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				cout << "-------------------------------------------------------------------------------------------\n";
				cout << "| " << "№" << " |  " << "Название" << "  |    " << "Континент" << "    | "
					<< "Площадь(млн.кв.км)" << " | " << "Население(млн.чел)" << " |  " << "Столица" << "   |\n";
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

	// минимальный элемент по населению страны
	Node* findMin(Node* root)
	{
		while (root->left != nullptr)
		{
			root = root->left;
		}
		return root;
	}

	// удаление элменета дерева по заданному населению страны
	Node* delele_element(Node* root, double key_population, int& flag)
	{
		if (root == NULL) {
			return root;
		}
		if (root->data.get_population() == key_population)
		{ // удаляем элемент
			if (root->left == nullptr && root->right == nullptr) // удалили корень, вернули nullptr
			{
				delete root; //у удаляемого нет потомков 
				flag = 1;
				return nullptr;
			}
			Node* temp; //хранения ссылки на новый корень поддерева после удаления текущего корня
			if (root->right == NULL) //один левый потомок
			{
				temp = root->left; //если нет правого потомка
				delete root;
				flag = 1;
				return temp;
			}
			else if (root->left == NULL)
			{
				temp = root->right; //если нет левого потомка
				delete root;
				flag = 1;
				return temp;
			}
			else //у удаляемого 2 потомка
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

	//// формирование дерева с клавиатуры 
	//void create_tree_of_countries(Node*& root)
	//{
	//	cout << "Введите количество стран: " << endl;
	//	int size = 0;
	//	size = input_countries(size);
	//	cin.ignore(); // пропуск \n после считывания числа 
	//	for (int i = 0; i < size; i++)
	//	{
	//		cout << "\nВведите название страны: " << endl;
	//		string your_name;
	//		getline(cin, your_name);

	//		cout << "Введите континент страны: " << endl;
	//		string your_continent;
	//		getline(cin, your_continent);

	//		cout << "Введите площадь страны: " << endl;
	//		double your_area = 0;
	//		your_area = input_area_population(your_area);

	//		cout << "Введите количество населения страны: " << endl;
	//		double your_population = 0;
	//		your_population = input_area_population(your_population);

	//		cin.ignore();
	//		cout << "Введите название столицы страны: " << endl;
	//		string your_capital;
	//		getline(cin, your_capital);

	//		T temp(your_name, your_continent, your_area, your_population, your_capital);

	//		cout << endl;
	//		insert(temp);
	//	}
	//}

	// добавление страны в дерево стран 
	void add_country_rec(Node*& root)
	{
		cin.ignore();
		cout << "\nВведите название страны: " << endl;
		string your_name;
		getline(cin, your_name);

		cout << "Введите континент страны: " << endl;
		string your_continent;
		getline(cin, your_continent);

		cout << "Введите площадь страны: " << endl;
		double your_area = 0;
		your_area = input_area_population(your_area);

		cout << "Введите количество населения страны: " << endl;
		double your_population = 0;
		your_population = input_area_population(your_population);

		cin.ignore();
		cout << "Введите название столицы страны: " << endl;
		string your_capital;
		getline(cin, your_capital);

		T temp(your_name, your_continent, your_area, your_population, your_capital);

		insert(temp);
	}

	
	void add_customer_rec(Node*& root)
	{
		// if () главный админ и добавление админа if ()
		cin.ignore();
		cout << "\nВведите логин пользователя: " << endl;
		string your_login;
		getline(cin, your_login);

		cout << "Введите пароль пользователя: " << endl;
		string your_pass;
		getline(cin, your_pass);

		//Customer* guest;
		T guest = new User(your_login, your_pass);

		insert_with_ptr(guest);
	}

	// ПЕРЕБАЛАНСИРОВКА ДЕРЕВА ПО НАЗВАНИЮ СТРАНЫ 

	void Balance_by_name_of_country(Node* root, BinaryTree& New_countryTree)
	{
		if (root) {
			Balance_by_name_of_country(root->left, New_countryTree);

			// Создаем новый элемент, используя новый ключ (например, name)
			// и вставляем его в новое дерево
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

	// поиск страны по заданному диапазону площади 
	void Search_By_Area_Range(Node* root, double min_area, double max_area, int& count, Node*& search_arr)
	{
		if (root == nullptr) {
			return; // дерево пусто
		}

		// Проверяем, находится ли текущий узел в заданном диапазоне площади
		if (root->data.get_area() >= min_area && root->data.get_area() <= max_area)
		{
			Node* temp = new Node[count + 1]; //массив из ноды
			for (int i = 0; i < count; ++i) {
				temp[i] = search_arr[i];
			}
			temp[count] = *root; //Node     *Node

			search_arr = temp; // оба массива имеют одинаковые адреса в памяти, при очистке temp очистится search_arr
			temp = nullptr;
			delete[] temp;
			++count;
		}

		// рекурсивно ищем в левом поддереве
		Search_By_Area_Range(root->left, min_area, max_area, count, search_arr);
		// рекурсивно ищем в правом поддереве
		Search_By_Area_Range(root->right, min_area, max_area, count, search_arr);
	}

	// количество узлов дерева
	int count_tree_nodes(Node* root)
	{
		if (root == nullptr) {
			return 0;
		}
		return 1 + count_tree_nodes(root->left) + count_tree_nodes(root->right);
	}

	// Вспомогательный метод для перебалансировки индексов в порядке pre-order
	void rebalanceRecPreOrder(Node* root, int& current_index) 
	{
		if (root != nullptr) 
		{
			rebalanceRecPreOrder(root->left, current_index);
			// присваиваем индекс текущему элементу
			root->index = ++current_index;
			rebalanceRecPreOrder(root->right, current_index);
		}
	}

	// Вспомогательный метод для перебалансировки индексов в порядке in-order
	void rebalanceRecInOrder(Node* root, int& current_index) 
	{
		if (root != nullptr) 
		{
			root->index = current_index++;
			rebalanceRecInOrder(root->left, current_index);
			rebalanceRecInOrder(root->right, current_index);
		}
	}

	// рекурсивный обход дерева и запись пользователей в файл
	//void write_customers_to_file_recursive(Node* root, ofstream& file)
	//{
	//	if (root != nullptr)
	//	{
	//		// Записываем данные о пользователе в файл
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
			// Записываем данные о пользователе в файл
			/*file << (*(root->data)).get_login() << ";" << (*(root->data)).get_password() << ";"
				<< (*(root->data)).get_role() << ";\n";*/
			file << *(root->data); //*customer => customer
			write_customers_to_file_recursive(root->left, file);
			write_customers_to_file_recursive(root->right, file);
		}
	}
};

