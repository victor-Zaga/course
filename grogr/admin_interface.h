#pragma once
#include "tree.h"
#include "user_interface.h"

class Admin_interface : public User_interface
{
private:
	BinaryTree<Customer*> customer_tree;

public:
	Admin_interface(BinaryTree<country*> _country_tree, BinaryTree<Customer*> _customer_tree, file_database _database) : User_interface(_country_tree, _database)
	{
		customer_tree = _customer_tree;
	}
	~Admin_interface() { customer_tree.clear_tree(); } // тк customer_tree - коопия дерева

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
		int guest_index = 0;
		int choice = 0;
		while (true)
		{
			show_menu(); // 1 2 3 
			cout << "4. Вставка новой страны." << endl;
			cout << "5. Вставка нового пользователя. " << endl;
			cout << "6. Вывод пользователей." << endl;
			cout << "7. Удаление заданной страны." << endl;
			cout << "8. Удаление заданного пользователя." << endl;
			cout << "9. Редактирование заданной страны." << endl;
			cout << "10. Редактирование заданного пользователя." << endl;
			cout << "11. Сохранение изменений в файл." << endl;
			cout << "12. Отмена изменений." << endl;
			cout << "0. Выход." << endl;
			cout << "Сделайте выбор: ";
			choice = input_int(choice);
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
				country_tree_to_view = database.read_countries_from_file();
				country_tree_to_view.search();
				break;
				// перенести первые 3 пункта
			case 4:
				country_tree.add_country();
				is_becup = false;
				break;

			case 5:
				customer_tree.add_user();
				is_becup = false;
				break;

			case 6:
				customer_tree_to_view = database.read_customers_from_file();
				customer_tree_to_view.print_customers();
				break;

			case 7:
				country_tree.remove_country();
				break;

			case 8:
				customer_tree.remove_user();
				break;

			case 9:
				country_tree.changing_country_info();
				break;

			case 10:
				customer_tree.changing_user_info();
				break;

			case 11:
				// сохренение изменений в файл
				database.write_tree_to_file(country_tree);
				database.write_tree_to_file(customer_tree);
				// сохранение изменений между сохранениями
				if (is_save)
				{
					original_country_tree = last_saved_country_tree;
					original_customer_tree = last_saved_customer_tree;
				}
				last_saved_country_tree = country_tree; // запоминаем апдейт деревья для бекапа
				last_saved_customer_tree = customer_tree;
				cout << "\nИзмененния были записаны в файл." << endl;
				is_save = true;
				is_becup = false;
				break;

			case 12:
				// отмена изменений
				if (is_save && !is_becup)
				{ // на 2 раза подряд
					country_tree = original_country_tree;
					customer_tree = original_customer_tree;
					database.write_tree_to_file(country_tree);
					database.write_tree_to_file(customer_tree);
					cout << "\nИзменения были отменены." << endl;
					last_saved_country_tree = country_tree; // уже не нужно запоминать измененные деревья, т.к. отменили изменения
					last_saved_customer_tree = customer_tree;
					is_becup = true;
				}
				else
				{
					cout << "\nИзменения еще не были внесены." << endl;
				}
				break;

			case 0:
				original_country_tree.clear_tree();
				original_customer_tree.clear_tree();

				last_saved_country_tree.clear_tree();
				last_saved_customer_tree.clear_tree();

				country_tree_to_view.clear_tree();
				customer_tree_to_view.clear_tree();
				cout << "\nПока" << endl;
				return;

			default:
				cout << "Нет такого пункта меню." << endl;
				break;
			}
		}
	}
};