#pragma once
#include "customer.h"
#include <iomanip>
#include <string>
using namespace std;

class Admin : public Customer
{
public:
	Admin(const string& _login, const string& _password, const int _role = 1) : Customer(_login, _password)
	{
		this->role = _role;
	}
	Admin() : Customer() {}
	~Admin() {}

	void show() override
	{
		string role = "Admin";
		cout << "| "
			 << std::setw(11) << std::left << this->get_login() << "| "
			 << std::setw(65) << std::left << this->get_password() << "| "
			 << std::setw(15) << std::left << role << "|  \n";
		cout << "------------------------------------------------------------------------------------------------------\n";
	}

	int get_role() const override
	{
		return this->role;
	}
};