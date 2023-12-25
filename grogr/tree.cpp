#include "country.cpp"

class Customer
{
protected:
	string login;
	string password;
	int role = -1;

public:
	Customer(const string& _login, const string& _password) : login(_login), password(_password) {}
	Customer()
	{
		login = "";
		password = "";
	}
	~Customer() {}

	// геттеры
	string get_login() const
	{
		return login;
	}
	string get_password() const
	{
		return password;
	}
	virtual int get_role() const { return this->role; }

	// сеттеры
	void set_login(const string& login)
	{
		this->login = login;
	}
	void set_password(const string& password)
	{
		this->password = password;
	}
	virtual void set_role(const int& _role) {}

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

	/*virtual string to_string() { return ""; }*/

	virtual void show() {}
};

class User : public Customer
{
//private:
//	const int is_admin = 0;

public:
	//User(const string& _login, const string& _password) : Customer(_login, _password) {}
	User(const string& _login, const string& _password, const int& _role) : Customer(_login, _password) 
	{
		this->role = _role;
	}
	User() : Customer() {}
	~User() {}

	//string get_login() const { return login; }
	//string get_password() const { return password; }

	//void set_login(const string& _login) { login = _login; }
	//void set_password(const string& _password) { password = _password; }

	//string to_string()
	//{
	//	char separator = ';';
	//	string curr_user = this->get_login() + separator + this->get_password() + separator + std::to_string(this->get_role()) + separator + "\n";
	//	return curr_user;
	//}

	void show() override
	{
		string role = "User";
		cout << "| "
			<< std::setw(11) << std::left << this->get_login() << "| "
			<< std::setw(16) << std::left << this->get_password() << "| "
			<< std::setw(15) << std::left << role << "|  \n";
		cout << "-----------------------------------------------------\n";
	}

	//int get_role() const override
	//{
	//	//return is_admin;
	//	return 0;
	//}
	int get_role() const override
	{
		return this->role;
	}

	void set_role(const int& _role) override
	{
		this->role = _role;
	}
};

class Admin : public Customer
{
//private:
//	const int is_admin = 1;
public:
	Admin(const string& _login, const string& _password, const int& _role) : Customer(_login, _password) 
	{
		this->role = _role;
	}
	Admin() : Customer() {}
	~Admin() {}

	/*string get_login() const { return login; }
	string get_password() const { return password; }

	void set_login(const string& _login) { login = _login; }
	void set_password(const string& _password) { password = _password; }*/

	//string to_string()
	//{
	//	char separator = ';';
	//	string curr_user = this->get_login() + separator + this->get_password() + separator + std::to_string(this->get_role()) + separator + "\n";
	//	return curr_user;
	//}

	void show() override
	{
		string role = "Admin";
		cout << "| "
			 << std::setw(11) << std::left << this->get_login() << "| "
			 << std::setw(16) << std::left << this->get_password() << "| "	
			 << std::setw(15) << std::left << role << "|  \n";
		cout << "-----------------------------------------------------\n";
	}

	//int get_role() const override
	//{
	//	//return is_admin;
	//	return 1;
	//}

	int get_role() const override
	{
		return this->role;
	}

	void set_role(const int& _role) override
	{
		this->role = _role;
	}
};

template <typename T>
class BinaryTree {
private:
	struct Node {
		T data; //Customer* data; // country* data
		Node* left;
		Node* right;
		int index; // индекс элемента

		Node(const T& value, int _index) : data(value), left(nullptr), right(nullptr), index(_index) {}
		Node() : data(nullptr), left(nullptr), right(nullptr), index(0) {}
	};

	Node* root;

public:
	BinaryTree() : root(nullptr) { }

	// Конструктор копирования
	BinaryTree(const BinaryTree& tree_to_copy) : root(nullptr) {
		root = copy_Node(tree_to_copy.root);
	}

	// Оператор присваивания
	BinaryTree& operator =(const BinaryTree& tree_to_save) {
		if (this != &tree_to_save) //this - объект в который нужно присвоить, tree_to_save - который нужно присвоить
		{
			this->clear_tree(); // Очищаем текущее дерево
			root = copy_Node(tree_to_save.root); // копирование дерева и возврат ногого root
		}
		return *this; // возврат ссылки на новое дерево
	}

