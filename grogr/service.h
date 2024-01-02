#pragma once
using namespace std;
#include <climits>
#include "country.h"

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
			std::cout << "Ошибка! Некорректный ввод. Попробуйте снова: ";
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
			std::cout << "Ошибка! Некорректный ввод. Попробуйте снова: ";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
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