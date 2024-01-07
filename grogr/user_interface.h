#pragma once
#include "tree.h"
#include "file_database.h"

class User_interface
{
protected:
	BinaryTree<country*> country_tree;
	file_database database;
public:
	User_interface(BinaryTree<country*> _country_tree, file_database _database) : country_tree(_country_tree), database(_database) {}
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
		cout << "\n1. Вывод информации о странах, отсортированной по численности населения." << endl;
		cout << "2. Вывод стран для заданного континента в алфавитном порядке." << endl;
		cout << "3. Поиск информации по площади в заданном диапазоне. " << endl;
	}

	void user_screen()
	{
		int choice = 0;
		while (true)
		{
			show_menu();
			cout << "0. Выход." << endl;
			cout << "Сделайте выбор: ";
			choice = input_int(choice);
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