	//Node* get_root() const
	//{
	//	return root;
	//}

	//void insert(const T& value)
	//{
	//	int count = count_tree_nodes(root) + 1;
	//	if (root == nullptr)
	//	{
	//		root = new Node(value, count);
	//	}
	//	else {
	//		insertRecursive(root, value, count);
	//	}
	//}

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
	//void printInOrder()
	//{
	//	printInOrderRec(root);
	//}

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
			cout << "Нет стран для заданного континента. \n";
		}
	}

	// перебалансировка дерева по названию страны вывод стран уже в алфавитним порядке
	void out_continent_countries_alfavit(BinaryTree<country*> countryTree)
	{
		BinaryTree<country*> new_tree = countryTree.Balance_By_Name(); // дерево new_tree в алфавитном порядке по обходу pre-order
		new_tree.Print_Tree_For_Continent(); // тут тоже обход pre-order поэтому в порядке возрастания по алфавиту
	}

	//удаление элемента
	void remove()
	{
		cout << "\nВведите номер для удаления: ";
		int index_to_delete = 0;
		index_to_delete = input_int(index_to_delete);

		Node* obj_to_delete = get_element_by_index(root, index_to_delete); // либо customer, либо country
		
		if (obj_to_delete != nullptr)
		{
			root = delele_element(root, obj_to_delete);
			cout << "Удаление прошло успешно." << endl;
			rebalanceIndexesPreOrder(); // перебалансировка индексов от левого поддерева к правому после удаления элемента
		}
		else
		{
			cout << "Данного элемента нет в дереве." << endl;
		}
	}

	//балансировка дерева по названию страны, возвращает отбалансированное дерево 
	BinaryTree Balance_By_Name()
	{
		BinaryTree<country*> New_country_tree; // по ссылке 
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
			cout << "\nНет стран с заданным диапазоном площади.\n";
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
				search_arr[i].data->show();
			}

			delete[] search_arr; // освобождение памями массива нод
		}
	}

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

	// Работа с пользователями
	Customer* check_customer_to_login_in(Customer* guest)
	{
		Customer* check = check_customers_rec(root, *(guest));
		return check; 
	}

	void write_data_to_file_(ofstream& file)
	{
		write_to_file_recursive(root, file);
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

	void print_customers()
	{
		print_customers_rec(root);
	}

	// Метод для очистки дерева
	void clear_tree() {
		clear(root);
		root = nullptr;
	}

	//// проверка на одинковые логины в дереве
	//bool is_same_logins(const string& login) const
	//{
	//	return is_same_logins_rec(root, login);
	//}

	// вспомогательный метод для проверки на одинаковые элементы в деревьях 
	template <typename T> bool is_same(const T& value)
	{
		return is_same_obj(root, value);
	}

	// метод для редактирования страны по заданному индексу
	void changing_country_info()
	{
		if (root == nullptr) {
			return;
		}

		cout << "\nВведите номер страны для редактирования: ";
		int ind_to_chage = 0;
		ind_to_chage = input_int(ind_to_chage);

		Node* country_to_change = get_element_by_index(root, ind_to_chage);

		country* temp_country = new country(country_to_change->data->get_name(), country_to_change->data->get_continent(), 
		country_to_change->data->get_area(), country_to_change->data->get_population(), country_to_change->data->get_capital());

		root = delele_element(root, country_to_change);
		rebalanceIndexesPreOrder();

		int choice_to_change = 0;
		do
		{
			// вывод меню для редактирования стран
			cout << "\n1. Редактировать название страны\n"
				 << "2. Редактировать континент\n"
				 << "3. Редактировать площадь территории страны\n"
				 << "4. Редактировать численность населения страны\n"
				 << "5. Редактировать столицу страны\n"
				 << "0. Закончить редактирование\n";

			cout << "Выберите действие: ";
			choice_to_change = input_int(choice_to_change);

			string new_name, new_continent, new_capital;
			double new_area = 0; 
			double new_population = 0;

			switch (choice_to_change)
			{
			case 1:
				cin.ignore();
				cout << "\nВведите новое название для страны: ";
				getline(cin, new_name);
				temp_country->set_name(new_name);
				cout << "Название страны отредактировано." << endl;
				break;

			case 2:
				cin.ignore();
				cout << "\nВведите новый континент для страны: ";
				getline(cin, new_continent);
				temp_country->set_continent(new_continent);
				cout << "Континент страны отредактирован." << endl;
				break;

			case 3:
				cin.ignore();
				cout << "\nВведите новую площадь территории страны: ";
				new_area = input_area_population(new_area);
				temp_country->set_area(new_area);
				cout << "Площадь территории страны отредактирована." << endl;
				break;

			case 4:
				cin.ignore();
				cout << "\nВведите новую численность населения: ";
				new_population = input_area_population(new_population);
				temp_country->set_population(new_population);
				cout << "Численность населения страны отредактирована." << endl;
				break;

			case 5:
				cin.ignore();
				cout << "\nВведите новую столицу страны: ";
				getline(cin, new_capital);
				temp_country->set_capital(new_capital);
				cout << "Столица страны отредактирована." << endl;
				break;

			case 0:
				cout << "\nРедактирование завершено." << endl;
				break;

			default:
				cout << "\nНет такого пунта для редактирования." << endl;
				break;
			}
		} while (choice_to_change != 0);

		insert_with_ptr(temp_country);
		rebalanceIndexesPreOrder();
		country_to_change = nullptr;
		delete country_to_change;
	}

	// метод для редактирования пользователя по заданному индексу 
	void changing_customer_info()
	{
		cout << "\nВведите номер пользователя для редактирования: ";
		int ind_to_chage = 0;
		ind_to_chage = input_int(ind_to_chage);

		Node* customer_to_change = get_element_by_index(root, ind_to_chage);

		Customer* temp_customer = nullptr;
		if (customer_to_change->data->get_role() == 0)
		{
			temp_customer = new User(customer_to_change->data->get_login(),
				customer_to_change->data->get_password(), customer_to_change->data->get_role());
		}
		else if (customer_to_change->data->get_role() == 1)
		{
			temp_customer = new Admin(customer_to_change->data->get_login(),
				customer_to_change->data->get_password(), customer_to_change->data->get_role());
		}

		root = delele_element(root, customer_to_change);
		rebalanceIndexesPreOrder();

		int choice_to_change = 0;
		do
		{
			// вывод меню для редактирования пользователей
			cout << "\n1. Редактировать логин\n"
				 << "2. Редактировать пароль\n"
				 << "3. Редактировать роль\n"
				 << "0. Закончить редактирование\n";

			cout << "Выберите действие: ";
			choice_to_change = input_int(choice_to_change);

			string new_login, new_password;
			int new_role = 0;

			switch (choice_to_change)
			{
			case 1:
				cin.ignore();
				cout << "\nВведите новый логин пользователя: ";
				getline(cin, new_login);
				temp_customer->set_login(new_login);
				cout << "Логин отредактирован." << endl;
				break;

			case 2:
				cin.ignore();
				cout << "\nВведите новый пароль пользователя: ";
				getline(cin, new_password);
				temp_customer->set_password(new_password);
				cout << "Пароль отредактирован." << endl;
				break;

			case 3:
				cin.ignore();
				cout << "\nВведите новую роль для пользователя (0 - user, 1 - admin): ";
				new_role = input_int(new_role);

				// проверки на роль, которая уже стоит изначально
				if (new_role == temp_customer->get_role() && new_role == 0)
				{
					cout << "\nЭтот пользователь и не имел прав администратора." << endl;
					break;
				}
				else if (new_role == temp_customer->get_role() && new_role == 1)
				{
					cout << "\nЭтот пользователь уже имеет права администратора." << endl;
					break;
				}

				// изменение роли пользователя
				if (new_role == 0)
				{
					temp_customer = new User(temp_customer->get_login(), temp_customer->get_password(), new_role);
					cout << "Роль отредактирована. Пользователь больше не имеет прав администратора!" << endl;
				}
				else if (new_role == 1)
				{
					temp_customer = new Admin(temp_customer->get_login(), temp_customer->get_password(), new_role);
					cout << "Роль отредактирована. Пользователь имеет права администратора!" << endl;
				}
				break;

			case 0:
				cout << "\nРедактирование завершено." << endl;
				break;

			default:
				cout << "\nНет такого пунта для редактирования." << endl;
				break;
			}
		} while (choice_to_change != 0);

		insert_with_ptr(temp_customer);
		rebalanceIndexesPreOrder();
		customer_to_change = nullptr;
		delete customer_to_change;
	}


private:

	// Вспомогательный метод для рекурсивного поиска узла по индексу - возвращает ноду, если есть нода с переданным индексом, иначе nullptr
	Node* get_element_by_index(Node* root, const int target_index)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		// Обход в порядке возрастания in-order
		Node* left_result = get_element_by_index(root->left, target_index);

		// Проверка, достигли ли мы нужного индекса
		if (root->index == target_index)
		{
			return root;
		}

		// Проверка, найден ли элемент в левом поддереве
		if (left_result != nullptr)
		{
			return left_result;
		}

		// Поиск в правом поддереве
		return get_element_by_index(root->right, target_index);
	}

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

	//void insertRecursive(Node* root, const T& value, int index)
	//{
	//	if (value < root->data) //country 
	//	{
	//		if (root->left == nullptr)
	//		{
	//			root->left = new Node(value, index);
	//		}
	//		else {
	//			insertRecursive(root->left, value, index);
	//		}
	//	}
	//	else
	//	{
	//		if (root->right == nullptr)
	//		{
	//			root->right = new Node(value, index);
	//		}
	//		else {
	//			insertRecursive(root->right, value, index);
	//		}
	//	}
	//}

	// рекурсивная вставка элемента дерева через указатель
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
	//void printInOrderRec(Node* root)
	//{
	//	if (root != nullptr)
	//	{
	//		cout << root->index;
	//		cout << ". ";
	//		(root->data).show(); // -> для укащателя , для страны будет.
	//		printInOrderRec(root->left); // по другому сразу левое поддерево потом вывод а потом правое поддерево
	//		printInOrderRec(root->right);
	//	}
	//}

	// вывод дерева в порядке возрастания населений стран при балансороке по населению
	void printTreePopulation(Node* root, bool is_root = true)
	{
		if (root != nullptr)
		{
			if (is_root)
			{
				cout << "\nСтраны по возрастанию численности населения: " << endl;
				cout << "-------------------------------------------------------------------------------------------\n";
				cout << "| " << "№" << " |  " << "Название" << "  |    " << "Континент" << "    | "
					<< "Площадь(млн.кв.км)" << " | " << "Население(млн.чел)" << " |  " << "Столица" << "   |\n";
				cout << "-------------------------------------------------------------------------------------------\n";
			}
			printTreePopulation(root->left, false);
			cout << "| " << root->index << " ";
			root->data->show();
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
			if (root->data->get_continent() == your_continent)
			{
				flag = 1;
				cout << "| " << root->index << " ";
				root->data->show();
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

	// рекурсивное удаление переданного элемента дерева (по заданному индексу)
	Node* delele_element(Node* root, Node* key_object)
	{
		if (root == NULL) {
			return root;
		}
		if (root->index == key_object->index)
		{ // удаляем элемент
			if (root->left == nullptr && root->right == nullptr) // удалили корень, вернули nullptr
			{
				delete root; //у удаляемого нет потомков 
				return nullptr;
			}
			Node* temp; //хранения ссылки на новый корень поддерева после удаления текущего корня
			if (root->right == NULL) //один левый потомок
			{
				temp = root->left; //если нет правого потомка
				delete root;
				return temp;
			}
			else if (root->left == NULL)
			{
				temp = root->right; //если нет левого потомка
				delete root;
				return temp;
			}
			else //у удаляемого 2 потомка
			{
				Node* min = findMin(root->right);
				//root->data.set_name(min->data.get_name());
				//root->data.set_continent(min->data.get_continent());
				//root->data.set_area(min->data.get_area());
				//root->data.set_population(min->data.get_population());
				//root->data.set_capital(min->data.get_capital());
				root->data = min->data; // root->data - либо customer, либо country  min->data - либо customer, либо country
				root->right = delele_element(root->right, min);
			}
		}
		else if (*(key_object->data) < *(root->data))
			root->left = delele_element(root->left, key_object);
		else
			root->right = delele_element(root->right, key_object);
		return root;
	}

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

		country* temp_county = new country(your_name, your_continent, your_area, your_population, your_capital);

		if (is_same(temp_county))
		{
			cout << "\nТакая страна уже существует." << endl;
		}
		else
		{
			insert_with_ptr(temp_county);
		}

		temp_county = nullptr;
		delete temp_county;
	}

	
	void add_customer_rec(Node*& root)
	{
		cout << "\nДобавить пользователя (1) или администратора (2): ";
		int choice = 0;
		choice = input_int(choice);
		string your_login, your_pass;
		Customer* new_customer = nullptr;
		if (choice == 1)
		{
			cin.ignore();
			cout << "\nВведите логин пользователя: " << endl;
			getline(cin, your_login);

			cout << "Введите пароль пользователя: " << endl;
			getline(cin, your_pass);

			new_customer = new User(your_login, your_pass, 0);
		}
		else if (choice == 2)
		{
			cin.ignore();
			cout << "\nВведите логин администратора: " << endl;
			getline(cin, your_login);

			cout << "Введите пароль администратора: " << endl;
			getline(cin, your_pass);

			new_customer = new Admin(your_login, your_pass, 1);
		}

		if (is_same(new_customer))
		{
			cout << "\nПользователь с логином " << your_login << " уже существует." << endl;
		}
		else
		{
			insert_with_ptr(new_customer);
		}
		new_customer = nullptr;
		delete new_customer;
	}

	// ПЕРЕБАЛАНСИРОВКА ДЕРЕВА ПО НАЗВАНИЮ СТРАНЫ 

	void Balance_by_name_of_country(Node* root, BinaryTree& New_countryTree)
	{
		if (root) {
			Balance_by_name_of_country(root->left, New_countryTree);

			// Создаем новый элемент, используя новый ключ (например, name)
			// и вставляем его в новое дерево
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

	// поиск страны по заданному диапазону площади 
	void Search_By_Area_Range(Node* root, double min_area, double max_area, int& count, Node*& search_arr)
	{
		if (root == nullptr) {
			return; // дерево пусто
		}

		// рекурсивно ищем в левом поддереве
		Search_By_Area_Range(root->left, min_area, max_area, count, search_arr);

		// Проверяем, находится ли текущий узел в заданном диапазоне площади
		if (root->data->get_area() >= min_area && root->data->get_area() <= max_area)
		{
			Node* temp = new Node[count + 1]; //массив из нод
			for (int i = 0; i < count; ++i) {
				temp[i] = search_arr[i];
			}
			temp[count] = *root; //Node     *Node

			search_arr = temp; // оба массива имеют одинаковые адреса в памяти, при очистке temp очистится search_arr
			temp = nullptr;
			delete[] temp;
			++count;
		}

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

	void write_to_file_recursive(Node* root, ofstream& file)
	{
		if (root != nullptr)
		{
			// Записываем данные о пользователе в файл
			/*file << (*(root->data)).get_login() << ";" << (*(root->data)).get_password() << ";"
				<< (*(root->data)).get_role() << ";\n";*/
			file << *(root->data); //*customer => customer
			write_to_file_recursive(root->left, file);
			write_to_file_recursive(root->right, file);
		}
	}

	// прайват метод для очистки памяти под дерево
	void clear(Node* node) 
	{
		if (node != nullptr) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	// приватный метод для рекурсивного копирования узлов
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
				cout << "\nСписок пользователей: " << endl;
				cout << "-----------------------------------------------------\n";
				cout << "| " << "№" << " |   " << "Логин" << "    |     " << "Пароль" << "      |     "
					<< "Статус" << "     | " << "\n";
				cout << "-----------------------------------------------------\n";
			}
			print_customers_rec(root->left, false);
			cout << "| " << root->index << " ";
			root->data->show();
			print_customers_rec(root->right, false);
		}
	}

	// метод для проверки на одинаковые элементы в деревьях
	template <typename T> bool is_same_obj(Node* root, const T& value)
	{
		if (root == nullptr)
		{
			return false; // элемент не найден
		}


		bool current_node = (*(root->data) == *value);  // элемент найден в текущем узле

		bool left_tree = is_same_obj(root->left, value);
		bool right_tree = is_same_obj(root->right, value);

		return current_node || left_tree || right_tree;
	}
};