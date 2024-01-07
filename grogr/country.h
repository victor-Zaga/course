#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

class country
{
private:
	string name;
	string continent;
	double area;
	double population;
	string capital;
public:
	country(string _name, string _continent, double _area, double _population, string _capital)
	{
		name = _name;
		continent = _continent;
		area = _area;
		population = _population;
		capital = _capital;
	}
	country()
	{
		name = "";
		continent = "";
		area = 0;
		population = 0;
		capital = "";
	}

	//геттеры
	string get_name() const { return name; }
	string get_continent() const { return continent; }
	double get_area() const { return area; }
	double get_population() const { return population; }
	string get_capital() const { return capital; }

	//сеттеры
	void set_name(const string& new_name) { this->name = new_name; }
	void set_continent(const string& new_continent) { continent = new_continent; }
	void set_area(const double new_area) { area = new_area; }
	void set_population(double new_population) { population = new_population; }
	void set_capital(const string& new_capital) { capital = new_capital; }

	void show()
	{
		cout << "| "
			<< std::setw(11) << std::left << this->get_name() << "| "
			<< std::setw(16) << std::left << this->get_continent() << "| "
			<< std::setw(19) << std::left << this->get_area() << "| "
			<< std::setw(19) << std::left << this->get_population() << "| "
			<< std::setw(11) << std::left << this->get_capital() << "|  \n";
		cout << "-------------------------------------------------------------------------------------------\n";
	}

	bool operator <(const country& con) const
	{
		return population < con.population;
	}

	bool operator >(const country& con) const
	{
		return population > con.population;
	}

	bool operator ==(const country& con) const
	{
		return name == con.name || area == con.area ||
			population == con.population || capital == con.capital;
	}

	string to_string() const
	{
		char separator = ';';

		stringstream area_stream;
		area_stream << fixed << setprecision(2) << this->get_area();
		string area_str = area_stream.str();

		std::stringstream population_stream;
		population_stream << fixed << setprecision(2) << this->get_population();
		string population_str = population_stream.str();

		// формирование строки
		string curr_country = this->get_name() + separator + this->get_continent() + separator + area_str +
			separator + population_str + separator + this->get_capital() + separator + "\n";

		return curr_country;
	}
};